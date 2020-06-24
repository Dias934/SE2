/*
 * time_maintenance.c
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#include "time_maintenance.h"

struct tm aux_time;

static void* execute_time_maintenance();

int* aux_time_flds_pts[2]={&(aux_time.tm_hour), &(aux_time.tm_min)};

static const int MAX_FLDS[2]={MAX_HOUR, MAX_MIN};

void * start_time_maintenance(){
	field=0;
	get_cur_time(&aux_time);
	view_time_maintenance(field, &aux_time);
	return &time_maintenance;
}

void * time_maintenance(){
	void *(*buttons_reaction)()=general_maintenance_actions(&execute_time_maintenance,&start_select_maintenance);
	return buttons_reaction();
}

void inc_time_flds(int dir){
	view_time_maintenance(field, &aux_time);
	if(count_pressing==0){
		*(aux_time_flds_pts[field])+=1*dir;
		if((*(aux_time_flds_pts[field]))<0)
			*(aux_time_flds_pts[field])=MAX_FLDS[field]-1;
		*(aux_time_flds_pts[field])=(*(aux_time_flds_pts[field]))%MAX_FLDS[field];
		count_pressing=wait_elapsed(count_pressing);
	}
	if(wait_elapsed(count_pressing)>(HALF_SECOND/divider)){
		count_pressing=0;
		divider++;
	}
}

void* execute_time_maintenance(){
	if(((button_map>>UP_BUTTON_POSITION)&PRESSING)==PRESSED && (((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0) && (((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0))
		inc_time_flds(1);
	else if(((button_map>>DOWN_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && ((button_map>>ENTER_BUTTON_POSITION)&PRESSED)==0)
		inc_time_flds(-1);
	else if(((button_map>>ENTER_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSED)==0 && ((button_map>>DOWN_BUTTON_POSITION)&PRESSED)==0){
		view_time_maintenance(++field, &aux_time);
		if(field>1){
			set_time(&aux_time);
			return &start_select_maintenance;
		}
	}
	else{
		count_pressing=0;
		divider=1;
	}
	return &time_maintenance;
}


