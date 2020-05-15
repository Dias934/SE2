/**
* @file		menu_maintenance.c
* @brief	Contains the Menu Maintenance source.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/
#include "menu_maintenance.h"




/**
 * @ingroup MENU_MAINTENANCE_STATIC_VARIABLES
 * @{
 * @brief keep track of time passed up to 10 seconds if no button is pressed
 */

uint32_t count_10;

short field;

short divider=1;

uint32_t count_pressing;


void * general_maintenance_actions(void * execute_maintenance, void * exit_maintenance){
	button_map=BUTTON_GetButtonsEvents();
	if(!(((button_map&PRESSED)>0) || (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0) || (((button_map>>ENTER_BUTTON_POSITION)&PRESSED)>0))){//checks if no buttons are pressed/pressing
		if(count_10==0)
			count_10=wait_elapsed(count_10);
		else if(wait_elapsed(count_10)>TEN_SECONDS){
			count_10=0;
			LCDText_Clear();
			return &normal_execution;
		}
	}
	else
		count_10=0;
	if(((button_map&PRESSED)>0) && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0)) //checks if the up and down button are on the state pressed/pressing
		return request_change_menu(execute_maintenance, exit_maintenance);
	else{
		turn_off_led();
		count=0;
	}
	return execute_maintenance;
}
