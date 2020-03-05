/**
* @file		I2C.h
* @brief	Contains the I2C function utility.
* @version	1.1
* @date		5 Mar 2020
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/

#ifndef I2C_H_
#define I2C_H_

#include "LPC17xx.h"

enum I2C_BUS{
	I2C_0 =0,
	I2C_1,
	I2C_2
};

enum I2C_CONFIG_RETURN_VALUES{
	FREQUENCY_ERROR=-3,
	DUTY_CYCLE_ERROR,
	BUS_ERROR,
	CONFIG_OK
};

#define I2C_FUNCTION 3
#define PCLK_CCLK_FUNCTION_L 2
#define PCLK_I2C0_BIT_POSITION 14
#define PCLK_I2C1_BIT_POSITION 6
#define PCLK_I2C2_BIT_POSITION 20

#define I2C0_FUNCTION 10
#define PINSEL_I2C0_BIT_POS 22

#define I2C1_FUNCTION 15
#define PINSEL_I2C1_BIT_POS 0

#define I2C2_FUNCTION 5
#define PINSEL_I2C2_BIT_POS 20

#define MEGA_VALUE 1000000
#define I2C_RATE_ADJUST 10

void init_I2C();

int I2C_ConfigTransfer(unsigned int frequency, unsigned int dutyCycle, unsigned int bus);

int I2C_Write(unsigned short slaveAddr, unsigned short *txBuffer, int length);

int I2C_Read(unsigned short *txBuffer, unsigned short *rxBuffer, int length);
#endif /* I2C_H_ */
