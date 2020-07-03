/*
 * dataManager.h
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#ifndef DATA_CENTER_H_
#define DATA_CENTER_H_

#include <24AA256.h>
#include "stdio.h"
#include "peripherals.h"
#include "BMP280.h"
#include "my_types.h"
#include <stdbool.h>

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

#define NOT_OK (-50)

#define DATA_ID 0xFA5A
#define DATA_ID_ADDR 5


bool init_data_manager();

void get_cur_time(struct tm *calendar);

void set_time(struct tm *calendar);

void set_calendar(struct tm *calendar);

short get_temperature_unit();

double get_temperature();

double get_pressure();

void set_unit(short unit);

void save_temperature_unit();

void undo_set_unit();

#endif /* DATA_CENTER_H_ */
