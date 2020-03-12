/*
 * viewLCDText.h
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#ifndef VIEWLCDTEXT_H_
#define VIEWLCDTEXT_H_

#include "data_manager.h"
#include "lcd.h"

/** @defgroup VIEW View
 * This package provides the core capability of View.
 * @{
 */
/** @defgroup VIEW_Public_FUNCTIONS View Public Functions
 * @{
*/
/**
 * @ normal mode view
 */
void view_init(short idx);
void view_init_result(char * s);
void view_normal();
/**
 * @ maintenance mode view
 */
void view_select_maintenance(short idx);
/**
 * @ change time view
 */
void view_time_maintenance(short field, struct tm *calendar);

void view_calendar_maintenance(short field, struct tm *calendar);

void view_temperature_unit_maintenance();
/**
 * @}
 * @}
 */

#endif /* VIEWLCDTEXT_H_ */
