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


#include "peripherals.h"

#define PERIPHERALS_PRIORITY 	5
#define PRINCIPAL_PRIORITY		2

typedef struct{
	short cmd;
	uint32_t *args;
}LCD_CMD_TYPEDEF;

extern QueueHandle_t Button_Queue;
extern QueueHandle_t Input_Queue;
extern QueueHandle_t LCD_Queue;

void Buttons_Task();

void LCD_Task();

void Local_Task();

#endif /* PROJECT_TASKS_H_ */
