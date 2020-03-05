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
 * @ingroup MENU_MAINTENANCE_STATIC_FUNCTIONS
 * @{
 *
 *@brief read the current button state and executes an action
 */
static void maintenance_buttons_interaction();

/**
 * @brief executes an action after only the up button is pressed while in select mode
 */
static void select_up_pressed(short value);

/**
 * @brief executes an action after only the down button is pressed while in select mode
 */
static void select_down_pressed(short value);

/**
 * @brief executes an action after only the enter button is pressed while in select mode
 */
static void select_enter_pressed();

/**
 * @brief executes an action after the up xor down button are pressed while in maintenance mode and time was selected
 */
static void time_up_down_pressed(short value);

/**
 * @brief executes an action after the enter button is pressed while in in maintenance mode and time was selected
 */
static void time_enter_pressed();

/**
 * @brief executes an action after the up xor down button is pressed while in in maintenance mode and date was selected
 */
static void date_up_down_pressed(short value);

/**
 * @brief executes an action after the enter button is pressed while in in maintenance mode and date was selected
 */
static void date_enter_pressed();

/**
 * @brief executes an action after the up xor down button is pressed while in in maintenance mode and temperature unit was selected
 */
static void temp_up_down_pressed(short value);

/**
 * @brief executes an action after the enter button is pressed while in in maintenance mode and temperature unit was selected
 */
static void temp_enter_pressed();

/**
 * @brief executes the select mode
 */
static void select_field();

/**
 * @brief executes the maintenance mode to change time
 */
static void maintenance_change_time();

/**
 * @brief executes the maintenance mode to change date
 */
static void maintenance_change_date();

/**
 * @brief executes the maintenance mode to change temperature unit
 */
static void maintenance_change_temperature_units();

/**
 * @}
 * @ingroup MENU_MAINTENANCE_STATIC_CONSTANTS
 * @{
 * @brief array of function pointers to select which view was selected
 */
void (*view[3])()={view_change_time, view_change_date, view_change_temperature_units};

/**
 * @brief array of function pointers to select which mode is to be called to execute maintenance
 */
void (*mode[4])()={select_field, maintenance_change_time, maintenance_change_date, maintenance_change_temperature_units};

/**
 * @brief array of function pointers to be called when enter button is pressed in the current mode
 */
void (*enter_funcs[])()={select_enter_pressed, time_enter_pressed, date_enter_pressed, temp_enter_pressed};

/**
 * @brief array of function pointers to be called when up xor button button is pressed in the current mode
 */
void (*up_down_func[])(short value)={select_up_pressed, select_down_pressed, time_up_down_pressed, date_up_down_pressed, temp_up_down_pressed};

/**
 * @}
 * @ingroup MENU_MAINTENANCE_STATIC_VARIABLES
 * @{
 * @brief keep track of time passed up to 10 seconds if no button is pressed
 */
uint32_t count_10;

/**
 * @brief count how long is the button pressed to delay the execution of the command
 */
uint32_t count_pressing_button;

/**
 * @brief count how long is the button pressed to increased the incremented value of the fields
 */
uint32_t count_continuos_pressing;

/**
 * @brief the current view index
 */
short view_idx=0;

/**
 * @brief the current mode index
 */
short mode_idx=0;
/**
 * @}
 */

void * maintenance_execution(){
	button_map=BUTTON_GetButtonsEvents();
	if(!(((button_map&PRESSED)>0) || (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0) || (((button_map>>ENTER_BUTTON_POSITION)&PRESSED)>0))){//checks if no buttons are pressed/pressing
		if(count_10==0)
			count_10=wait_elapsed(count_10);
		if(wait_elapsed(count_10)>TEN_SECONDS){
			mode_idx=0;
			count_10=0;
			turn_off_led();
			LCDText_Cursor(CURSOR_OFF);
			LCDText_Clear();
			return &normal_execution;
		}
	}
	else
		count_10=0;
	if(((button_map&PRESSED)>0) && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0)){ //checks if the up and down button are on the state pressed/pressing
		if(count!=0 && wait_elapsed(count)>=TWO_SECONDS){
			mode_idx=0;
			LCDText_Cursor(CURSOR_OFF);
		}
		return up_and_down_pressed(&maintenance_execution, &normal_execution, &turn_off_led);
	}
	else{
		turn_on_led();
		count=0;
	}
	(*mode[mode_idx%4])();
	return &maintenance_execution; //checks if no button is pressed for 10 seconds to change to normal menu. If not returns maintenance menu
}

void maintenance_buttons_interaction(){
	if(((button_map>>ENTER_BUTTON_POSITION)&PRESSED)>0){
		if(count_continuos_pressing==0)
					count_continuos_pressing=wait_elapsed(count_continuos_pressing);
		(*enter_funcs[mode_idx])();
	}
	else if(((button_map&PRESSED)>0) && !(((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0)){
		if(count_continuos_pressing==0)
					count_continuos_pressing=wait_elapsed(count_continuos_pressing);
		(*up_down_func[2*mode_idx-(  (view_idx*mode_idx/2)%2  )*view_idx])(1);
	}
	else if(!((button_map&PRESSED)>0) && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)>0)){
		if(count_continuos_pressing==0)
					count_continuos_pressing=wait_elapsed(count_continuos_pressing);
		(*up_down_func[2*mode_idx+1-mode_idx])(-1);
	}
	else{
		count_continuos_pressing=0;
	}
}

void select_up_pressed(short value){
	if(!((button_map&PRESSING)==PRESSING)){
		LCDText_Clear();
		view_idx=(view_idx+value)%3;
	}
}

void select_down_pressed(short value){
	if(!((button_map>>DOWN_BUTTON_POSITION&PRESSING)==PRESSING)){
		LCDText_Clear();
		view_idx+=value;
		if(view_idx<0) view_idx=2;
	}
}

void select_enter_pressed(){
	while(button_map!=NOT_PRESSED)
		button_map=BUTTON_GetButtonsEvents();
	LCDText_Cursor(CURSOR_ON);
	mode_idx=view_idx+1;
}

void select_field(){
	backup_dateTime();
	(*view[view_idx%3])();
	maintenance_buttons_interaction();
}

void time_up_down_pressed(short value){
	if(count_pressing_button==0)
		count_pressing_button=wait_elapsed(count_pressing_button);
	if(wait_elapsed(count_pressing_button)>150){
		change_time(value*(wait_elapsed(count_continuos_pressing)/ONE_SECOND+1));
		count_pressing_button=0;
		(*view[view_idx%3])();
	}
}

void time_enter_pressed(){
	while(button_map!=NOT_PRESSED)
		button_map=BUTTON_GetButtonsEvents();
	if(nextField(TIME_FIELDS)==0){
		send_time();
		LCDText_Clear();
		LCDText_Cursor(CURSOR_OFF);
		mode_idx=0;
	}
	(*view[view_idx%3])();
}

void date_up_down_pressed(short value){
	if(count_pressing_button==0)
		count_pressing_button=wait_elapsed(count_pressing_button);
	if(wait_elapsed(count_pressing_button)>150){
		change_date(value*(wait_elapsed(count_continuos_pressing)/ONE_SECOND+1));
		count_pressing_button=0;
		(*view[view_idx%3])();
	}
}

void date_enter_pressed(){
	while(button_map!=NOT_PRESSED)
		button_map=BUTTON_GetButtonsEvents();
	if(nextField(DATE_FIELDS)==0){
		send_date();
		LCDText_Clear();
		LCDText_Cursor(CURSOR_OFF);
		mode_idx=0;
	}
	(*view[view_idx%3])();
}

void temp_up_down_pressed(short value){
	if(count_pressing_button==0)
			count_pressing_button=wait_elapsed(count_pressing_button);
	if(wait_elapsed(count_pressing_button)>150){
		change_temp_unit(value);
		count_pressing_button=0;
		(*view[view_idx%3])();
	}
}

void temp_enter_pressed(){
	while(button_map!=NOT_PRESSED)
		button_map=BUTTON_GetButtonsEvents();
	send_temp_unit();
	LCDText_Clear();
	LCDText_Cursor(CURSOR_OFF);
	mode_idx=0;
}

void maintenance_change_time(){
	LCDText_Locate(1,get_CurrentField()*3+1);
	LCDText_Cursor(CURSOR_ON);
	maintenance_buttons_interaction();
}

void maintenance_change_date(){
	LCDText_Locate(1,9-get_CurrentField()*5+2*(get_CurrentField()/2));
	LCDText_Cursor(CURSOR_ON);
	maintenance_buttons_interaction();
}

void maintenance_change_temperature_units(){
	LCDText_Locate(1,0);
	maintenance_buttons_interaction();
}
