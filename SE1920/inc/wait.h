/**
* @file		wait.h
* @brief	Contains the delay API.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef WAIT_H_
#define WAIT_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

/** @defgroup WAIT Wait
 * This package provides the core capabilities for wait functions.
 * @{
 */

/** @defgroup WAIT_Public_Constants Wait Public Constants
 * @{
*/

/**
 *  @brief	number of milliseconds in a second
*/
#define MILLISECONDS_DIVISION 1000
/**
 *  @brief	number of microseconds in a second
*/
#define MICROSECONDS_DIVISION 1000000

/**
 *  @brief	Select CCLK frequency for PCLK (Table 42 of the manual)
*/
#define CCLK_FREQ 1

/**
 *  @brief	Timer0 clk position in PCLKSEL0
*/
#define TIMER0_CLK 2

/**
 *  @brief	Select timer mode of the register CTCR
*/
#define TIMER_MODE 0

/**
 *  @brief	Select reset mode on match register 0
*/
#define MR0I 0
/**
 *  @brief	Select reset mode on match register 0
*/
#define MR0S 2
/**
 *  @brief	Interupt mask of MR0 in IR register
*/
#define MR0_INTERRUPT 1

/**
 *  @brief	Disable and reset TC and PC
*/
#define RESET_STOPWATCH 1
/**
 *  @brief	Enable and reset TC and PC
*/
#define START_STOPWATCH 0



/**
 * @}
 */



/** @defgroup WAIT_Public_Functions Wait Public Functions
 * @{
 */
/**
 * @brief	Initialises the wait API for 1 ms resolution.
 * @note	This function must be called prior to any other WAIT functions.
 */
void init_wait();

/**
 * @brief	waits the corresponding time from hz to ms.
 * @param	frequency: the whole number of hertz to wait.
 * @note created for applications that needs a certain frequency. Blocking function
 */

void wait_hz(int frequency);

/**
 * @brief	Waits a number of milliseconds.
 * @param	millis: the whole number of milliseconds to wait.
 * @note blocking function
 */
void wait_ms(int millis);

/**
 * @brief	Counts the time that has passed since the time received.
 * @param	time: start time.
 * @return	millis: the time that has passed or the current time if input parameter = 0.
 * @note not blocking function
 */
uint32_t wait_elapsed(uint32_t time);

/**
 * @brief	Waits a number of microseconds.
 * @param	waitUs: wait a certain number of microseconds.
 * @note    blocking function
 */
void wait_ChronoUs(uint32_t waitUs);


/**
 * @}
 */


/**
 * @}
 */

#endif /* WAIT_H_ */
