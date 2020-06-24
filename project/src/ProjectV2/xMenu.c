/**
* @file		menu.h
* @brief	Contains the Menu functions.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#include "menu.h"
#include "menu_normal.h"

uint32_t count;
int button_map;
DATA_TYPEDEF *local_data;

void *request_change_menu(void *origen(), void *destiny()){
	if(count==0)
		count=wait_elapsed(count);
	if((wait_elapsed(0)/PRESSING_TIME)%2>0)
		turn_on_led();
	else
		turn_off_led();
	if(wait_elapsed(count)>=TWO_SECONDS){
		if(((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0) && (((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0)){
			count=0;
			turn_off_led();
			return destiny;
		}
		if((wait_elapsed(0)/RELEASE_TIME)%2>0)
			turn_on_led();
		else
			turn_off_led();
	}
	return origen;
}
