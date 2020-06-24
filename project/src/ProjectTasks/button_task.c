/*
 * button_task.c
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ProjectTasks/button_task.h"
#include "ProjectTasks/view_task.h"
#include "init_menu.h"

TaskHandle_t *Button_Task;

QueueHandle_t Button_Queue;
QueueHandle_t Input_Queue;

void Button_Interrupt_Handler(void){
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken=pdTRUE;
	int b=BUTTON_GetButtonsEvents();
	xQueueSendFromISR(Button_Queue, &b, &xHigherPriorityTaskWoken);
}

void buttons_task(){
	Button_Queue= xQueueCreate(1, sizeof(int));
	if(Input_Queue == NULL)
		Input_Queue= xQueueCreate(1, sizeof(int));
	bool waiting=true;
	int button=0;
	BaseType_t result;
	init_menu(INIT_PERIPHERALS);
	while(1){
		if(waiting){
			result=xQueueReceive(Button_Queue, &button, portMAX_DELAY);
			waiting=false;
		}
		else
			result=xQueueReceive(Button_Queue, &button, 0);
		if(result == errQUEUE_EMPTY){
			taskENTER_CRITICAL();
			button=BUTTON_GetButtonsEvents();	//avoid being interrupted while reading current button state
			taskEXIT_CRITICAL();
			waiting=true;
		}
		xQueueSend(Input_Queue, &button, portMAX_DELAY);
	}
}
