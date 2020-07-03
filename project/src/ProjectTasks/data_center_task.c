/*
 * data_center_task.c
 *
 *  Created on: 18/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ProjectTasks/data_center_task.h"
#include "ProjectTasks/sensor_task.h"
#include "ProjectTasks/local_task.h"
#include "ProjectTasks/e2prom_task.h"
#include <string.h>

TaskHandle_t *Data_center_Task;

DATA_TYPEDEF curr_data;
CMD_TYPEDEF maintenance_cmd;

QueueHandle_t Remote_In_Queue;
QueueHandle_t Data_In_Queue;

void execute_cmd();

void get_curr_time();

void init_data_center();

void change_time(struct tm cal);

void change_calendar(struct tm cal);

void change_temperature_unit(unsigned short unit);

void change_time_calendar();

void data_center_task(){
	Data_In_Queue= xQueueCreate(DATA_IN_QUEUE_SIZE, sizeof(CMD_TYPEDEF));
	init_data_center();
	while(1){
		get_curr_time();
		get_sensor_info(&curr_data.sensor_info);
		send_to_local(curr_data);
		//send_to_remote(curr_data); //send data for MQTT
		if(xQueueReceive(Data_In_Queue, &maintenance_cmd, pdMS_TO_TICKS(WAITING_FOR_MAINTENANCE)) == pdPASS)
			execute_cmd();
	}
}

void init_data_center(){
	unsigned short rx=0;
	while(!get_stored_data(PROJECT_ID_ADDR, &rx, 1));
	if(rx== PROJECT_ID_VAL){	//load data from memory
		get_stored_data(TEMPERATURE_UNIT_ADDR, &curr_data.unit, 1);
	}
	else{						//prepare data
		rx=PROJECT_ID_VAL;
		curr_data.unit=CELSIUS;
		set_stored_data(PROJECT_ID_ADDR, &rx, 1);	//write project ID value to read data after reset
		unsigned short aux=0;
	}
}

void get_curr_time(){
	RTC_GetValue(&curr_data.cal);
}

void execute_cmd(){
	switch(maintenance_cmd.cmd){
	case CHANGE_TIME: change_time(*((struct tm *)maintenance_cmd.args)); break;
	case CHANGE_CALENDAR: change_calendar(*((struct tm *)maintenance_cmd.args)); break;
	case CHANGE_TIME_CALENDAR: change_time_calendar(); break;
	case CHANGE_TEMPERATURE_UNIT: change_temperature_unit(*((unsigned short *)maintenance_cmd.args)); break;
	}
	if(maintenance_cmd.args_size>0)
		my_free(maintenance_cmd.args);
}

void change_time(struct tm cal){
	RTC_SetMaskedValue(&cal, HOUR_MASK | MIN_MASK);
}

void change_calendar(struct tm cal){
	RTC_SetMaskedValue(&cal, YEAR_MASK | MONTH_MASK | DOM_MASK);
}

void change_temperature_unit(unsigned short unit){
	curr_data.unit=unit;
	set_stored_data(TEMPERATURE_UNIT_ADDR, &curr_data.unit, sizeof(unsigned short));
}

void change_time_calendar(){

	/*RTC_SetMaskedValue(&cal, YEAR_MASK | MONTH_MASK | DOM_MASK | DOY_MASK | DOW_MASK |
			HOUR_MASK | MIN_MASK | SEC_MASK);*/
}

bool send_new_time(struct tm newTime){
	if(Data_In_Queue!=NULL){
		CMD_TYPEDEF maintenance;
		maintenance.cmd=CHANGE_TIME;
		maintenance.args_size=sizeof(struct tm);
		maintenance.args=my_malloc(sizeof(struct tm));
		memcpy(maintenance.args, &newTime, sizeof(struct tm));
		xQueueSend(Data_In_Queue, &maintenance, portMAX_DELAY);
		return true;
	}
	return false;
}

bool send_new_calendar(struct tm newTime){
	if(Data_In_Queue!=NULL){
		CMD_TYPEDEF maintenance;
		maintenance.cmd=CHANGE_CALENDAR;
		maintenance.args_size=sizeof(struct tm);
		maintenance.args=my_malloc(sizeof(struct tm));
		memcpy(maintenance.args, &newTime, sizeof(struct tm));
		xQueueSend(Data_In_Queue, &maintenance, portMAX_DELAY);
		return true;
	}
	return false;
}

bool send_new_temperature_unit(unsigned short unit){
	if(Data_In_Queue!=NULL){
		CMD_TYPEDEF maintenance;
		maintenance.cmd=CHANGE_TEMPERATURE_UNIT;
		maintenance.args_size=sizeof(unsigned short);
		maintenance.args=my_malloc(sizeof(unsigned short));
		memcpy(maintenance.args, &unit, sizeof(unsigned short));
		xQueueSend(Data_In_Queue, &maintenance, portMAX_DELAY);
		return true;
	}
	return false;
}

bool send_new_calendar_time(){
	if(Data_In_Queue!=NULL){
		CMD_TYPEDEF maintenance;
		maintenance.cmd=CHANGE_TIME_CALENDAR;
		xQueueSend(Data_In_Queue, &maintenance, portMAX_DELAY);
		return true;
	}
	return false;
}
