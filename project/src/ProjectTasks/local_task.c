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
#include "ProjectTasks/button_task.h"
#include "peripherals.h"
#include "menu_normal.h"
#include <string.h>

void end_local_init_seq();


QueueHandle_t Local_In_Queue;

void local_task(){
	end_local_init_seq();
	void *(*menu_execute)()=&normal_execution;
	while(1){
		get_buttons_map(&button_map);
		xQueueReceive(Local_In_Queue, &local_data, pdMS_TO_TICKS(WAIT_FOR_BUTTON_TIMEOUT));
		menu_execute=menu_execute();
	}
}

void end_local_init_seq(){
	Local_In_Queue= xQueueCreate(1, sizeof(DATA_TYPEDEF));
	while(!init_menu(INIT_END))
		vTaskDelay( pdMS_TO_TICKS(INIT_WAIT_DELAY));
	send_to_view(VIEW_INIT_RESULTS, END_LOCAL_INIT,strlen(END_LOCAL_INIT) , 1);
}

void send_to_local(DATA_TYPEDEF data){
	if(Local_In_Queue != NULL)
		if(xQueueSend(Local_In_Queue, &data, 0)!= pdPASS)
			xQueueOverwrite(Local_In_Queue, &data);
}
