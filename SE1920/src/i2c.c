/**
* @file		I2C.c
* @brief	Contains the I2C function utility.
* @version	1.1
* @date		5 Mar 2020
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/

#include "i2c.h"
#include "string.h"
#include "stdlib.h"

LPC_I2C_TypeDef* i2c_buses[]={LPC_I2C0, LPC_I2C1, LPC_I2C2 };
int i2c_scl_sch_sum;
unsigned short *tx_i2c[3];
unsigned short tx_i2c_lens[3]={0,0,0};
unsigned short tx_i2c_counts[3]={0,0,0};
unsigned short tx_i2c_succ[3]={0,0,0};
unsigned short *rx_i2c[3];
unsigned short rx_i2c_lens[3]={0,0,0};
unsigned short rx_i2c_counts[3]={0,0,0};
unsigned short rx_i2c_succ[3]={0,0,0};
unsigned short sla_addr[3];
static unsigned short bus_configured=0;
static unsigned short i2c_state;

void init_I2C(){
	LPC_SC->PCLKSEL0 &= ~(PCLK_CCLK_FUNCTION_RESET<<PCLK_I2C0_BIT_POSITION);
	LPC_SC->PCLKSEL0 |= (PCLK_CCLK_FUNCTION_H<<PCLK_I2C0_BIT_POSITION);
	LPC_SC->PCLKSEL1 &= ~((PCLK_CCLK_FUNCTION_RESET<<PCLK_I2C1_BIT_POSITION)|(PCLK_CCLK_FUNCTION_RESET<<PCLK_I2C2_BIT_POSITION));
	LPC_SC->PCLKSEL1 |= (PCLK_CCLK_FUNCTION_H<<PCLK_I2C1_BIT_POSITION)|(PCLK_CCLK_FUNCTION_H<<PCLK_I2C2_BIT_POSITION);
	i2c_scl_sch_sum=SystemCoreClock/MEGA_VALUE*I2C_RATE_ADJUST;
	i2c_state=I2C_FREE;
}

void I2C_InitBus(unsigned int bus){
	if((bus_configured&bus)==0){
		bus_configured|=bus;
		switch (bus){
			case I2C_0:
				LPC_PINCON->PINSEL1 &= ~(I2C0_L_FUNCTION<<PINSEL_I2C0_BIT_POS);
				LPC_PINCON->PINSEL1 |= I2C0_H_FUNCTION<<PINSEL_I2C0_BIT_POS;

				LPC_PINCON->PINMODE1 &= ~(NO_PULL_UP_OR_DOWN_L<<PINSEL_I2C0_BIT_POS);
				LPC_PINCON->PINMODE1 |= NO_PULL_UP_OR_DOWN_H<<PINSEL_I2C0_BIT_POS;
				LPC_PINCON->PINMODE_OD1 |= OPEN_DRAIN <<PINMODE_OD_I2C0_BIT_POS;

				i2c_buses[0]->I2CONCLR=CLR_I2CONCLR;
				NVIC_EnableIRQ(I2C0_IRQn);
				break;
			case I2C_1:
				LPC_PINCON->PINSEL0 |= I2C1_FUNCTION<<PINSEL_I2C1_BIT_POS;

				LPC_PINCON->PINMODE0 &= ~(NO_PULL_UP_OR_DOWN_L<<PINSEL_I2C1_BIT_POS);
				LPC_PINCON->PINMODE0 |= NO_PULL_UP_OR_DOWN_H<<PINSEL_I2C1_BIT_POS;
				LPC_PINCON->PINMODE_OD0 |= OPEN_DRAIN <<PINMODE_OD_I2C1_BIT_POS;

				i2c_buses[1]->I2CONCLR=CLR_I2CONCLR;
				NVIC_EnableIRQ(I2C1_IRQn);
				break;
			case I2C_2:
				LPC_PINCON->PINSEL0 &= ~(I2C2_L_FUNCTION<<PINSEL_I2C2_BIT_POS);
				LPC_PINCON->PINSEL0 |= I2C2_H_FUNCTION<<PINSEL_I2C2_BIT_POS;
				LPC_PINCON->PINMODE0 &= ~(NO_PULL_UP_OR_DOWN_L<<PINSEL_I2C2_BIT_POS);
				LPC_PINCON->PINMODE0 |= NO_PULL_UP_OR_DOWN_H<<PINSEL_I2C2_BIT_POS;
				LPC_PINCON->PINMODE_OD0 |= OPEN_DRAIN <<PINMODE_OD_I2C2_BIT_POS;
				i2c_buses[2]->I2CONCLR=CLR_I2CONCLR;
				NVIC_EnableIRQ(I2C2_IRQn);
				break;
		}
	}
}

int I2C_ConfigTransfer(unsigned int frequency, unsigned int dutyCycle, unsigned short bus){
	if((bus&i2c_state)!=I2C_FREE)
		return BUS_BUSY;
	if(frequency!=I2C_STANDARD_FREQUENCY && frequency != I2C_FAST_FREQUENCY)
		return FREQUENCY_ERROR;
	if(dutyCycle>100)
		return DUTY_CYCLE_ERROR;
	if((bus&bus_configured)==0)
		return NO_BUS_CONFIGURED;
	switch (frequency){
		case I2C_STANDARD_FREQUENCY: i2c_scl_sch_sum=I2C_STANDARD_SCL_SUMS;break;
		case I2C_FAST_FREQUENCY: i2c_scl_sch_sum=I2C_FAST_SCL_SUMS;break;
	}
	i2c_buses[bus>>1]->I2SCLH=i2c_scl_sch_sum*dutyCycle/100;
	i2c_buses[bus>>1]->I2SCLL=i2c_scl_sch_sum*(100-dutyCycle)/100;
	return CONFIG_OK;
}

int I2C_Write(unsigned short slaveAddr, unsigned short *tx_i2cBuffer, unsigned short length, unsigned short bus){
	if(length<=0)
		return INVALID_LENGTH;
	if((bus&i2c_state)!=I2C_FREE)
		return BUS_BUSY;
	if((bus&bus_configured)==0)
		return NO_BUS_CONFIGURED;
	unsigned short a_bus=bus>>1;
	tx_i2c_succ[a_bus]=UNCERTAIN;
	i2c_state|=bus;
	tx_i2c_lens[a_bus]=length;
	tx_i2c_counts[a_bus]=0;
	sla_addr[a_bus]=slaveAddr;
	tx_i2c[a_bus]=malloc(sizeof(unsigned short)*length);
	memcpy(tx_i2c[a_bus], tx_i2cBuffer,sizeof(unsigned short)*length);
	i2c_buses[a_bus]->I2CONCLR=CLR_I2CONCLR;
	i2c_buses[a_bus]->I2CONSET=SET_I2EN;
	i2c_buses[a_bus]->I2CONSET=SET_STA;
	return WRITE_OK;
}

int I2C_WriteRead(unsigned short slaveAddr, unsigned short *tx_i2cBuffer, unsigned short tx_i2c_length, unsigned short *rx_i2cBuffer, unsigned short rx_i2c_length, unsigned short bus){
	if(tx_i2c_length<=0 || rx_i2c_length<=0)
		return INVALID_LENGTH;
	if((bus&i2c_state)!=I2C_FREE)
		return BUS_BUSY;
	if((bus&bus_configured)==0)
		return NO_BUS_CONFIGURED;
	i2c_state=bus;
	unsigned short a_bus=bus>>1;
	tx_i2c_succ[a_bus]=UNCERTAIN;
	rx_i2c_succ[a_bus]=UNCERTAIN;
	tx_i2c_lens[a_bus]=tx_i2c_length;
	tx_i2c_counts[a_bus]=0;
	sla_addr[a_bus]=slaveAddr;
	tx_i2c[a_bus]=malloc(sizeof(unsigned short)*tx_i2c_length);
	memcpy(tx_i2c[a_bus], tx_i2cBuffer,sizeof(unsigned short)*tx_i2c_length);
	rx_i2c_lens[a_bus]=rx_i2c_length;
	rx_i2c_counts[a_bus]=0;
	rx_i2c[a_bus]=rx_i2cBuffer;
	i2c_buses[a_bus]->I2CONCLR=CLR_I2CONCLR;
	i2c_buses[a_bus]->I2CONSET=SET_I2EN;
	i2c_buses[a_bus]->I2CONSET=SET_STA;
	return READ_OK;
}

int I2C_OnlyRead(unsigned short slaveAddr, unsigned short *rx_i2cBuffer, unsigned short rx_i2c_length, unsigned short bus){
	if(rx_i2c_length<=0)
		return INVALID_LENGTH;
	if((bus&i2c_state)!=I2C_FREE)
		return BUS_BUSY;
	if((bus&bus_configured)==0)
		return NO_BUS_CONFIGURED;
	i2c_state=bus;
	unsigned short a_bus=bus>>1;
	rx_i2c_succ[a_bus]=UNCERTAIN;
	rx_i2c_lens[a_bus]=rx_i2c_length;
	rx_i2c_counts[a_bus]=0;
	rx_i2c[a_bus]=rx_i2cBuffer;
	i2c_buses[a_bus]->I2CONCLR=CLR_I2CONCLR;
	i2c_buses[a_bus]->I2CONSET=SET_I2EN;
	i2c_buses[a_bus]->I2CONSET=SET_STA;
	return READ_OK;
}

int get_i2c_state(unsigned short bus){
	return i2c_state&bus;
}

int tx_successful(unsigned short bus){
	return tx_i2c_succ[bus>>1];
}

int rx_successful(unsigned short bus){
	if(rx_i2c_succ[bus>>1]==SUCCESSFUL)
		wait_ms(1);
	return rx_i2c_succ[bus>>1];
}

static void I2C_Handler(unsigned short in_bus){
	unsigned short bus=in_bus>>1;
	unsigned short res=(i2c_buses[bus]->I2STAT)>>I2STAT_OFFSET_BITS;
	switch(res){
		case IDLE_BUS: return;
		case M_START:
		case M_REP_START:
			i2c_buses[bus]->I2CONCLR=CLR_STA;
			if(tx_i2c_lens[bus]>0)
				i2c_buses[bus]->I2DAT=sla_addr[bus] | I2C_W;
			else
				i2c_buses[bus]->I2DAT=sla_addr[bus] | I2C_R;
			break;
		case MT_SLA_W_ACK:
			i2c_buses[bus]->I2DAT=tx_i2c[bus][tx_i2c_counts[bus]];
			tx_i2c_counts[bus]++;
			i2c_buses[bus]->I2CONSET=SET_AA;
			break;
		case MT_DATA_W_ACK:
			if(tx_i2c_counts[bus]<tx_i2c_lens[bus]){
				i2c_buses[bus]->I2DAT=tx_i2c[bus][tx_i2c_counts[bus]];
				tx_i2c_counts[bus]++;
			}
			else{
				if(rx_i2c_counts[bus]==0 && rx_i2c_lens[bus]>0)	// se houver leituras a fazer depois de uma escrita
					i2c_buses[bus]->I2CONSET=SET_STA;
				else{
					i2c_buses[bus]->I2CONSET=SET_STO;
					i2c_state&=~(in_bus);
				}
				tx_i2c_lens[bus]=0;
				tx_i2c_succ[bus]=SUCCESSFUL;
				i2c_buses[bus]->I2CONSET=SET_AA;
				free(tx_i2c[bus]);
			}
			i2c_buses[bus]->I2CONSET=SET_AA;
			break;
		case M_ARBITRATION_LOST:
			i2c_buses[bus]->I2CONSET=SET_STA|SET_AA;
			i2c_state&=~(in_bus);
			if(tx_i2c_lens[bus]>0)
				free(tx_i2c[bus]);
			break;
		case MR_DATA_R_ACK:
			rx_i2c[bus][rx_i2c_counts[bus]]=(i2c_buses[bus]->I2DAT);
			rx_i2c_counts[bus]++;
		case MR_SLA_R_ACK:
			if(rx_i2c_counts[bus]<rx_i2c_lens[bus]-1)
				i2c_buses[bus]->I2CONSET=SET_AA;
			else
				i2c_buses[bus]->I2CONCLR=CLR_AA;
			break;
		case MR_DATA_R_NOT_ACK:
			rx_i2c[bus][rx_i2c_counts[bus]]=i2c_buses[bus]->I2DAT;
			rx_i2c_counts[bus]++;
			i2c_buses[bus]->I2CONSET=SET_STO|SET_AA;
			i2c_state&=~(in_bus);
			rx_i2c_succ[bus]=SUCCESSFUL;
			break;
		case MR_SLA_R_NOT_ACK:
			i2c_buses[bus]->I2CONSET=SET_STO|SET_AA;
			i2c_state&=~(in_bus);
			rx_i2c_succ[bus]=UNSUCC;
			break;
		case MT_SLA_W_NOT_ACK:
		case MT_DATA_W_NOT_ACK:
			i2c_buses[bus]->I2CONSET=SET_STO|SET_AA;
			i2c_state&=~(in_bus);
			tx_i2c_lens[bus]=0;
			free(tx_i2c[bus]);
			tx_i2c_succ[bus]=UNSUCC;
			break;
		default:
			i2c_buses[bus]->I2CONSET=SET_STO|SET_AA;
			i2c_state&=~(in_bus);
	}
	i2c_buses[bus]->I2CONCLR=CLR_SI;
}

void I2C0_IRQHandler(void){
	I2C_Handler(I2C_0);
}

void I2C1_IRQHandler(void){
	I2C_Handler(I2C_1);
}

void I2C2_IRQHandler(void){
	I2C_Handler(I2C_2);
}

