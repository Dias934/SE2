/**
* @file		I2C.c
* @brief	Contains the I2C function utility.
* @version	1.1
* @date		5 Mar 2020
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/


#include "LPC17xx.h"
#include "i2c.h"

static  LPC_I2C_TypeDef* i2c_buses[]={LPC_I2C0, LPC_I2C1, LPC_I2C2 };
static int current_bus;
static int i2c_scl_sch_sum;

void init_I2C(){
	LPC_SC->PCLKSEL0 &= ~(PCLK_CCLK_FUNCTION_L<<PCLK_I2C0_BIT_POSITION);
	LPC_SC->PCLKSEL1 &= ~((PCLK_CCLK_FUNCTION_L<<PCLK_I2C1_BIT_POSITION)|(PCLK_CCLK_FUNCTION_L<<PCLK_I2C2_BIT_POSITION));
	i2c_scl_sch_sum=SystemCoreClock/MEGA_VALUE*I2C_RATE_ADJUST;
}

int I2C_ConfigTransfer(unsigned int frequency, unsigned int dutyCycle, unsigned int bus){
	if(frequency>100000)
		return FREQUENCY_ERROR;
	if(dutyCycle>100)
		return DUTY_CYCLE_ERROR;
	if(bus>I2C_2)
		return BUS_ERROR;
	current_bus=bus;
	switch (bus){
			case 0:
				LPC_PINCON->PINSEL1 &= ~(I2C0_FUNCTION<<PINSEL_I2C0_BIT_POS);
				break;
			case 1:
				LPC_PINCON->PINSEL0 |= I2C1_FUNCTION<<PINSEL_I2C1_BIT_POS;
				break;
			case 2:
				LPC_PINCON->PINSEL0 &= ~(I2C2_FUNCTION<<PINSEL_I2C2_BIT_POS);
				break;
	}
	i2c_buses[current_bus]->I2SCLH=i2c_scl_sch_sum*dutyCycle/100;
	i2c_buses[current_bus]->I2SCLL=i2c_scl_sch_sum*(100-dutyCycle)/100;
	return CONFIG_OK;
}

int I2C_Write(unsigned short slaveAddr, unsigned short *txBuffer, int length){
	return 0;
}

int I2C_Read(unsigned short *txBuffer, unsigned short *rxBuffer, int length){
	return 0;
}

