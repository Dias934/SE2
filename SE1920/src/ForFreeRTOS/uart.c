/*
 * uart.c
 *
 *  Created on: 02/04/2020
 *      Author: Manuel Dias e Ricardo Romano
 */

#include "uart.h"
#include "rbuffer.h"
#include "mem_allocation.h"

static double fr[]={1, 1.067, 1.071, 1.077, 1.083, 1.091, 1.1, 1.111, 1.125, 1.133, 1.143, 1.154, 1.167, 1.182, 1.2, 1.214, 1.222, 1.231, 1.25, 1.267, 1.273, 1.286, 1.3, 1.308, 1.333, 1.357, 1.364, 1.375, 1.385, 1.4, 1.417, 1.429, 1.444, 1.455, 1.462, 1.467, 1.5, 1.533, 1.538, 1.545, 1.556, 1.571, 1.583, 1.6, 1.615, 1.625, 1.636, 1.643, 1.667, 1.692, 1.7, 1.714, 1.727, 1.733, 1.75, 1.769, 1.778, 1.786, 1.8, 1.818, 1.833, 1.846, 1.857, 1.867, 1.875, 1.889, 1.9, 1.909, 1.917, 1.923, 1.929, 1.933};
static int DivAddVall[]={0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 3, 2, 3, 1, 4, 3, 2, 3, 4, 1, 5, 4, 3, 5, 2, 5, 3, 4, 5, 6, 7, 1, 8, 7, 6, 5, 4, 7, 3, 8, 5, 7, 9, 2, 9, 7, 5, 8, 11, 3, 10, 7, 11, 4, 9, 5, 11, 6, 13, 7, 8, 9, 10, 11, 12, 13, 14};
static int MulVal[] = {1, 15, 14, 13, 12, 11, 10, 9, 8, 15, 7, 13, 6, 11, 5, 14, 9, 13, 4, 15, 11, 7, 10, 13, 3, 14, 11, 8, 13, 5, 12, 7, 9, 11, 13, 15, 2, 15, 13, 11, 9, 7, 12, 5, 13, 8, 11, 14, 3, 13, 10, 7, 11, 15, 4, 13, 9, 14, 5, 11, 6, 13, 7, 15, 8, 9, 10, 11, 12, 13, 14, 15};

RBUF_Type *tx_uart;
RBUF_Type *rx_uart;
static bool int_mode=false;
uint32_t errors;
bool intrtx_uartStatus;

int divideAndConquer(double* array, double value, int left, int right){
	if(left==right)
		return left;
	int mean=(left+right)/2;
	if(value<array[mean])
		return divideAndConquer(array,value,left,mean);
	else if(value>array[mean])
		return divideAndConquer(array,value,mean+1,right);
	else
		return mean;
	return -1;
}

bool UARTSetDivisors(unsigned int baud){
	double DLest=((double)SystemCoreClock)/(16*baud);
	int aux=(int)DLest;
	if(DLest-aux>0){
		int idx=TABLE_SIZE/2;
		double FRest=1.5;
		do{
			if(!(FRest>1.1 && FRest<1.9)){
				if(FRest<1.1) idx++;
				else idx--;
				if(!(fr[idx]>1.1 && fr[idx]<1.9))
					return false;
			}
			DLest=(double)((int)(SystemCoreClock/(16*baud*fr[idx])));
			FRest=((double)SystemCoreClock)/(16*baud*DLest);
		}while(!(FRest>1.1 && FRest<1.9));
		FRest=((int)(FRest*1000))/1000.0;
		idx=divideAndConquer(fr,FRest,0,TABLE_SIZE-1);
		LPC_UART0->FDR=(DivAddVall[idx]<<DIVADDVAL) | (MulVal[idx]<<MULVAL);
	}
	else{
		LPC_UART0->FDR=0;
		LPC_UART0->FDR=1<<MULVAL;
	}
	LPC_UART0->LCR|= UART_LCR_DLAB_EN;
	LPC_UART0->DLL=((uint8_t)DLest);
	LPC_UART0->DLM=((int)DLest)>>8;
	LPC_UART0->LCR&= ~UART_LCR_DLAB_EN;
	return true;
}

void UART_init_Int(){
	LPC_UART0->FCR = ( UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
	LPC_UART0->IER = UART_IER_RBRINT_EN | UART_IER_RLSINT_EN;
	intrtx_uartStatus = true;
	tx_uart=init_buffer(BUFFER_SIZE);
	rx_uart=init_buffer(BUFFER_SIZE);
	while (1) {
		uint32_t iir;
		iir = (LPC_UART0->IIR & UART_IIR_MASK) & UART_IIR_INTID_MASK;
		if ((iir == UART_IIR_INTID_RDA_MASK) || (iir == UART_IIR_INTID_CTI_MASK)) {
			LPC_UART0->RBR;
		}
		else break;
	}
	NVIC_EnableIRQ(UART0_IRQn);
}

void UART_init(){
	LPC_UART0->FCR = ( UART_FCR_FIFO_EN | UART_FCR_RX_RS | UART_FCR_TX_RS);
	LPC_UART0->FCR = 0;
	uint8_t tmp;
	while (LPC_UART0->LSR & UART_LSR_RDR) { // Dummy reading - empty rx_uart!
		tmp = LPC_UART0->RBR;
	}
	LPC_UART0->TER = UART_TER_TXEN;
	while (!(LPC_UART0->LSR & UART_LSR_THRE)); // Wait for tx_uart complete
	LPC_UART0->TER = 0; // Disable tx_uart
	LPC_UART0->IER = 0; // Disable interrupt
	LPC_UART0->LCR = 0; // Set LCR to default state
	LPC_UART0->ACR = 0;
	tmp = LPC_UART0->LSR; // Clean status
	tmp = (LPC_UART0->LCR & (UART_LCR_DLAB_EN | UART_LCR_BREAK_EN)) & UART_LCR_BITMASK;
	tmp |= UART_LCR_WLEN8;
	LPC_UART0->LCR = (uint8_t) (tmp & UART_LCR_BITMASK);
	LPC_UART0->TER |= UART_TER_TXEN;
}

bool UART_Initialize(unsigned int baud, bool interrupt) {
	int_mode=interrupt;
	LPC_SC->PCLKSEL0 &= ~(UART0_PCLK_CONFIG_L);
	LPC_SC->PCLKSEL0 |= (UART0_PCLK_CONFIG_H);
	LPC_PINCON->PINSEL0 &= ~(UART0_PINSEL_CONFIG_L);
	LPC_PINCON->PINSEL0 |= UART0_PINSEL_CONFIG_H;
	LPC_PINCON->PINMODE0 &= ~(UART0_PINMODE_CONFIG_L);
	LPC_PINCON->PINMODE_OD0 &= ~(UART0_PINMODE_OD_CONFIG_L);
	if (!UARTSetDivisors(baud))
		return false;
	UART_init();
	if(interrupt)
		UART_init_Int();
	return true;
}

bool UART_GetChar(char *ch) {
	if (!UART_IsChar())
		return false;
	*ch = LPC_UART0->RBR;
	return true;
}

bool UART_IsChar(void) {
	return (LPC_UART0->LSR & UART_LSR_RDR) != 0;
}

unsigned char UART_ReadChar(void) {
	while ((LPC_UART0->LSR & UART_LSR_RDR) == 0);
	return LPC_UART0->RBR;
}

void UART_WriteChar(char ch) {
	while ((LPC_UART0->LSR & UART_LSR_THRE) == 0);
	LPC_UART0->THR = ch;
}

void UART_WriteString(char *str) {
	while (*str) UART_WriteChar(*str++);
}

bool UART_Printf(char *format, ...){
	va_list valist;
	va_start(valist,format);
	char str[100];
	int ret=vsprintf(str, format, valist);
	if(ret<0)
		return false;
	else
		UART_WriteBuffer(str,ret);
	return true;
}

uint32_t UART_WriteBuffer(char *buffer, int len) {
	uint8_t *data = (uint8_t*) buffer;
	uint32_t bytes = 0;
	LPC_UART0->IER &= (~UART_IER_THRE_EN) & UART_IER_BITMASK;
	while ((len > 0) && (!is_full(tx_uart))) {
		push(tx_uart,*data);
		data++;
		bytes++;
		len--;
	}
	uint8_t d;
	pop(tx_uart, &d);
	LPC_UART0->THR=d;
	if(intrtx_uartStatus)
		LPC_UART0->IER |= UART_IER_THRE_EN;
	return bytes;
}



uint32_t UART_ReadBuffer(char *buffer, uint32_t len) {
	uint8_t *data = (uint8_t*) buffer;
	uint32_t bytes = 0;
	LPC_UART0->IER &= (~UART_IER_RBRINT_EN) & UART_IER_BITMASK;
	while ((len > 0) && !(is_empty(rx_uart))) {
		pop(rx_uart,data);
		data++;
		bytes++;
		len--;
	}
	LPC_UART0->IER |= UART_IER_RBRINT_EN;
	return bytes;
}

void UART_Flush(){
	reset_buffer(tx_uart);
	reset_buffer(rx_uart);

}

void UART_ErrorInt(){
	errors=LPC_UART0->LSR;
}

void UART_ReceiveInt(){
	while (!is_full(rx_uart) && (LPC_UART0->LSR & UART_LSR_RDR) != 0)
		push(rx_uart,LPC_UART0->RBR);
	if(is_full(rx_uart))
		LPC_UART0->IER &= (~UART_IER_RBRINT_EN) & UART_IER_BITMASK;
}

void UART_TransmitInt(){
	LPC_UART0->IER &= (~UART_IER_THRE_EN) & UART_IER_BITMASK;
	while(!is_empty(tx_uart) && ((LPC_UART0->LSR & UART_LSR_THRE) != 0)){
		uint8_t data;
		pop(tx_uart,&data);
		LPC_UART0->THR=data;
	}
	if(is_empty(tx_uart)){
		intrtx_uartStatus=true;
	}
	else{
		intrtx_uartStatus=false;
		LPC_UART0->IER |= UART_IER_THRE_EN;
	}
}

void UART0_IRQHandler(){
	uint32_t iir;
	while (!((iir = LPC_UART0->IIR) & UART_IIR_INTSTAT_NOT_PEND)) {
		switch ((iir & UART_IIR_INTID_MASK)>>UART_IIR_INTID_POS) {
		case RLS:
			UART_ErrorInt();
			break;
		case RDA:
		case CTI:
			UART_ReceiveInt();
			break;
		case THRE_INT:
			UART_TransmitInt();
			break;
		}
	}
}
