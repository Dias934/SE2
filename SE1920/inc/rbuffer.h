/*
 * rbuffer.h
 *
 *  Created on: 16/04/2020
 *      Author: Manuel
 */

#ifndef RBUFFER_H_
#define RBUFFER_H_
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "stdbool.h"
#include "stdlib.h"

typedef struct {
	uint32_t size;
	uint32_t head;
	uint32_t tail;
    uint8_t* b;
} RBUF_Type;

RBUF_Type* init_buffer(unsigned int size);

bool is_full(RBUF_Type* buff);

bool is_empty(RBUF_Type* buff);

void reset_buffer(RBUF_Type* buff);

bool push(RBUF_Type* buff, uint8_t data);

bool pop(RBUF_Type* buff, uint8_t* data);

void delete_buffer(RBUF_Type* buff);

#endif /* RBUFFER_H_ */
