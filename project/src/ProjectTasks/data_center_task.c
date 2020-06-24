/*
 * data_center_task.c
 *
 *  Created on: 18/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ProjectTasks/data_center_task.h"
#include "ProjectTasks/sensor_task.h"

TaskHandle_t *Data_center_Task;

DATA_TYPEDEF *curr_data;
MAINTENANCE_CMD_TYPEDEF *maintenance_cmd;

QueueHandle_t Local_In_Queue;
QueueHandle_t Remote_In_Queue;
QueueHandle_t Data_In_Queue;

static double celsius_to_far();

static double celsius();

static double (*temperature_funcs[])()={celsius, celsius_to_far};

static void execute_cmd();

void get_sensor_info();

void get_curr_time();

void data_center_task(){
	if(Sensor_Queue == NULL)
		Sensor_Queue= xQueueCreate(1, sizeof(SENSOR_TYPEDEF));
	if(Local_In_Queue == NULL)
		Local_In_Queue= xQueueCreate(1, sizeof(DATA_TYPEDEF));
	if(Remote_In_Queue == NULL)
		Remote_In_Queue= xQueueCreate(1, sizeof(DATA_TYPEDEF));
	if(Data_In_Queue == NULL)
		Data_In_Queue= xQueueCreate(DATA_IN_QUEUE_SIZE, sizeof(MAINTENANCE_CMD_TYPEDEF));
	curr_data=my_malloc(sizeof(DATA_TYPEDEF));
	curr_data->unit=0;
	while(1){
		get_curr_time();
		get_sensor_info();
		if(xQueueSend(Local_In_Queue, &curr_data, 0)!= pdPASS)
			xQueueOverwrite(Local_In_Queue, curr_data);
		if(xQueueSend(Remote_In_Queue, &curr_data, 0)!=pdPASS)
			xQueueOverwrite(Remote_In_Queue, curr_data);
		if(xQueueReceive(Data_In_Queue, maintenance_cmd, pdMS_TO_TICKS(WAITING_FOR_MAINTENANCE)) == pdPASS)
			execute_cmd();
	}
}

void get_sensor_info(){
	if(xQueueReceive(Sensor_Queue, &curr_data->sensor_info, pdMS_TO_TICKS(WAIT_NEXT_MEASURE_INTERVAL))==errQUEUE_EMPTY)
		curr_data->sensor_info.valid=false;
	else
		curr_data->sensor_info.temp=temperature_funcs[curr_data->unit]();
}

void get_curr_time(){
	RTC_GetValue(&curr_data->cal);
}

void execute_cmd(){

}

static double celsius_to_far(){
	return (curr_data->sensor_info.temp)*9/5 + 32;
}

static double celsius(){
	return curr_data->sensor_info.temp;
}
