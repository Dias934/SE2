/*
 * led.c
 *
 *  Created on: 01/10/2019
 *      Author: A38866
 */

#include <led.h>

static int led_state=0;

void init_led(){
	LPC_GPIO0->FIODIR|=(1<<LED_PIN);
	turn_off_led();
}

void turn_on_led(){
	LPC_GPIO0->FIOSET=(1<<LED_PIN);
	led_state=1;
}

void turn_off_led(){
	LPC_GPIO0->FIOCLR=(1<<LED_PIN);
	led_state=0;
}

int led_get_state(){
	return led_state;
}
