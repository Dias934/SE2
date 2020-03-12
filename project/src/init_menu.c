/*
 * init_menu.c
 *
 *  Created on: 11/03/2020
 *      Author: A38866
 */

#include "init_menu.h"

static int idx=0;

void init_sensors(){
	int ret=ret=init_bmp280();
	if(ret==0){
		idx++;
		view_init_result("OK");
	}
	else{
		view_init_result("BMP280 not found");
		return;
	}
}

void init_data(){
	int ret=init_data_manager();
	if(ret==0){
		idx++;
		view_init_result("OK");
	}
	else{
		view_init_result("Sector not found");
		return;
	}
}

static void (*select_inits[])()={init_sensors, init_data};

void *start_inits(){
	init_peripherals();
	view_init(0);
	wait_ms(ONE_SECOND);
	view_init_result("OK");
	wait_ms(ONE_SECOND);
	return &init_menu;
}

void *init_menu(){
	view_init(idx+1);
	wait_ms(ONE_SECOND);
	select_inits[idx]();
	wait_ms(ONE_SECOND);
	if(idx>=2)
		return &normal_execution;
	else
		return &init_menu;
}
