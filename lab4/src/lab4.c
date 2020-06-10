/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "FreeRTOS.h"
#include "peripherals.h"
#include "task.h"
#include "event_groups.h"
#include "LPC17xx.h"

	EventGroupHandle_t xButtonGroup;

/*void Button_Interrupt_Handler(void){
	xEventGroupSetBitsFromISR( xButtonGroup, 1, pdFALSE);
}

void Buttons_Action(void){
	xButtonGroup = xEventGroupCreate();
	while(1){
		 int x=xEventGroupWaitBits( xButtonGroup, 1, pdTRUE, pdFALSE,  pdMS_TO_TICKS( 100 ));
		 if(x==1)
			 printf("%d\n", BUTTON_GetButtonsEvents());
	}
}

int main(void) {
	init_peripherals();
	xTaskCreate(Buttons_Action, "Action", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	vTaskStartScheduler();
	return 0 ;
}*/



