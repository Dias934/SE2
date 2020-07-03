/*
 * my_types.h
 *
 *  Created on: 24/06/2020
 *      Author: Manuel
 */

#ifndef MY_TYPES_H_
#define MY_TYPES_H_

#include <time.h>

typedef struct{
	double temp;
	double press;
	bool valid;
}SENSOR_TYPEDEF;

typedef struct{
	struct tm cal;
	SENSOR_TYPEDEF sensor_info;
	unsigned short unit;
}DATA_TYPEDEF;

enum TEMPERATURE_UNITS{
	CELSIUS=0,
	FAHRENHEIT
};

typedef struct{
	short cmd;
	short args_size;
	void *args;
}CMD_TYPEDEF;

#endif /* MY_TYPES_H_ */
