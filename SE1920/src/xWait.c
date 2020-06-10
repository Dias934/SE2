/*
 * xWait.h
 *
 *  Created on: 04/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "FreeRTOS.h"
#include "task.h"

#include "wait.h"


void init_wait(void){
	//SysTick_Config(SystemCoreClock/MILLISECONDS_DIVISION);
	LPC_SC->PCLKSEL0=(CCLK_FREQ<<TIMER0_CLK);
	LPC_TIM0->CTCR=TIMER_MODE;
	LPC_TIM0->TCR=(1<<RESET_STOPWATCH);
	LPC_TIM0->MCR=(1<<MR0S) | (1<<MR0I);
	LPC_TIM0->PR=SystemCoreClock/MICROSECONDS_DIVISION;
}

void wait_hz(int frequency){
	uint32_t conv_ms=((double)1/frequency)*1000;
	wait_ms(conv_ms);
}

void wait_ms(int millis){
	vTaskDelay(pdMS_TO_TICKS(millis));
}

uint32_t wait_elapsed(uint32_t time){
	if(time==0) return xTaskGetTickCount();
	return xTaskGetTickCount()-time;
}

void wait_ChronoUs(uint32_t waitUs){
	LPC_TIM0->MR0=waitUs;
	LPC_TIM0->TCR=1;
	while(((LPC_TIM0->IR)&MR0_INTERRUPT)!=1);
	LPC_TIM0->TCR=(1<<RESET_STOPWATCH);
	LPC_TIM0->IR=1;
}
