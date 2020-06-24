/*
 * data_center_task.h
 *
 *  Created on: 18/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "project_tasks.h"
#include "sensor_task.h"
#include "data_center.h"
#include <time.h>

#ifndef DATA_CENTER_TASK_H_
#define DATA_CENTER_TASK_H_

#define DATA_CENTER_TASK_NAME "Data Center"
#define DATA_CENTER_STACK_SIZE (configMINIMAL_STACK_SIZE*2)
#define DATA_CENTER_PRIORITY	3
#define DATA_IN_QUEUE_SIZE 		2	//data income from local and remote

#define WAITING_FOR_MAINTENANCE	100

enum DATA_REQUESTS{
	CHANGE_TIME=0,
	CHANGE_CALENDAR,
	CHANGE_TIME_CALENDAR,
	CHANGE_TEMPERATURE_UNIT
};

typedef struct{
	short cmd;
	void *args;
}MAINTENANCE_CMD_TYPEDEF;

extern TaskHandle_t *Data_center_Task;

void data_center_task();


#endif /* SENSOR_TASK_H_ */
