#include <stdio.h>
#include <stdbool.h>

/* Kernel includes. */
#include "FreeRTOS.h"

/* Kernel includes. */
#include "queue.h"
#include "task.h"
#include "event_groups.h"
#include "LPC17xx.h"
#include "peripherals.h"

QueueHandle_t Button_Queue;


void Button_Interrupt_Handler(void){
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken=pdTRUE;
	int b=BUTTON_GetButtonsEvents();
	xQueueSendFromISR(Button_Queue, &b, &xHigherPriorityTaskWoken);
}

void Buttons_Action(){
	Button_Queue= xQueueCreate(1, sizeof(int));
	bool fix=false;
	int y=0;
	BaseType_t result;
	while(1){
		if(fix)
			result=xQueueReceive(Button_Queue, &y, 0);
		else
			result=xQueueReceive(Button_Queue, &y, portMAX_DELAY);
		if(result == errQUEUE_EMPTY && fix){
			printf("%d\n", BUTTON_GetButtonsEvents());
			fix=false;
			printf("----\n");
		}
		else if(result==pdPASS){
			printf("%d\n", y);
			fix=true;
		}
	}
}

int main(void) {
	//init_peripherals();
	init_BUTTON();
	//init_wait();
	//wait_ms(1000);
	xTaskCreate(Buttons_Action, "Action", configMINIMAL_STACK_SIZE*2, NULL, 1, NULL );
	vTaskStartScheduler();
	return 0 ;
}

/*QueueHandle_t LED_Queue;
void LED_Action(){
	int j=0;
	while(1){
		if(xQueueReceive(LED_Queue, &j, portMAX_DELAY)){
			if(j%2==0)
				turn_on_led();
			else
				turn_off_led();
		}
	}
}

void LED_Process(){
	init_led();
	LED_Queue= xQueueCreate(30, sizeof(int));
	int i=0;
	while(1){
		xQueueSendToBack(LED_Queue, i, 0);
		vTaskDelay( pdMS_TO_TICKS(500));
		i++;
	}
}

int main(void) {
	xTaskCreate(LED_Action, "Action", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(LED_Process, "Process", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	vTaskStartScheduler();
	return 0;
}*/

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
	/* This function will get called if a task overflows its stack. */

	(void) pxTask;
	(void) pcTaskName;

	for (;;)
		;
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void vConfigureTimerForRunTimeStats(void) {
	const unsigned long TCR_COUNT_RESET = 2, CTCR_CTM_TIMER = 0x00,
			TCR_COUNT_ENABLE = 0x01;

	/* This function configures a timer that is used as the time base when
	 collecting run time statistical information - basically the percentage
	 of CPU time that each task is utilising.  It is called automatically when
	 the scheduler is started (assuming configGENERATE_RUN_TIME_STATS is set
	 to 1). */

	/* Power up and feed the timer. */
	LPC_SC->PCONP |= (1 << 2);
	LPC_SC->PCLKSEL0 = (LPC_SC->PCLKSEL0 & (~(0x3 << 4))) | (0x01 << 4);

	/* Reset Timer 1 */
	LPC_TIM1->TCR = TCR_COUNT_RESET;

	/* Just count up. */
	LPC_TIM1->CTCR = CTCR_CTM_TIMER;

	/* Prescale to a frequency that is good enough to get a decent resolution,
	 but not too fast so as to overflow all the time. */
	LPC_TIM1->PR = ( configCPU_CLOCK_HZ / 10000UL) - 1UL;

	/* Start the counter. */
	LPC_TIM1->TCR = TCR_COUNT_ENABLE;
}
/*-----------------------------------------------------------*/

