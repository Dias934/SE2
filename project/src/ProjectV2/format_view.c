#include <data_center.h>
#include "format_view.h"
#include <stdio.h>

static char TEMPERATURE_UNIT[2]={'C','F'};

static char SEC_CHARACTER[2]={' ',':'};

static double celsius_to_far(double temp){
	return (temp)*9/5 + 32;
}

static double celsius(double temp){
	return temp;
}

static double (*temperature_funcs[])(double)={celsius, celsius_to_far};

void format_full_calendar(struct tm cal, char* str){
	sprintf(str, "%02d%c%02d %02d/%02d/%04d", cal.tm_hour, SEC_CHARACTER[cal.tm_sec%2], cal.tm_min, cal.tm_mday, cal.tm_mon+1, cal.tm_year+1900);
}

void format_time(struct tm cal, char* str){
	sprintf(str, "%02d%c%02d%11c", cal.tm_hour, SEC_CHARACTER[cal.tm_sec%2], cal.tm_min, ' ');
}

void format_calendar(struct tm cal, char* str){
	sprintf(str, "%02d/%02d/%04d%6c", cal.tm_mday, cal.tm_mon+1, cal.tm_year+1900,' ');
}

void format_time_maintenance(struct tm cal, char* str){
	sprintf(str, "%02d%c%02d%11c", cal.tm_hour, SEC_CHARACTER[cal.tm_sec%2], cal.tm_min,' ');
}

void format_calendar_maintenance(struct tm cal, char* str){
	sprintf(str,"%02d/%02d/%04d%6c",cal.tm_mday, cal.tm_mon+1, cal.tm_year+1900,' ');
}

void format_temperature_pressure(double temp, double press, char* str, unsigned short unit){
	if(temp>NOT_OK){
		if(temp>=100)
			sprintf(str,"%3.0f%c%4c%6.0fPa", temperature_funcs[unit](temp), TEMPERATURE_UNIT[unit],' ', press);
		else
			sprintf(str,"%2.0f%c%5c%6.0fPa",temperature_funcs[unit](temp), TEMPERATURE_UNIT[unit],' ', press);
	}
	else
		sprintf(str,"sensor not found");
}

void format_temperature_unit(char* str, unsigned short unit){
	sprintf(str,"%c%15c", TEMPERATURE_UNIT[unit],' ');
}
