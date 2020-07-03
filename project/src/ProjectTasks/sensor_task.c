/*
 * sensor_task.c
 *
 *  Created on: 18/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ProjectTasks/sensor_task.h"
#include "init_menu.h"

TaskHandle_t *Sensor_Task;

QueueHandle_t Sensor_Queue;

static SENSOR_TYPEDEF sensor_inf=SENSOR_INIT_STATE;

void init_sensor_task();

void sensor_task(){
	Sensor_Queue= xQueueCreate(1, sizeof(SENSOR_TYPEDEF));
	init_sensor_task();
	int ret;
	while(1){
		taskENTER_CRITICAL();
		ret=measure();
		taskEXIT_CRITICAL();
		sensor_inf.valid=!(ret==TRANSF_ERROR);
		if(sensor_inf.valid){
			sensor_inf.press=current_press;
			sensor_inf.temp=current_temp;
			if(xQueueSend(Sensor_Queue, &sensor_inf, pdMS_TO_TICKS(WAIT_NEXT_MEASURE_INTERVAL))!= pdPASS)
				xQueueOverwrite(Sensor_Queue,&sensor_inf);
		}
		else{
			taskENTER_CRITICAL();
			init_sensor_task();
			taskEXIT_CRITICAL();
		}
	}
}

void init_sensor_task(){
	while(!sensor_inf.valid){
		taskENTER_CRITICAL();
		sensor_inf.valid=init_menu(INIT_BMP280);
		taskEXIT_CRITICAL();
		if(xQueueSend(Sensor_Queue, &sensor_inf, pdMS_TO_TICKS(RESTART_INIT_TIME))!= pdPASS)
			xQueueOverwrite(Sensor_Queue,&sensor_inf);
	}
}

void get_sensor_info(SENSOR_TYPEDEF * ptr){
	if(Sensor_Queue != NULL){
		if(xQueueReceive(Sensor_Queue, ptr, pdMS_TO_TICKS(WAIT_NEXT_MEASURE_INTERVAL))==errQUEUE_EMPTY)
			ptr->valid=false;
	}
}


