/**
* @file		I2C.h
* @brief	Contains the sensor interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano,  Manuel Dias
* @numbers  43924, 38866
*/

#ifndef I2C_H_
#define I2C_H_
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "wait.h"
#endif

enum I2C_BUS{
	I2C_0 =0,
	I2C_1,
	I2C_2
};

enum I2C_TRANSF_RESULT{
	UNSUCC=-1,
	UNCERTAIN,
	SUCCESSFUL
};

enum I2C_RETURN_VALUES{
	FREQUENCY_ERROR=-6,
	DUTY_CYCLE_ERROR,
	BUS_ERROR,
	NO_BUS_CONFIGURED,
	BUS_BUSY,
	INVALID_LENGTH,
	CONFIG_OK,
	WRITE_OK,
	READ_OK
};

enum I2C_STATUS_CODES{
	M_START=1,
	M_REP_START,
	MT_SLA_W_ACK, //Master Transmitter Slave Write ACK
	MT_SLA_W_NOT_ACK,
	MT_DATA_W_ACK, //Master Transmitter Data Write ACK
	MT_DATA_W_NOT_ACK,
	M_ARBITRATION_LOST,
	MR_SLA_R_ACK, //Master Receiver Slave Read ACK
	MR_SLA_R_NOT_ACK,
	MR_DATA_R_ACK, //Master Receiver Data Read ACK
	MR_DATA_R_NOT_ACK,
	IDLE_BUS=0x1F
};

#define I2C_FREE 0

#define I2C_0 1
#define I2C_1 I2C_0<<1
#define I2C_2 I2C_0<<2

#define I2C_W 0
#define I2C_R 1


#define I2C_STANDARD_FREQUENCY 100000
#define I2C_FAST_FREQUENCY 400000

#define I2C_STANDARD_SCL_SUMS 1000
#define I2C_FAST_SCL_SUMS 250

#define I2STAT_OFFSET_BITS 3

#define I2C_FUNCTION 3
#define PCLK_CCLK_FUNCTION_RESET 3
#define PCLK_CCLK_FUNCTION_H 1
#define PCLK_I2C0_BIT_POSITION 14
#define PCLK_I2C1_BIT_POSITION 6
#define PCLK_I2C2_BIT_POSITION 20

#define I2C0_L_FUNCTION 10
#define I2C0_H_FUNCTION 5
#define PINSEL_I2C0_BIT_POS 22

#define I2C1_FUNCTION 15
#define PINSEL_I2C1_BIT_POS 0

#define I2C2_L_FUNCTION 5
#define I2C2_H_FUNCTION 10
#define PINSEL_I2C2_BIT_POS 20

#define MEGA_VALUE 1000000
#define I2C_RATE_ADJUST 10

#define AA_POS 2
#define SI_POS 3
#define STO_POS 4
#define STA_POS 5
#define I2EN_POS 6
#define SET_AA 1<<AA_POS
#define SET_SI 1<<SI_POS
#define SET_STA 1<<STA_POS
#define SET_STO 1<<STO_POS
#define SET_I2EN 1<<I2EN_POS

#define AAC_POS 2
#define SIC_POS 3
#define STAC_POS 5
#define I2ENC_POS 6
#define CLR_AA 1<<AAC_POS
#define CLR_SI 1<<SIC_POS
#define CLR_STA 1<<STAC_POS
#define CLR_I2EN 1<<I2ENC_POS
#define CLR_I2CONCLR CLR_AA|CLR_SI|CLR_STA|CLR_I2EN

#define NO_PULL_UP_OR_DOWN_L 5
#define NO_PULL_UP_OR_DOWN_H 10

#define OPEN_DRAIN 3

#define PINMODE_OD_I2C0_BIT_POS 27
#define PINMODE_OD_I2C1_BIT_POS 0
#define PINMODE_OD_I2C2_BIT_POS 10

void init_I2C();

void I2C_InitBus(unsigned int bus);

int I2C_ConfigTransfer(unsigned int frequency, unsigned int dutyCycle, unsigned short bus);

int I2C_Write(unsigned short slaveAddr, unsigned short *txBuffer, unsigned short length, unsigned short bus);

int I2C_WriteRead(unsigned short slaveAddr, unsigned short *txBuffer, unsigned short tx_length, unsigned short *rxBuffer, unsigned short rx_length, unsigned short bus);

int I2C_OnlyRead(unsigned short slaveAddr, unsigned short *rxBuffer, unsigned short rx_length, unsigned short bus);

int get_i2c_state(unsigned short bus);

int tx_successful(unsigned short bus);

int rx_successful(unsigned short bus);

#endif /* I2C_H_ */
