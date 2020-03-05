/**
* @file		button.h
* @brief	Contains the buttons interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef BUTTON_H_
#define BUTTON_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/** @defgroup BUTTON Button
 * This package provides the core capabilities for button functions.
 * @{
 */
/** @defgroup BUTTON_Public_Constants Button Public Constants
 * @{
*/

/**
 *  @brief	Up Button Pin in GPIO Port 2
*/
#define UP_BUTTON_PIN 8
/**
 *  @brief	Down Button Pin in GPIO Port 2
*/
#define DOWN_BUTTON_PIN 7
/**
 *  @brief	Enter Button Pin in GPIO Port 2
*/
#define ENTER_BUTTON_PIN 6

/**
 *  @brief	Up Button Pin Configuration start position in GPIO Port 2
 *  @note can be used on PINSEL4 and PINMODE4. On another ports and pins please consult the User Manual
*/
#define PINCFG_UP_BUTTON 2*UP_BUTTON_PIN
/**
 *  @brief	Down Button Pin Configuration start position in GPIO Port 2
 *  @note can be used on PINSEL4 and PINMODE4. On another ports and pins please consult the User Manual
*/
#define PINCFG_DOWN_BUTTON 2*DOWN_BUTTON_PIN
/**
 *  @brief	Enter Button Pin Configuration start position in GPIO Port 2
 *  @note can be used on PINSEL4 and PINMODE4. On another ports and pins please consult the User Manual
*/
#define PINCFG_ENTER_BUTTON 2*ENTER_BUTTON_PIN
/**
 *  @brief	Pull up value
 *  @note the value is logically reversed
*/
#define PINCFG_PULLUP 3

/**
 *  @brief	Buttons positions of UP, DOWN and ENTER on the register in LGPIO of Port 2
*/
#define BUTTONS_MASK 0x000001C0
/**
 *  @brief	Button position of UP on the register in LGPIO of Port 2
*/
#define UP_BUTTON_MASK 0x00000100
/**
 *  @brief	Button position of DOWN on the register in LGPIO of Port 2
*/
#define DOWN_BUTTON_MASK 0x00000080
/**
 *  @brief	Button position of ENTER on the register in LGPIO of Port 2
*/
#define ENTER_BUTTON_MASK 0x00000040

/**
 *  @brief	Button state of not being pressed
*/
#define NOT_PRESSED 0
/**
 *  @brief	Button state of just pressed
*/
#define PRESSED 1
/**
 *  @brief	Button state of being pressed
*/
#define PRESSING 3
/**
 *  @brief	Button state of just released
*/
#define RELEASED 2

/**
 *  @brief	Position of Up Button on BUTTON_GetButtonsEvents bitmap
*/
#define UP_BUTTON_POSITION 0
/**
 *  @brief	Position of Down Button on BUTTON_GetButtonsEvents bitmap
*/
#define DOWN_BUTTON_POSITION 2
/**
 *  @brief	Position of Enter Button on BUTTON_GetButtonsEvents bitmap
*/
#define ENTER_BUTTON_POSITION 4
/**
 * @}
 */

/** @defgroup BUTTON_Public_Structures Button Public Structures
 * @{
*/
/**
 * @brief struture to represent the UP, DOWN and ENTER buttons state
 */
typedef struct{
	short up;
	short down;
	short enter;
}BUTTONS_STATE_TYPEDEF;
/**
 * @}
 */

/** @defgroup BUTTON_Public_Functions Button Public Functions
 * @{
 */
/**
 * @brief	Initializes the Button API.
 * @note	This function must be called prior to any other BUTTON functions.
 */
void init_BUTTON(void);

/**
 * @brief	Read the buttons values
 * @return	bitmap code 0 if there is no button pressed.
 */
int BUTTON_Hit(void);

/**
 * @brief	Call the Button_init function,  just one. Check if some button is pressed
 * @return	bitmap code.
 */
int BUTTON_Read(void);

/**
 * @brief	Check if there is any change at the buttons state
 * @return	Bitmap code. 0:1-> up button state, 2:3 -> down button state, 4:5 -> enter button state
 */
int BUTTON_GetButtonsEvents(void);

/**
 * @}
 */


/**
 * @}
 */
#endif /* BUTTON_H_ */
