/*
 * peripherals.c
 *
 *  Created on: 22/10/2019
 *      Author: A38866
 */

#include "peripherals.h"

void init_peripherals(){
	init_wait();
	init_RTC(0);
	init_ui();
	init_spi();
}
