/**
* @file		ui.h
* @brief	Contains the User Interface functionalities.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef UI_H_
#define UI_H_

#include <led.h>
#include <button.h>
#include <lcd.h>

/** @defgroup UI UI
 * This package provides the User Interface contact with the hardware.
 * @{
 */
/** @defgroup UI_Public_Functions UI Public Functions
 * @{
 */

/**
 * @brief	Initializes UI control
 * @return	Nothing
 * @note	This function must be called first to interact with the hardware.
 */
void init_ui(void);

/**
 * @}
 */

/**
 * @}
 */

#endif /* UI_H_ */
