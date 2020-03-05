/**
* @file		view.h
* @brief	Contains the View functions.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/
#ifndef VIEW_H_
#define VIEW_H_

#include "data_storage.h"
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
void view_normal();
/**
 * @ maintenance mode view
 */
void view_maintenance(short idx);
/**
 * @ change time view
 */
void view_change_time();
/**
 * @ change date view
 */
void view_change_date();
/**
 * @ change temperature view
 */
void view_change_temperature_units();
/**
 * @}
 * @}
 */
#endif /* VIEW_H_ */
