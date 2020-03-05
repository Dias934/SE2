/**
* @file		lcd.h
* @brief	Contains the lcd interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef LCD_H_
#define LCD_H_


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "HD44780.h"


/** @defgroup LCD lcd
 * This package provides the core capabilities for the LCD Display.
 * @{
 */
/** @defgroup LCD_Public_Constants LCD Public Constants
 *  This package provides the public constants of the LCD Display
 * @{
*/
#define MAX_CHAR 32
/**
 *@defgroup LCD_Pins_Public_Constants LCD Pins
 * This package provides the chosen pins to control the LCD
 * @{
 */

/**
 * @brief Pin of Port 0 to send data to bit 4 of the LCD
 */
#define LCD_DB4 23
/**
 * @brief Pin of Port 0 to send data to bit 5 of the LCD
 */
#define LCD_DB5 24
/**
 * @brief Pin of Port 0 to send data to bit 6 of the LCD
 */
#define LCD_DB6 25
/**
 * @brief Pin of Port 0 to send data to bit 7 of the LCD
 */
#define LCD_DB7 26
/**
 * @brief Pin of Port 1 to send the Enable signal of the LCD
 */
#define LCD_ENABLE 30
/**
 * @brief Pin of Port 1 to RS pin of the LCD
 */
#define LCD_RS 31

/**
 * @}
 */

/**
 *@defgroup LCD_Config_Pins_Public_Constants LCD Config Pins
 * This package provides the configuration pins of the MCU to control the LCD
 * @{
 */

/**
 * @brief The bit position that corresponds the chosen pin to send data to bit 4 of the LCD of the register PINSEL1
 */
#define PINCFG_DB4 14
/**
 * @brief The bit position that corresponds the chosen pin to send data to bit 5 of the LCD of the register PINSEL1
 */
#define PINCFG_DB5 16
/**
 * @brief The bit position that corresponds the chosen pin to send data to bit 6 of the LCD of the register PINSEL1
 */
#define PINCFG_DB6 18
/**
 * @brief The bit position that corresponds the chosen pin to send data to bit 7 of the LCD of the register PINSEL1
 */
#define PINCFG_DB7 20
/**
 * @brief The bit position that corresponds the chosen pin to the Enable signal of the LCD of the register PINSEL3
 */
#define PINCFG_ENABLE 28
/**
 * @brief The bit position that corresponds the chosen pin to the RS of the LCD of the register PINSEL3
 */
#define PINCFG_RS 30
/**
 * @}
 * @}
 */

/** @defgroup LCD_Public_Functions LCD Public Functions
 *  This package provides the public functions of the LCD Display
 * @{
*/

/**
 * @brief LCD instruction initialization function to be able to send and control the LCD using 4 bits.
 * @note Call this function only at the beginning of the program and only once
 */
void init_LCDText(void);

/**
 * @brief	Writes the given character on the LCD in the current cursor position.
 * @param	ch: character to write.
 */
void LCDText_WriteChar(char ch);

/**
 * @brief	Writes the given string on the LCD in the current cursor position.
 * @param	str: string to write.
 * @note this function can change between lines if the string is to large
 */
void LCDText_WriteString(char *str);

/**
 * @brief	Put the cursor in the given position of the lcd
 * @param	row: put the cursor at the first (0) or the second line(1).
 * @param   column put the cursor at the given column (0-15).
 */
void LCDText_Locate(int row, int column);

/**
 * @brief	Clear the LCD Display
 * @note  The cursor goes back to the initial position, first line (0) and first column (0).
 */
void LCDText_Clear(void);

/**
 * @brief	Writes the given string on the LCD in the current cursor position using a certain format.
 * @param	fmt: String to write.
 * @note   identical to the C printf library.
 */
void LCDText_Printf(char *fmt, ...); /* DESAFIO */

void LCDText_PrintBinary(int bin);

void LCDText_Cursor(int state);

/**
 * @}
 * @}
 */
#endif /* LCD_H_ */
