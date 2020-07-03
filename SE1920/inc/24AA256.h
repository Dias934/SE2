/*
 * 24AA256.h
 *
 *  Created on: 13/03/2020
 *      Author: A38866
 */

#ifndef E2PROM_H_
#define E2PROM_H_

#include "i2c.h"
#include "wait.h"
#include <stdbool.h>

#define SLAVE_ADDR 0xA0

#define I2C_CHOSEN_BUS I2C_2

#define SLA_ADDR 0xA0

#define HALF_DUTY 50

#define PAGE_SIZE 64

#define MAX_ADDR 0x7FFF

#define BYTE_TRANSF_TIME 10

#define INIT_WRITE_BYTE_TEST	0xA5

#define TRANSF_TIMEOUT 5000 //5 seconds

enum TRANSF_ERRORS{
	OUT_OF_BOUNDS,
	TIMEOUT_ERROR
};

enum READ_WRITE_STATUS{
	READING=-2,
	WRITING,
	DONE
};

bool init_24AA256(unsigned short id_addr);

int byte_write(unsigned short addr, unsigned short data);

int page_write(unsigned short addr, unsigned short * tx_buffer, unsigned short length);

int current_read(unsigned short *rx);

int random_read(unsigned short addr, unsigned short *rx);

int sequential_read(unsigned short addr, unsigned short * rx_buffer, unsigned short length);

int is_writing();

int is_reading();

#endif
