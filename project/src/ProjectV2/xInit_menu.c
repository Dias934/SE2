/*
 * init_menu.c
 *
 *  Created on: 11/03/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "init_menu.h"

static char * INITS[]={"Peripherals", "BMP280", "E2PROM"};

static short initialized=0;

bool menu_init_TempSensor(){
	bool ret=init_bmp280();
	if(ret)
		initialized |= 1<<INIT_BMP280;
	else
		initialized &= ~(1<<INIT_BMP280);
	return ret;
}

bool menu_init_e2prom(){
	bool ret=init_24AA256(TEST_E2PROM_ADDR);
	if(ret)
		initialized |= 1<<INIT_E2PROM;
	else
		initialized &= ~(1<<INIT_E2PROM);
	return ret;
}

bool menu_init_peripherals(){
	initialized |= 1<<INIT_PERIPHERALS;
	return true;
}

static bool (*select_inits[])()={menu_init_peripherals, menu_init_TempSensor, menu_init_e2prom};

bool init_menu(short idx){
	if(idx!= INIT_END)
		return select_inits[idx]();
	return idx==INIT_END && initialized==ALL_INITIALIZED;
}
