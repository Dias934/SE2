/**
* @file		menu_normal.c
* @brief	Contains the Menu Normal functions.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#include "menu_normal.h"

void * normal_execution(){
	view_normal();
	button_map=BUTTON_GetButtonsEvents();
	if(((button_map&PRESSED)>0) && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0)) //checks if the up and down button are on the state pressed/pressing (the first bit is 1 if its pressed/pressing, check states)
		return up_and_down_pressed(&normal_execution, &maintenance_execution, &turn_on_led);
	else{
		turn_off_led();
		count=0;
	}
	return &normal_execution;
}
