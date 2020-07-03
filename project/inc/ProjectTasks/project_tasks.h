/*
 * project_tasks.h
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#ifndef PROJECT_TASKS_H_
#define PROJECT_TASKS_H_

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "peripherals.h"
#include "mem_allocation.h"

#define PERIPHERALS_PRIORITY 	4
#define PRINCIPAL_PRIORITY		2

extern QueueHandle_t Input_Queue;
extern QueueHandle_t View_Queue;
extern QueueHandle_t Local_In_Queue;
extern QueueHandle_t Remote_In_Queue;
extern QueueHandle_t Data_In_Queue;


#endif /* PROJECT_TASKS_H_ */
