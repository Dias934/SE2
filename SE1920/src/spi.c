/*
 * spi.c
 *
 *  Created on: 07/11/2019
 *      Author: A38866
 */


#include "spi.h"

void init_spi(void){
	LPC_PINCON->PINSEL0 |= SPI_FUNCTION<<PINSEL_SCK_BIT_POS;
	LPC_PINCON->PINSEL1 |= SPI_FUNCTION<<PINSEL_MISO_BIT_POS | SPI_FUNCTION<<PINSEL_MOSI_BIT_POS;
	LPC_SPI->SPCR |= MASTER_MODE<<MASTER_MODE_BIT_POSITION | BITS_MODE<<BIT_ENABLE_BIT_POSITION;
	LPC_SPI->SPCR &= ~(MSB_MODE_L<<LSBF_BIT_POSITION);
	LPC_SC->PCLKSEL0 &= ~(PCLK_CCLK_FUNCTION_L<<PCLK_SPI_BIT_POSITION);
}


int SPI_ConfigTransfer(int frequency, int bitData, int mode){
	int ret=CUSTOM_CONFIG_TRANSFER;
	int div=SystemCoreClock/frequency;
	int data=bitData;
	int clkMode=mode;
	if(div<8){
		div=8;
		ret+=DEFAULT_FREQUENCY;
	}
	else if(div%2>0)
		div++;
	LPC_SPI->SPCCR=div;
	if(bitData<EIGHT_BITS || bitData>FIFTEEN_BITS){
		data=SIXTEEN_BITS;
		ret+=DEFAULT_DATABIT;
	}
	LPC_SPI->SPCR &= ~(BITS_MASK<<BITS_BIT_POSITION); //erase previous value
	LPC_SPI->SPCR |= data<<BITS_BIT_POSITION; //set new value
	if(clkMode>CPHA_CPOL_HH){
		clkMode=CPHA_CPOL_LL;
		ret+=DEFAULT_MODE;
	}
	LPC_SPI->SPCR &= ~((clkMode&CPHA_CPOL_BIT_MASK)<<CPHA_CPOL_BIT_POSITION);
	return ret;
}

int SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int length){
	short status=LPC_SPI->SPSR; //clear the status register. Optional but suggested by the manufacturer
	status=SPIF;
	for(int i=0; i<length && status==SPIF;i++){
		status=0;  //clear the status of the previous transfer
		LPC_SPI->SPDR=txBuffer[i];
		do{
			status=((LPC_SPI->SPSR)>>3)&0x1F;
		}while(status==0);
		if(status==MODF)
			LPC_SPI->SPCR |= 1<<5;
		else if(status==WCOL)
			LPC_SPI->SPDR;
		else if(status==SPIF)
			rxBuffer[i]=LPC_SPI->SPDR;
	}
	return status;
}

