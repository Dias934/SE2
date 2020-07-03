/*
 * sensor_task.h
 *
 *  Created on: 18/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "project_tasks.h"
#include "my_types.h"
#include "BMP280.h"

#ifndef SENSOR_TASK_H_
#define SENSOR_TASK_H_

#define SENSOR_TASK_NAME 	"Sensor"
#define SENSOR_STACK_SIZE 	(configMINIMAL_STACK_SIZE)

#define SENSOR_INIT_STATE 	{0, 0, false}

#define RESTART_INIT_TIME 	10
#define WAIT_NEXT_MEASURE_INTERVAL 	250


void sensor_task();

void get_sensor_info(SENSOR_TYPEDEF * ptr);

#endif /* SENSOR_TASK_H_ */
