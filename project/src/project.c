/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "project_tasks.h"

QueueHandle_t Button_Queue;
QueueHandle_t Input_Queue;
QueueHandle_t LCD_Queue;



void init(){
	init_BUTTON();
	init_wait();
	Button_Queue= xQueueCreate(1, sizeof(int));
	Input_Queue= xQueueCreate(1, sizeof(int));
	LCD_Queue= xQueueCreate(50, sizeof(char *));
}

int main(void) {
	init();
	xTaskCreate(Buttons_Task, "Buttons", configMINIMAL_STACK_SIZE, NULL, PERIPHERALS_PRIORITY, NULL );
	xTaskCreate(LCD_Task, "LCD", configMINIMAL_STACK_SIZE*5, NULL, PERIPHERALS_PRIORITY, NULL );
	xTaskCreate(Local_Task, "Local", configMINIMAL_STACK_SIZE, NULL, PRINCIPAL_PRIORITY, NULL );
	vTaskStartScheduler();
	/*void *(*menu_execute)()=&start_inits;
    while(1) {
    	menu_execute=menu_execute();
    }
    return 0 ;*/
}


