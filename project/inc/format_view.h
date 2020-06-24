
#ifndef FORMAT_VIEW_H_
#define FORMAT_VIEW_H_

#include <time.h>

void format_full_calendar(struct tm *cal, char* str,  char seg);

void format_time(struct tm *cal, char* str,  char seg);

void format_calendar(struct tm *cal, char* str);

void format_time_maintenance(struct tm *cal, char* str, char seg);

void format_calendar_maintenance(struct tm *cal, char* str);

void format_temperature_pressure(double temp, double press, char* str, char unit);

void format_temperature_unit(char* str, char unit);

#endif
