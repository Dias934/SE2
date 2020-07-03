/*
 * select_maintenance.c
 *
 *  Created on: 11/03/2020
 *      Author: A38866
 */

#include "select_maintenance.h"

static void *execute_select();

static short idx=0;

static short nr_funcs=3;

static void *(*select_funcs[])()={start_time_maintenance, start_calendar_maintenance, start_temperature_unit_maintenance};

void * start_select_maintenance(){
	view_select_maintenance(idx, local_data);
	return &select_maintenance;
}

void * select_maintenance(){
	void *(*execute)()=general_maintenance_actions(&execute_select, &normal_execution);
	return execute();
}

void * execute_select(){
	if(((button_map>>UP_BUTTON_POSITION)&PRESSING)==PRESSED && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0) && (((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0)){
		idx=(idx+1)%nr_funcs;
		view_select_maintenance(idx, local_data);
	}
	else if(((button_map>>DOWN_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && ((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0){
		if(idx==0)
			idx=nr_funcs-1;
		else
			idx--;
		view_select_maintenance(idx, local_data);
	}
	else if(((button_map>>ENTER_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && ((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0)
		return select_funcs[idx];
	return &select_maintenance;
}
