/*
 * button_task.c
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "project_tasks.h"

void Button_Interrupt_Handler(void){
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken=pdTRUE;
	int b=BUTTON_GetButtonsEvents();
	xQueueSendFromISR(Button_Queue, &b, &xHigherPriorityTaskWoken);
}

void Buttons_Task(){
	bool fix=false;
	int button=0;
	BaseType_t result;
	while(1){
		if(fix)
			result=xQueueReceive(Button_Queue, &button, 0);
		else
			result=xQueueReceive(Button_Queue, &button, portMAX_DELAY);
		if(result == errQUEUE_EMPTY && fix){
			button=BUTTON_GetButtonsEvents();
			fix=false;
		}
		else if(result==pdPASS)
			fix=true;
		xQueueSend(Input_Queue, &button, portMAX_DELAY);
	}
}
