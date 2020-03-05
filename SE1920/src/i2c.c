/**
* @file		I2C.c
* @brief	Contains the I2C function utility.
* @version	1.1
* @date		5 Mar 2020
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/

#ifndef I2C_H_
#define I2C_H_

#include "LPC17xx.h"

static  LPC_I2C_TypeDef* i2c_buses[]={LPC_I2C0, LPC_I2C1, LPC_I2C2 };
static int current_bus;


void init_I2C(){

}

int I2C_ConfigTransfer(int frequency, int bitData, int mode, int bus){
	current_bus=bus;
	i2c_buses[current_bus]->I2SCLH=125;
}

int I2C_Write(unsigned short slaveAddr, unsigned short *txBuffer, int length){

}

int I2C_Read(unsigned short *txBuffer, unsigned short *rxBuffer, int length){

}

#endif
