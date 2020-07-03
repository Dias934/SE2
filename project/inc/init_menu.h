/*
 * init_menu.h
 *
 *  Created on: 11/03/2020
 *      Author: A38866
 */

#ifndef INIT_MENU_H_
#define INIT_MENU_H_

#include "menu.h"
#include "menu_normal.h"

enum INIT_IDX{
	INIT_PERIPHERALS=0,
	INIT_BMP280,
	INIT_E2PROM,
	INIT_END
};

#define ALL_INITIALIZED 	0x7

#define TEST_E2PROM_ADDR 	0

bool init_menu(short idx);

#endif /* INIT_MENU_H_ */
