/*
 * peripherals.c
 *
 *  Created on: 09/03/2020
 *      Author: A38866
 */

#include "peripherals.h"


void init_peripherals(){
	init_wait();
	init_RTC(0);
	init_LCDText();
	init_led();
	init_BUTTON();
	init_spi();
}
