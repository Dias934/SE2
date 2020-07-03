/*
 * e2prom_task.c
 *
 *  Created on: 25/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ProjectTasks/e2prom_task.h"
#include "init_menu.h"
#include <string.h>

QueueHandle_t E2prom_request_Queue;
QueueHandle_t E2prom_response_Queue;

void init_e2prom();

void write_to_e2prom(E2PROM_MSG_TYPEDEF msg);

void read_from_e2prom(E2PROM_MSG_TYPEDEF msg);

void e2prom_task(){
	E2prom_request_Queue=xQueueCreate(1, sizeof(E2PROM_MSG_TYPEDEF));
	E2prom_response_Queue=xQueueCreate(1, sizeof(E2PROM_MSG_TYPEDEF));
	init_e2prom();
	E2PROM_MSG_TYPEDEF msg;
	while(1){
		if(xQueueReceive(E2prom_request_Queue, &msg, portMAX_DELAY)==pdPASS){
			if(msg.cmd==WRITE)
				write_to_e2prom(msg);
			else
				read_from_e2prom(msg);
		}
	}
}

void init_e2prom(){
	taskENTER_CRITICAL();
	taskENABLE_INTERRUPTS();
	while(!init_menu(INIT_E2PROM));
	taskEXIT_CRITICAL();
}

bool get_stored_data(unsigned short addr, unsigned short *buff, unsigned short size){
	bool ret=false;
	if(E2prom_request_Queue!=NULL){
		E2PROM_MSG_TYPEDEF msg;
		msg.cmd=READ;
		msg.addr=addr;
		msg.size=size;
		msg.buff=my_malloc(sizeof(unsigned short)*size);
		if(xQueueSend(E2prom_request_Queue, &msg, pdMS_TO_TICKS(WAIT_TO_READ))== pdPASS){
			if(xQueueReceive(E2prom_response_Queue, &msg, pdMS_TO_TICKS(WAIT_TO_READ))== pdPASS){
				memcpy(buff, msg.buff, size);
				ret=true;
				my_free(msg.buff);
			}
		}
	}
	return ret;
}

bool set_stored_data(unsigned short addr, unsigned short *buff, unsigned short size){
	if(E2prom_request_Queue!=NULL){
		E2PROM_MSG_TYPEDEF msg;
		msg.cmd=WRITE;
		msg.addr=addr;
		msg.size=size;
		msg.buff=my_malloc(sizeof(unsigned short)*size);
		memcpy(msg.buff, buff, size);
		xQueueSend(E2prom_request_Queue, &msg, pdMS_TO_TICKS(WAIT_TO_WRITE));
		return true;
	}
	return false;
}

void write_to_e2prom(E2PROM_MSG_TYPEDEF msg){
	short result=WRITING;
	if(msg.size==1){
		while(result!=SUCCESSFUL){
			result=WRITING;
			byte_write(msg.addr, msg.buff[0]);
			while(result==WRITING)
				result=is_writing();
		}
	}
	else{
		while(result!=SUCCESSFUL){
			result=WRITING;
			page_write(msg.addr, msg.buff, msg.size);
			while(result==WRITING)
				result=is_writing();
		}
	}
	wait_ms(BYTE_TRANSF_TIME);
	my_free(msg.buff);
}

void read_from_e2prom(E2PROM_MSG_TYPEDEF msg){
	unsigned short *buff=my_malloc(sizeof(unsigned short)*msg.size);
	short result=READING;
	while(result!=SUCCESSFUL){
		result=READING;
		if(msg.size==1)
			random_read(msg.addr, buff);
		else
			sequential_read(msg.addr, buff, msg.size);
		while(result==READING)
			result=is_reading();
	}
	memcpy(msg.buff, buff, sizeof(unsigned short)*msg.size);
	xQueueSend(E2prom_response_Queue, &msg, 0);
}


