/*
 * init_menu.c
 *
 *  Created on: 11/03/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "init_menu.h"

static char * INITS[]={"Peripherals", "BMP280", "Data Manager"};

static short initialized=0;

bool menu_init_TempSensor(){
	bool ret=init_bmp280();
	if(ret){
		view_init_result("OK");
		initialized |= 1<<INIT_BMP280;
	}
	else{
		view_init_result("BMP280 not found");
		initialized &= ~(1<<INIT_BMP280);
	}
	return ret;
}

bool menu_init_data(){
	view_init_result("OK");
	initialized |= 1<<INIT_E2PROM;
	return true;
}

bool menu_init_peripherals(){
	view_init_result("OK");
	initialized |= 1<<INIT_PERIPHERALS;
	return true;
}

static bool (*select_inits[])()={menu_init_peripherals, menu_init_TempSensor, menu_init_data};

bool init_menu(short idx){
	view_init(INITS[idx]);
	wait_ms(HALF_SECOND);
	bool ret= select_inits[idx]();
	wait_ms(HALF_SECOND);
	return ret;
}
