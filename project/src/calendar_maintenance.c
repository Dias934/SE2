/*
 * calendar_maintenance.c
 *
 *  Created on: 11/03/2020
 *      Author: A38866
 */

#include "calendar_maintenance.h"

struct tm aux_cal;

static void* execute_calendar_maintenance();

int* aux_cal_flds_pts[3]={&(aux_cal.tm_year), &(aux_cal.tm_mon), &(aux_cal.tm_mday)};

static const int MAX_FLDS[2]={MAX_YEAR, MAX_MONTH};

void * start_calendar_maintenance(){
	field=0;
	get_cur_time(&aux_cal);
	view_calendar_maintenance(field, &aux_cal);
	return calendar_maintenance();
}

void * calendar_maintenance(){
	void *(*buttons_reaction)()=general_maintenance_actions(&execute_calendar_maintenance,&start_select_maintenance);
	return buttons_reaction();
}

void inc_calendar_flds(int dir){
	if(count_pressing==0){
		*(aux_cal_flds_pts[field])+=1*dir;
		if(field<2){
			if((*(aux_cal_flds_pts[field]))<0)
				*(aux_cal_flds_pts[field])=MAX_FLDS[field]-1;
			*(aux_cal_flds_pts[field])=(*(aux_cal_flds_pts[field]))%MAX_FLDS[field];
		}
		else{
			int max=MAX_DAYS_MAP[aux_cal.tm_mon];
			if(aux_cal.tm_mon==FEBRUARY && aux_cal.tm_year%4==0)
				max++;
			if((*(aux_cal_flds_pts[field]))<=0)
				*(aux_cal_flds_pts[field])=max;
			else if((*(aux_cal_flds_pts[field]))>max)
				*(aux_cal_flds_pts[field])=1;
		}
		count_pressing=wait_elapsed(count_pressing);
	}
	if(wait_elapsed(count_pressing)>(HALF_SECOND/divider)){
		count_pressing=0;
		divider++;
	}
	view_calendar_maintenance(field, &aux_cal);
}

void* execute_calendar_maintenance(){
	if(((button_map>>UP_BUTTON_POSITION)&PRESSING) && (((button_map>>DOWN_BUTTON_POSITION)&PRESSING)==0) && (((button_map>>ENTER_BUTTON_POSITION)&PRESSING)==0))
		inc_calendar_flds(1);
	else if(((button_map>>DOWN_BUTTON_POSITION)&PRESSING) && ((button_map>>UP_BUTTON_POSITION)&PRESSING)==0 && ((button_map>>ENTER_BUTTON_POSITION)&PRESSING)==0)
		inc_calendar_flds(-1);
	else if(((button_map>>ENTER_BUTTON_POSITION)&PRESSING)==PRESSED && ((button_map>>UP_BUTTON_POSITION)&PRESSING)==0 && ((button_map>>DOWN_BUTTON_POSITION)&PRESSING)==0){
		view_calendar_maintenance(++field, &aux_cal);
		if(field>2){
			set_time(&aux_cal);
			return &start_select_maintenance;
		}
	}
	else{
		count_pressing=0;
		divider=1;
	}
	return &calendar_maintenance;
}
