/*
 * rbuffer.c
 *
 *  Created on: 16/04/2020
 *      Author: Manuel
 */

#include "rbuffer.h"
#include "math.h"

void pow_of_2(unsigned int *size){
	double result=sqrt(*size);
	if(result-((int)result)>0.0)
		*size=(unsigned int)pow(((unsigned int) result)+1,2.0);
}

RBUF_Type* init_buffer(unsigned int size){
	pow_of_2(&size);
	RBUF_Type* buff= malloc(sizeof(RBUF_Type));
	buff->b=malloc(sizeof(uint8_t)*size*2);
	buff->size=size;
	buff->tail=0;
	buff->head=0;
	reset_buffer(buff);
	return buff;
}

bool is_full(RBUF_Type* buff){
	return ((buff->tail & ((buff->size)-1))==(((buff->head)+1)&((buff->size)-1)));
}

bool is_empty(RBUF_Type* buff){
	return ((buff->tail & ((buff->size)-1))==(((buff->head))&((buff->size)-1)));
}

void reset_buffer(RBUF_Type* buff){
	buff->tail=0;
	buff->head=0;
}

bool push(RBUF_Type* buff, uint8_t data){
	if(is_full(buff))
		return false;
	int x=(buff->head)++ & ((buff->size)-1);
	buff->b[x]=data;
	return true;
}

bool pop(RBUF_Type* buff, uint8_t* data){
	if(is_empty(buff))
		return false;
	int x=(buff->tail++) & ((buff->size)-1);
	*data=buff->b[x];
	return true;
}

void delete_buffer(RBUF_Type* buff){
	free(buff);
}
