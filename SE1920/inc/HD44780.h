/**
* @file		HD44780.h
* @brief	Contains the data needed to interect the HD44780 LCD Display.
* @version	1.1
* @date		12 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef HD44780_H_
#define HD44780_H_

/** @defgroup HD44780 HD44780
 * This package provides the core capabilities for HD44780 LCD Display.
 * @{
 */
/** @defgroup HD44780_Public_Constants HD44780 Public Constants
 * @{
*/

/**
 * @brief defines if the written data is a command or a character data
 */
enum RS_VAL{
	COMMAND,
	DATA
};


/**
 * @defgroup HD44780_Command_Instructions HD44780 Command Instructions
 * This package provides the all the information about the Command Instructions
 * @{
 */

/**
 * @defgroup HD44780_Init_Command Init Command
 * Init command
 * @{
 * @brief Initialization instruction value according to the manufacturer
 */
#define INIT_VAL 0x3
/**
 * @}
 */

/**
 * @defgroup HD44780_Clear_Display_Command Clear Display Command
 * Clear display command
 * @{
 * @brief Clears entire display and sets DDRAM address 0 in address counter.
 */
#define CLEAR_DISPLAY_CMD 0X1
/**
 * @}
 */

/**
 * @defgroup HD44780_Return_Home_Command Return Home Command
 * Return home command
 * @{
 *@brief Sets DDRAM address 0 in address counter. Also returns display from being
 *@brief shifted to original position. DDRAM contents remain unchanged.
 */
#define RETURN_HOME_CMD 0X2
/**
 * @}
 */

/**
 * @defgroup HD44780_Entry_Mode_Set_Command Entry Mode Set Command
 * Entry set mode command
 * @{
 *@brief Sets cursor move direction and specifies display shift.
 *@brief These operations are performed during data write and read.
 */
#define ENTRY_MODE_SET_CMD 0X4
/**
 * @brief Shift Enable bit position. Shifts the entire display either to the
 * @brief right (I/D = 0) or to the left (I/D = 1) when S is 1. The display does
 * @brief not shift if S is 0. If S is 1, it will seem as if the cursor does not
 * @brief move but the display does. The display does not shift when reading from
 * @brief DDRAM. Also, writing into or reading out from CGRAM does not shift the display.
 */
#define S_POSITION 0
/**
 * @brief Increment or Decrements bit position. Increments (I/D = 1)
 * @brief or decrements (I/D = 0) the DDRAM address by 1 when a character code is
 * @brief written into or read from DDRAM. The cursor or blinking moves to the right
 * @brief when incremented by 1 and to the left when decremented by 1.
 * @brief The same applies to writing and reading of CGRAM.
 */
#define I_D_POSITION 1
/**
 * @brief S values: SHIFT_DISABLE=0 and SHIFT_ENABLE=1
 */
enum S_VAL{
	SHIFT_DISABLE,
	SHIFT_ENABLE
};
/**
 * @brief I/D values: DECREMENT=0 and INCREMENT=1
 */
enum I_D_VAL{
	DECREMENT,
	INCREMENT
};
/**
 * @}
 */

/**
 * @defgroup HD44780_Display_Control_Command Display Control Command
 * Display control command
 * @{
 * @brief Sets entire display (D) on/off, cursor on/off (C), and
 * @brief blinking of cursor position character (B).
 */
#define DISPLAY_CONTROL_CMD 0X8

/**
 * @brief Blinking cursor enable bit position. The character indicated by the
 * @brief cursor blinks when B is 1.
 */
#define B_POSITION 0
/**
 *@brief Cursor enable bit position. The cursor is displayed when C is 1 and
 *@brief not displayed when C is 0. Even if the cursor disappears, the function
 *@brief of I/D or other specifications will not change during display data write.
 */
#define C_POSITION 1
/**
 * @brief Display enable bit position. The display is on when D is 1 and off
 * @brief when D is 0. When off, the display data remains in DDRAM, but can be
 * @brief displayed instantly by setting D to 1.
 */
#define D_POSITION 2

/**
 * @brief B values: BLINK_CURSOR_OFF=0 and BLINK_CURSOR_ON=1
 */
enum B_VAL{
	BLINK_CURSOR_OFF,
	BLINK_CURSOR_ON
};
/**
 * @brief C values: CURSOR_OFF=0 and CURSOR_ON=1
 */
enum C_VAL{
	CURSOR_OFF,
	CURSOR_ON
};
/**
 * @brief D values: DISPLAY_OFF=0 and DISPLAY_ON=1
 */
enum D_VAL{
	DISPLAY_OFF,
	DISPLAY_ON
};
/**
 * @}
 */

/**
 * @defgroup HD44780_Cursor_Display_Shift_Command Cursor Display Shift Command
 * Cursor Display Shift command
 * @{
 * @brief Moves cursor and shifts display without changing DDRAM contents.
 */
#define CURSOR_DISPLAY_SHIFT_CMD 0X10

/**
 * @brief Shift Right or Left bit position. Cursor or display shift shifts
 * @brief the cursor position or display to the right or left without writing
 * @brief or reading display data
 */
#define R_L_POSITION 2
/**
 * @brief Display shift or Cursor move bit position.
 */
#define S_C_POSITION 3

/**
 * @brief R/L values: SHIFT_LEFT=0 and SHIFT_RIGHT=1
 */
enum R_L_VAL{
	SHIFT_LEFT,
	SHIFT_RIGHT
};
/**
 * @brief S/C values: CURSOR_MOVE=0 and DISPLAY_SHIFT=1
 */
enum S_C_VAL{
	CURSOR_MOVE,
	DISPLAY_SHIFT
};
/**
 * @}
 */

/**
 * @defgroup HD44780_Function_Set_Command Function Set Command
 * Function Set command
 * @{
 *@brief  Sets interface data length (DL), number of display lines (N), and character font (F).
 *@note  Perform the function at the head of the program before executing
 *@note  any instructions (except for the read busy flag and address instruction).
 *@note  From this point, the function set instruction cannot be executed unless the
 *@note  interface data length is changed.
 */
#define FUNCTION_SET_CMD 0X20

/**
 * @brief Select Font bit position. Sets the character font.
 */
#define F_POSITION 2
/**
 * @brief Number of Lines bit position. Sets the number of display lines.
 */
#define N_POSITION 3
/**
 * @brief Data Length bit position. Sets the interface data length. Data is
 * @brief sent or received in 8-bit lengths (DB7 to DB0) when DL is 1, and in
 * @brief 4-bit lengths (DB7 to DB4) when DL is 0.When 4-bit length is selected,
 * @brief data must be sent or received twice.
 */
#define DL_POSITION 4

/**
 * @brief F values: EIGHT_DOT_FONT=0 and TEN_DOT_FONT=1
 */
enum F_VAL{
	EIGHT_DOT_FONT,
	TEN_DOT_FONT
};
/**
 * @brief N values: ONE_LINE=0 and TWO_LINES=1
 */
enum N_VAL{
	ONE_LINE,
	TWO_LINES
};
/**
 * @brief DL values: FOUR_BIT=0 and EIGHT_BIT=1
 */
enum DL_VAL{
	FOUR_BIT,
	EIGHT_BIT
};
/**
 * @}
 */

/**
 * @defgroup HD44780_Set_CGRAM_ADDR_Command Set CGRAM Address Command
 * Set CGRAM Address command
 * @{
 * @brief Sets CGRAM address. CGRAM data is sent and received after this setting.
 */
#define SET_CGRAM_ADDR_CMD 0X40
/**
 * @}
 */

/**
 * @defgroup HD44780_Set_DDRAM_ADDR_Command Set DDRAM Address Command
 * Set DDRAM Address command
 * @{
 * @brief Sets DDRAM address. DDRAM data is sent and received after this setting.
 */
#define SET_DDRAM_ADDR_CMD 0X80

/**
 *@brief Bit position of the row. Use this constant to shift the row number you
 *@brief want the cursor to be
 *@note for shift left only (Figure 6 of the manufacturer)
 */
#define ROW_POSITION 6
/**
 *@brief the maximum value that a column can have
 */
#define MAX_COL_VALUE 0xF

/**
 * @}
 * @}
 * @}
 * @}
 */
#endif /* HD44780_H_ */
