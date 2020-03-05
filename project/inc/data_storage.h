/**
* @file		data_storage.h
* @brief	Contains the Data Storage interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include "stdio.h"
#include "peripherals.h"
#include "BMP280.h"
#include "flash.h"

/**
 * @defgroup DATA_STORAGE Data Storage
 * This package provides the core capability of data storage.
 * @{
 */
/** @defgroup Data_Storage_Public_Constants Data Storage Public Constants
 * @{
*/
/**
 * @brief number of fields the user can change in the structure of time (HH:mm)
 */
#define TIME_FIELDS 2
/**
 * @brief number of fields the user can change in the structure of date (DD/MM/YYYY)
 */
#define DATE_FIELDS 3
/**
 * @brief number of fields the user can change in the structure of temperature
 */
#define TEMP_FIELDS 0
/**
 * @brief year OFFSET
 */
#define YEAR_OFFSET 0
/**
 * @brief month OFFSET
 */
#define MONTH_OFFSET 0
/**
 * @brief day OFFSET
 */
#define DAY_OFFSET 1

/**
 * @brief Enum that contain the max day value for each month
 */
enum MAX_DAYS_IN_MONTH {
	JANUARY_DAYS = 31,
	FEBRUARY_DAYS = 28,
	MARCH_DAYS = 31,
	APRIL_DAYS = 30,
	MAY_DAYS = 31,
	JUNE_DAYS = 30,
	JULY_DAYS = 31,
	AUGUST_DAYS = 31,
	SEPTEMBER_DAYS = 30,
	OCTOBER_DAYS = 31,
	NOVEMBER_DAYS = 30,
	DECEMBER_DAYS = 31
};

/**
 * @brief Array that contains the MAX_DAYS_IN_MONTH variables
 */
static const enum MAX_DAYS_IN_MONTH MAX_DAYS_MAP[] ={
		JANUARY_DAYS,
		FEBRUARY_DAYS,
		MARCH_DAYS,
		APRIL_DAYS,
		MAY_DAYS,
		JUNE_DAYS,
		JULY_DAYS,
		AUGUST_DAYS,
		SEPTEMBER_DAYS,
		OCTOBER_DAYS,
		NOVEMBER_DAYS,
		DECEMBER_DAYS
};

/**
 * @brief Enum that contain the name of each month
 */
enum MONTH{
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

/**
 * @brief Enum that contain Temperature names
 */
enum TEMPERATURE_UNITS{
	CELSIUS=0,
	FAHRENHEIT
};

/**
 * @}
 */

/** @defgroup Data_Storage_Public_Functions Data Storage Public Functions
 * @{
*/
/**
 * @brief Initialize data storage functions
 * @note must be called first
 */
void init_data_st();
/**
 * @brief saves the current date time at dateTime pointer
 */
void backup_dateTime();
/**
 * @brief calls send_dateTime with timer mask
 */
void send_time();
/**
 * @brief calls send_dateTime with date mask
 */
void send_date();
/**
 * @brief send the Temperature Unit
 */
void send_temp_unit();
/**
 * @brief send the updated time/date to RTC
 */
void send_dateTime(short mask);
/**
 * @brief transform the current date into a string
 */
void dateTimeToString(char *str);
/**
 * @brief transform the current temperature and pressure into a string
 */
void TemperatureAndPressureToString(char *str);
/**
 * @brief writes in str the current time
 */
void get_Time(char* str);
/**
 * @brief writes in str the current temperature
 */
void get_Temperature(char *str);
/**
 * @brief writes in str the current date
 */
void get_Date(char* str);
/**
 * @brief add to the current time the val
 */
void change_time(int val);
/**
 * @brief add to the current date the val
 */
void change_date(int val);
/**
 * @brief change the temperature unit
 */
void change_temp_unit(int val);
/**
 * @brief advance to the next field. In Time it goes from HH to mm.
 * In Date it goes from YYYY to MM and then to DD
 */
int nextField(int type);
/**
 * @return returns the current field
 */
int get_CurrentField();
/**
 * @}
 *
 *
 * @defgroup DATA_STORAGE_STATIC_FUNCTIONS Date Storage Static Functions
 * @{
 * @}
 * @defgroup DATA_STORAGE_STATIC_CONSTANTS Date Storage Static Constants
 * @{
 * @}
 * @defgroup DATA_STORAGE_STATIC_VARIABLES Date Storage Static Variables
 * @{
 * @}
 * @}
 */
#endif /* DATA_STORAGE_H_ */
