/**
* @file		rtc.h
* @brief	Contains the RTC function utility.
* @version	1.1
* @date		12 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef RTC_H_
#define RTC_H_

#include "time.h"
#include "LPC17xx.h"

/**
 * @defgroup RTC RTC
 * This package provides the core capabilities for RTC functions.
 * @{
 * @defgroup RTC_Public_Constants RTC Public Constants
 * @{
 * @defgroup RTC_Public_TIME_Constants RTC Public Time Constants
 * @{
 * @defgroup RTC_Public_TIME_VARIABLES_BITS_POSITION RTC Public Time Variables Bits and Position
 * @{
 *  @brief	describe the time variables bits and position at Consolidated time registers
*/

#define SEC_BITS 0x3F
#define MIN_BITS 0x3F
#define HOUR_BITS 0x1F

#define SEC_POSITION 0
#define MIN_POSITION 8
#define HOUR_POSITION 16

/**
 * @}
 * @defgroup RTC_Public_TIME_VARIABLES_MAX_VALUE RTC Public Time Variables Max Value
 * @{
 *  @brief	describe the max value for the time variables
 */

#define MAX_SEC 60
#define MAX_MIN 60
#define MAX_HOUR 24
/**
 * @}
 * @brief time masks
 */
#define TIME_MASK HOUR_MASK | MIN_MASK

/**
 * @}
 * @defgroup RTC_Public_DATE_Constants RTC Public Date Constants
 * @{
 * @defgroup RTC_Public_DATE_VARIABLES_MAX_VALUE RTC Public DATE Variables Max Value
 * @{
 * @brief	describe the max value for the date variables
 */

#define MAX_YEAR 4096
#define MAX_MONTH 12
#define MAX_DAY 31

/**
 * @}
 * @defgroup RTC_Public_DATE_VARIABLES_BITS_POSITION RTC Public Date Variables Bits and Position
 * @{
 * @brief	describe the date variables bits and position at Consolidated time registers
*/

#define DOW_BITS 0xF
#define DOM_BITS 0x1F
#define MONTH_BITS 0xF
#define YEAR_BITS 0xFFF
#define DOY_BITS 0xFFF

#define DOW_POSITION 24
#define DOM_POSITION 0
#define MONTH_POSITION 8
#define YEAR_POSITION 16
#define DOY_POSITION 0
/**
 * @}
 * @brief date masks
 */
#define DATE_MASK YEAR_MASK | MONTH_MASK | DOM_MASK
/**
 * @defgroup RTC_Public_DATE_ADJUSTMENTS RTC Public Date Adjustments
 * @{
 */
#define MONTH_ADJUSTMENT (+1) //LPC1769 [1-12] time.h [0-11]
#define DOY_ADJUSTMENT (+1) //LPC1769 [1-365(366)] time.h [0-365]

#define GMT_PLUS_ONE (+1)
/**
 *@}
 *@}
 *@}
 *@defgroup RTC_Public_ENUMS RTC Public Enums
 *@{
 */
/**
 * @brief RTC flags
 */
enum RTC_FLAGS {
		SEC_MASK=1,
		MIN_MASK,
		HOUR_MASK,
		DOW_MASK,
		DOM_MASK,
		MONTH_MASK,
		YEAR_MASK,
		DOY_MASK
};
/**
 * @}
 */
#define CTCRST_VAL 0
#define CCALEN_VAL 0x10
#define INIT_VAL_RTC CTCRST_VAL|CCALEN_VAL
#define CLKEN_ENABLE 1
#define CLKEN_DISABLE 0

/**
 *@defgroup RTC_Public_FUNCTIONS RTC Public Functions
 *@{
 */
/**
 * @brief	Initializes the RTC API
 * @note	This function must be called prior to any other RTC functions.
 */
void init_RTC(time_t seconds);
/**
 * @brief put at dateTime the value of the current time
 */
void RTC_GetValue(struct tm *dateTime);
/**
 * @brief Insert in RTC the values from dateTime. the mask is used to choose between dates and time
 */
void RTC_SetMaskedValue(struct tm *dateTime, short mask);
/**
 * @brief Insert in RTC the values from dateTime.
 */
void RTC_SetValue(struct tm *dateTime);
/**
 * @brief Insert in RTC the value of seconds in date form.
 */
void RTC_SetSconds(time_t seconds);
/**
 * @return returns the RTC value in seconds since 1/01/1970.
 */
time_t RTC_GetSeconds(void);

/**
 * @}
 */
#endif /* RTC_H_ */
