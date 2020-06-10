/*
 * local_task.c
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "project_tasks.h"

void Local_Task(){
	int in;
	char str[16];
	while(1){
		xQueueReceive(Input_Queue, &in, portMAX_DELAY);
		printf("%d\n",in);
		sprintf(str,"%d",in);
		xQueueSend(LCD_Queue, str, portMAX_DELAY);
	}
}
