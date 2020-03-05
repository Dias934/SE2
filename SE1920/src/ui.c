/*
 * ui.c
 *
 *  Created on: 01/10/2019
 *      Author: A38866
 */

#include <ui.h>


void init_ui(void){
	init_LCDText();
	init_led();
	init_BUTTON();
}
