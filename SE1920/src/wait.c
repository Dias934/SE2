/*
 * wait.c
 *
 *  Created on: 01/10/2019
 *      Author: A38866
 */
#include <wait.h>

static uint32_t __ms=0;

void init_wait(void){
	SysTick_Config(SystemCoreClock/MILLISECONDS_DIVISION);
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
	uint32_t start=__ms;
	while((__ms-start)<millis);
}

uint32_t wait_elapsed(uint32_t time){
	if(time==0) return __ms;
	return __ms-time;
}

void wait_ChronoUs(uint32_t waitUs){
	LPC_TIM0->MR0=waitUs;
	LPC_TIM0->TCR=1;
	while(((LPC_TIM0->IR)&MR0_INTERRUPT)!=1);
	LPC_TIM0->TCR=(1<<RESET_STOPWATCH);
	LPC_TIM0->IR=1;
}

void SysTick_Handler(void){
	++__ms;
}
