/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "ProjectTasks/view_task.h"
#include "ProjectTasks/local_task.h"
#include "ProjectTasks/button_task.h"
#include "ProjectTasks/data_center_task.h"
#include "ProjectTasks/sensor_task.h"

int main(void) {
	xTaskCreate(local_task, LOCAL_TASK_NAME, LOCAL_STACK_SIZE, NULL, PRINCIPAL_PRIORITY, Local_Task );

	xTaskCreate(data_center_task, DATA_CENTER_TASK_NAME, DATA_CENTER_STACK_SIZE, NULL, DATA_CENTER_PRIORITY, Data_center_Task);

	xTaskCreate(sensor_task, SENSOR_TASK_NAME, SENSOR_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, Sensor_Task);

	xTaskCreate(buttons_task, BUTTON_TASK_NAME, BUTTON_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, Button_Task );

	xTaskCreate(view_task, VIEW_TASK_NAME, VIEW_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, View_Task );

	vTaskStartScheduler();
}


