/*
 * temperature_unit_maintenance.c
 *
 *  Created on: 12/03/2020
 *      Author: A38866
 */

#include "temperature_unit_maintenance.h"
#include "ProjectTasks/data_center_task.h"

static short aux_unit;

static void* execute_temperature_unit_maintenance();

static const short MAX_UNITS=2;

void * start_temperature_unit_maintenance(){
	aux_unit=local_data.unit;
	view_temperature_unit_maintenance(aux_unit);
	return &temperature_unit_maintenance;
}

void * temperature_unit_maintenance(){
	void *(*buttons_reaction)()=general_maintenance_actions(&execute_temperature_unit_maintenance, &start_select_maintenance);
	return buttons_reaction();
}

void inc_temp_fld(int dir){
	aux_unit+=dir;
	if(aux_unit<0)
		aux_unit=MAX_UNITS-1;
	else
		aux_unit=aux_unit%MAX_UNITS;
	view_temperature_unit_maintenance(aux_unit);
}

void* execute_temperature_unit_maintenance(){
	if(((button_map>>UP_BUTTON_POSITION)&PRESSING)==PRESSED && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0) && (((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0))
		inc_temp_fld(1);
	else if(((button_map>>DOWN_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && ((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0)
		inc_temp_fld(-1);
	else if(((button_map>>ENTER_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && ((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0){
		send_new_temperature_unit(aux_unit);
		return &start_select_maintenance;
	}
	else{
		count_pressing=0;
		divider=1;
	}
	return &temperature_unit_maintenance;
}
