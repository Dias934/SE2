/*
 * data_manager.c
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#include "data_center.h"
#include "FreeRTOS.h"

static const int ID=0xFA5A5A5F;

static unsigned short unit_idx=0;

static double celsius_to_far();

static double celsius();

static double (*temperature_funcs[])()={celsius, celsius_to_far};

static bool sensor_state;

static double temperature;

static double pressure;

bool init_data_center(){
	return true;
}

short get_temperature_unit(){
	return unit_idx;
}

double get_temperature(){
	int ret=measure();
	if(ret==TRANSF_ERROR)
		return NOT_OK;
	return temperature_funcs[unit_idx]();
}

static double celsius_to_far(){
	return current_temp*9/5 + 32;
}

static double celsius(){
	return current_temp;
}

double get_pressure(){
	return current_press;
}

void set_unit(short unit){
	unit_idx=unit;
}

/*

bool init_data_manager(){

	return true;
}

void get_cur_time(struct tm *calendar){
	RTC_GetValue(calendar);
}

void set_time(struct tm *calendar){
	RTC_SetMaskedValue(calendar, TIME_MASK);
}

void set_calendar(struct tm *calendar){
	RTC_SetMaskedValue(calendar, CALENDAR_MASK);
}

short get_temperature_unit(){
	return unit_idx;
}

double get_temperature(){
	int ret=measure();
	if(ret==TRANSF_ERROR)
		return NOT_OK;
	return temperature_funcs[unit_idx]();
}

static double celsius_to_far(){
	return current_temp*9/5 + 32;
}

static double celsius(){
	return current_temp;
}

double get_pressure(){
	return current_press;
}

void set_unit(short unit){
	unit_idx=unit;
}

void save_temperature_unit(){
	writeToFlash(&unit_idx,sizeof(unit_idx));
}

void undo_set_unit(){
	readFromFlash(&unit_idx);
}*/
