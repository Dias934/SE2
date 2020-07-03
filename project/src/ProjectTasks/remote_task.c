/*
 * remote_task.c
 *
 *  Created on: 01/07/2020
 *      Author: Manuel Dias e Ricardo Romano
 */
#include "FreeRTOS.h"
#include "ProjectTasks/remote_task.h"
#include "queue.h"

#include "ESP01.h"

QueueHandle_t Remote_queue;


void remote_task(){

	taskENTER_CRITICAL();
	Remote_queue=xQueueCreate(1, sizeof(CMD_TYPEDEF));
	taskENABLE_INTERRUPTS();
	init_ESP01(115200);
	taskEXIT_CRITICAL();
	while(1){

	}
}

bool send_to_remote(DATA_TYPEDEF data){
	if(Remote_queue !=NULL){
		return true;
	}
	return false;
}

bool time_request(time_t *time){
	if(Remote_queue !=NULL){
		CMD_TYPEDEF remote_cmd;
		remote_cmd.cmd;
		return true;
	}
	return false;
}

