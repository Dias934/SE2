/*
 * init_menu.c
 *
 *  Created on: 11/03/2020
 *      Author: A38866
 */

#include "init_menu.h"

static int idx=0;

const static short size=3;

static char * INITS[3]={"Peripherals","BMP280","Data Manager"};

void menu_init_TempSensor(){
	int ret=init_bmp280();
	if(ret==0){
		idx++;
		view_init_result("OK");
	}
	else{
		view_init_result("BMP280 not found");
		return;
	}
}

void menu_init_data(){
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

void menu_init_peripherals(){
	idx++;
	view_init_result("OK");
}

static void (*select_inits[])()={menu_init_peripherals, menu_init_TempSensor, menu_init_data};

void *start_inits(){
	init_peripherals();
	return &init_menu;
}

void *init_menu(){
	view_init(INITS[idx]);
	wait_ms(ONE_SECOND);
	select_inits[idx]();
	wait_ms(ONE_SECOND);
	if(idx>=size)
		return &normal_execution;
	else
		return &init_menu;
}
