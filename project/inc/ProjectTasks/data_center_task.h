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

#define PROJECT_ID_ADDR 		0x08
#define PROJECT_ID_VAL			0xA0

#define TEMPERATURE_UNIT_ADDR	0x10

enum DATA_REQUESTS{
	CHANGE_TIME=0,
	CHANGE_CALENDAR,
	CHANGE_TIME_CALENDAR,
	CHANGE_TEMPERATURE_UNIT
};

void data_center_task();

bool send_new_time(struct tm newTime);

bool send_new_calendar(struct tm newTime);

bool send_new_temperature_unit(unsigned short unit);

bool send_new_calendar_time();

#endif /* SENSOR_TASK_H_ */
