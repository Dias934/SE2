/*
 * 24AA256.h
 *
 *  Created on: 13/03/2020
 *      Author: A38866
 */



#include "i2c.h"
#include "wait.h"

#define SLAVE_ADDR 0xA0

#define I2C_CHOSEN_BUS I2C_2

#define SLA_ADDR 0xA0

#define HALF_DUTY 50

#define PAGE_SIZE 64

#define MAX_ADDR 0x7FFF

#define BYTE_TRANSF_TIME 5

#define TRANSF_TIMEOUT 5000 //5 seconds

enum TRANSF_ERRORS{
	OUT_OF_BOUNDS,
	TIMEOUT_ERROR
};

enum READING_STATUS{
	READING=-1,
	DONE
};

int init_24AA256(unsigned short id_addr);

int byte_write(unsigned short addr, unsigned short data);

int page_write(unsigned short addr, unsigned short * tx_buffer, unsigned short length);

int current_read(unsigned short *rx);

int random_read(unsigned short addr, unsigned short *rx);

int sequential_read(unsigned short addr, unsigned short * rx_buffer, unsigned short length);

int is_reading();

