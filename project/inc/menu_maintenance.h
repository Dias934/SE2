/**
* @file		menu_maintenance.h
* @brief	Contains the Menu Maintenance functions.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/
#ifndef MENU_MAINTENANCE_H_
#define MENU_MAINTENANCE_H_

#include "menu_normal.h"
#include "viewLCDText.h"

/** @defgroup MENU_MAINTENANCE Menu Maintenance
 * This package provides the core capability of Menu Maintenance mode.
 * @{
 */
/** @defgroup MENU_MAINTENANCE_Public_Constants Menu Maintenance Public Constants
 * @{
*/
/**
 * @brief 10s=10000 milisec
 */
#define TEN_SECONDS 10000

#define HALF_SECOND 500
/**
 * @}
 */
/** @defgroup MENU_MAINTENANCE_Public_Function Menu Maintenance Public Function
 * @{
*/
/**
 * @return returns a pointer to a maintenance function
 */

extern uint32_t count_10;
extern short field;

extern short divider;

extern uint32_t count_pressing;

void * general_maintenance_actions(void * execute_maintenance, void * exit_maintenance);
/**
 * @}
 *
 * @defgroup MENU_MAINTENANCE_STATIC_FUNCTIONS Menu Maintenance Static Functions
 * @defgroup MENU_MAINTENANCE_STATIC_VARIABLES Menu Maintenance Static Variables
 * @defgroup MENU_MAINTENANCE_STATIC_CONTANTS Menu Maintenance Static Constants
 * @}
 */
#endif /* MENU_MAINTENANCE_H_ */
