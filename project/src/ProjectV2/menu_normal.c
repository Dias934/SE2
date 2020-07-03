/**
* @file		menu_normal.c
* @brief	Contains the Menu Normal functions.
* @version	1.1
* @date		4 Out 2019
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#include "menu_normal.h"

void * normal_execution(){
	view_normal(local_data);
	//checks if the up and down button are on the state pressed/pressing (the first bit is 1 if its pressed/pressing, check states)
	//OR in case count is GE than 2 sec, it means the user wants to change menu
	if( wait_elapsed(count)>=TWO_SECONDS || (((button_map&PRESSED)>0) && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0)))
		return request_change_menu(&normal_execution, &start_select_maintenance);
	else{
		turn_off_led();
		count=0;
	}
	return &normal_execution;
}
