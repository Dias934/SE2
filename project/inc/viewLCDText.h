/*
 * viewLCDText.h
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#ifndef VIEWLCDTEXT_H_
#define VIEWLCDTEXT_H_

#include "data_center.h"
#include "lcd.h"

/** @defgroup VIEW View
 * This package provides the core capability of View.
 * @{
 */
/** @defgroup VIEW_Public_FUNCTIONS View Public Functions
 * @{
*/

enum MAINT_VIEW_IDX{
	TIME_MAINT=0,
	CAL_MAINT,
	TEMP_UNIT_MAINT
};


/**
 * @ normal mode view
 */
void view_init(char * s);
void view_init_result(char * s);
void view_normal(DATA_TYPEDEF data);
/**
 * @ maintenance mode view
 */
void view_select_maintenance(short idx, DATA_TYPEDEF data);
/**
 * @ change time view
 */
void view_time_maintenance(short field, struct tm calendar);

void view_calendar_maintenance(short field, struct tm calendar);

void view_temperature_unit_maintenance(unsigned short unit);
/**
 * @}
 * @}
 */

#endif /* VIEWLCDTEXT_H_ */
