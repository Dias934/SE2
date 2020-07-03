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
#include "ProjectTasks/e2prom_task.h"

int main(void) {
	xTaskCreate(local_task, LOCAL_TASK_NAME, LOCAL_STACK_SIZE, NULL, PRINCIPAL_PRIORITY, NULL );

	xTaskCreate(data_center_task, DATA_CENTER_TASK_NAME, DATA_CENTER_STACK_SIZE, NULL, DATA_CENTER_PRIORITY, NULL);

	xTaskCreate(e2prom_task, E2PROM_TASK_NAME, E2PROM_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, NULL);
	xTaskCreate(sensor_task, SENSOR_TASK_NAME, SENSOR_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, NULL);
	xTaskCreate(buttons_task, BUTTON_TASK_NAME, BUTTON_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, NULL );

	xTaskCreate(view_task, VIEW_TASK_NAME, VIEW_STACK_SIZE, NULL, VIEW_PRIORITY, NULL );

	vTaskStartScheduler();
}


