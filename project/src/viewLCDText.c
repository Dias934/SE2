/*
 * ViewLCDText.c
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#include "viewLCDText.h"

char str[16];

static char * MAINTENANCE_CHANGE_TITLE[]={"Change Time","Change Date","Change Temp. Un"};

static char TEMPERATURE_UNIT[2]={'C','F'};

static char SEC_CHARACTER[2]={' ',':'};

void format_full_calendar(){
	struct tm cal;
	get_cur_time(&cal);
	sprintf(str,"%02d%c%02d %02d/%02d/%04d", cal.tm_hour,SEC_CHARACTER[cal.tm_sec%2],cal.tm_min, cal.tm_mday, cal.tm_mon+1, cal.tm_year+1900);
}

void format_time(){
	struct tm cal;
	get_cur_time(&cal);
	sprintf(str,"%02d%c%02d%11c",cal.tm_hour,SEC_CHARACTER[cal.tm_sec%2],cal.tm_min,' ');
}

void format_calendar(){
	struct tm cal;
	get_cur_time(&cal);
	sprintf(str,"%02d/%02d/%04d%6c",cal.tm_mday,cal.tm_mon+1, cal.tm_year+1900,' ');
}

void format_time_maintenance(struct tm *cal){
	sprintf(str,"%02d%c%02d%11c",cal->tm_hour,SEC_CHARACTER[(cal->tm_sec)%2],cal->tm_min,' ');
}

void format_calendar_maintenance(struct tm *cal){
	sprintf(str,"%02d/%02d/%04d%6c",cal->tm_mday,cal->tm_mon+1, cal->tm_year+1900,' ');
}

void format_temperature_pressure(){
	double temp=get_temperature();
	if(temp>NOT_OK){
		double press=get_pressure();
		char unit=TEMPERATURE_UNIT[get_temperature_unit()];
		if(temp>=100)
			sprintf(str,"%3.0f%c%4c%6.0fPa",temp, unit,' ', press);
		else
			sprintf(str,"%2.0f%c%5c%6.0fPa",temp, unit,' ', press);
	}
	else
		sprintf(str,"sensor not found");
}

void format_temperature_unit(){
	double temp=get_temperature();
	if(temp>NOT_OK){
		char unit=TEMPERATURE_UNIT[get_temperature_unit()];
		if(temp>99)
			sprintf(str,"%3.0f%c%12c",temp, unit,' ');
		else
			sprintf(str,"%2.0f%c%13c",temp, unit,' ');
	}
	else
		sprintf(str,"sensor not found");
}

void view_init(char * s){
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	LCDText_WriteString("Initializing:");
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	LCDText_WriteString(s);
}

void view_init_result(char * s){
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	LCDText_WriteString(s);
}

void view_normal(){
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	format_full_calendar();
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_temperature_pressure();
	LCDText_WriteString(str);
}

static void (*select_format[])()={&format_time, &format_calendar, &format_temperature_unit};

void view_select_maintenance(short idx){
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	if(idx<2)
		sprintf(str,"%s%5c",MAINTENANCE_CHANGE_TITLE[idx],' ');
	else
		sprintf(str,"%s",MAINTENANCE_CHANGE_TITLE[idx]);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	(select_format[idx])();
	LCDText_WriteString(str);
}

void view_time_maintenance(short field, struct tm *calendar){
	LCDText_Locate(0,0);
	sprintf(str,"%s%5c",MAINTENANCE_CHANGE_TITLE[0],' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_time_maintenance(calendar);
	LCDText_WriteString(str);
	LCDText_Locate(1,field*3+1);
	LCDText_Cursor(CURSOR_ON);
}

void view_calendar_maintenance(short field, struct tm *calendar){
	LCDText_Locate(0,0);
	sprintf(str,"%s%5c",MAINTENANCE_CHANGE_TITLE[1],' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_calendar_maintenance(calendar);
	LCDText_WriteString(str);
	if(field==0)
		LCDText_Locate(1,9);
	else
		LCDText_Locate(1,7-field*3);
	LCDText_Cursor(CURSOR_ON);
}

void view_temperature_unit_maintenance(){
	LCDText_Locate(0,0);
	sprintf(str,"%s",MAINTENANCE_CHANGE_TITLE[2]);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_temperature_unit();
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	LCDText_Cursor(CURSOR_ON);
}
