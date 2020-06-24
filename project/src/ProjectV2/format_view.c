#include <data_center.h>
#include "format_view.h"
#include <stdio.h>

void format_full_calendar(struct tm *cal, char* str, char seg){
	sprintf(str, "%02d%c%02d %02d/%02d/%04d", cal->tm_hour, seg, cal->tm_min, cal->tm_mday, cal->tm_mon+1, cal->tm_year+1900);
}

void format_time(struct tm *cal, char* str, char seg){
	sprintf(str, "%02d%c%02d%11c", cal->tm_hour, seg, cal->tm_min, ' ');
}

void format_calendar(struct tm *cal, char* str){
	sprintf(str, "%02d/%02d/%04d%6c", cal->tm_mday, cal->tm_mon+1, cal->tm_year+1900,' ');
}

void format_time_maintenance(struct tm *cal, char* str, char seg){
	sprintf(str, "%02d%c%02d%11c", cal->tm_hour, seg, cal->tm_min,' ');
}

void format_calendar_maintenance(struct tm *cal, char* str){
	sprintf(str,"%02d/%02d/%04d%6c",cal->tm_mday,cal->tm_mon+1, cal->tm_year+1900,' ');
}

void format_temperature_pressure(double temp, double press, char* str, char unit){
	if(temp>NOT_OK){
		if(temp>=100)
			sprintf(str,"%3.0f%c%4c%6.0fPa",temp, unit,' ', press);
		else
			sprintf(str,"%2.0f%c%5c%6.0fPa",temp, unit,' ', press);
	}
	else
		sprintf(str,"sensor not found");
}

void format_temperature_unit(char* str, char unit){
	sprintf(str,"%c%15c", unit,' ');
}
