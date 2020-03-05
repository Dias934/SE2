/**
* @file		menu.h
* @brief	Contains the Menu functions.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef MENU_H_
#define MENU_H_

#include "peripherals.h"
#include "view.h"
/** @defgroup MENU Menu
 * This package provides the core capability of Menu.
 * @{
 */
/** @defgroup MENU_Public_Constants Menu Public Constants
 * @{
*/
/**
 * @brief 1s = 1000 milisec
 */
#define ONE_SECOND 1000
/**
 * @brief 2s = 2000 milisec
 */
#define TWO_SECONDS 2000
/**
 * @brief pressing time value
 */
#define PRESSING_TIME 250
/**
 * @brief release time value
 */
#define RELEASE_TIME 100
/**
 * @}
 * @defgroup MENU_Public_VARIABLES Menu Public Variables
 * @{
 * @brief keep track of time up to 2 seconds
 */
extern uint32_t count;

/**
 * @brief stores the map of the buttons
 */
extern int button_map;


/**
 * @}
 * @defgroup MENU_Public_Functions Menu Public Functions
 * @{
 */
/**
 * @brief initialize menu
 * @note must be called first
 */
void *init_menu();
/**
 * @brief manage the up and down button function time. If up and down button are pressed
 *
 */
void *up_and_down_pressed(void *origen(), void *destiny(), void (*led_state)());
/**
 * @}
 * @}
 */
#endif /* MENU_H_ */
