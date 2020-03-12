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

void *request_change_menu(void *origen(), void *destiny()){
	if(count==0)
		count=wait_elapsed(count);
	if((wait_elapsed(0)/PRESSING_TIME)%2>0)
		turn_on_led();
	else
		turn_off_led();
	if(wait_elapsed(count)>=TWO_SECONDS){
		count=0;
		while(button_map!=NOT_PRESSED){
			if((wait_elapsed(0)/RELEASE_TIME)%2>0)turn_on_led();
			else turn_off_led();
			button_map=BUTTON_GetButtonsEvents();
		}
		turn_off_led();
		LCDText_Clear();
		return destiny;
	}
	return origen;
}
