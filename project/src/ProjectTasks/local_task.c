/*
 * local_task.c
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "ProjectTasks/local_task.h"
#include "init_menu.h"
#include "ProjectTasks/view_task.h"
#include "ProjectTasks/data_center_task.h"
#include "peripherals.h"
#include "menu_normal.h"
#include <string.h>

void end_local_init_seq();

TaskHandle_t *Local_Task;
LCD_CMD_TYPEDEF* cmde;

void local_task(){
	end_local_init_seq();
	cmde=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	local_data=my_malloc(sizeof(DATA_TYPEDEF));
	void *(*menu_execute)()=&normal_execution;
	while(1){
		xQueueReceive(Input_Queue, &button_map, pdMS_TO_TICKS(WAIT_FOR_BUTTON_TIMEOUT));
		if(xQueueReceive(Local_In_Queue, local_data, 1)!= pdPASS)
			button_map=button_map;
		menu_execute=menu_execute();
	}
	my_free(cmde);
}

void end_local_init_seq(){
	if(Input_Queue == NULL)
		Input_Queue= xQueueCreate(1, sizeof(int));
	if(View_Queue == NULL)
		View_Queue= xQueueCreate(10, sizeof(LCD_CMD_TYPEDEF));
	if(Data_In_Queue == NULL)
		Data_In_Queue= xQueueCreate(DATA_IN_QUEUE_SIZE, sizeof(MAINTENANCE_CMD_TYPEDEF));
	if(Local_In_Queue == NULL)
		Local_In_Queue= xQueueCreate(1, sizeof(DATA_TYPEDEF));
	while(init_menu(INIT_END))
		taskYIELD();
	cmde=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmde->cmd=VIEW_INIT_RESULTS;
	cmde->args=my_malloc(strlen(END_LOCAL_INIT));
	memcpy(cmde->args, &END_LOCAL_INIT, strlen(END_LOCAL_INIT)+1);
	xQueueSend(View_Queue, cmde, portMAX_DELAY);
	my_free(cmde);
}
