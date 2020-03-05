/**
* @file		data_storage.c
* @brief	Contains the Data Storage interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#include "data_storage.h"

struct tm dateTime;
/**
 * @ingroup DATA_STORAGE_STATIC_FUNCTIONS
 * @{
 */

/**
 * @return return the value of the current Temperature in Celsius
 */
double static celsius();
/**
 * @brief transform Celsius into Fanhrenheit
 * @return return the value in Fahrenheit
 */
double static celsius_to_fahrenheit();
/**
 *
 * @}
 *
 * @ingroup DATA_STORAGE_STATIC_CONSTANTS
 * @{
 *
 * @brief arry that represents the current second. ' ' even second, ':' odd second
 */
const char SEC_CHARACTER[2]={' ',':'};

/**
 * @brief arry that represents the temperature units
 */
const char TEMPERATURE_UNIT[2]={'C','F'};

/**
 * @brief arry that represents the pointers of time in time structure
 */
int* TIME_PTRS[TIME_FIELDS]={&(dateTime.tm_hour),&(dateTime.tm_min)};

/**
 * @brief arry that represents the maximum values of hour and minutes
 */
const int MAX_TIMES[TIME_FIELDS]={MAX_HOUR, MAX_MIN};

/**
 * @brief arry that represents the pointers of date in time structure
 */
int* DATE_PTRS[DATE_FIELDS]={&(dateTime.tm_year),&(dateTime.tm_mon),&(dateTime.tm_mday)};

/**
 * @brief arry that represents the maximum values of years, months and days
 */
int MAX_DATES[DATE_FIELDS]={MAX_YEAR, MAX_MONTH, MAX_DAY};

/**
 * @brief arry that represents the offset values of years, months and days
 */
int DATE_OFFSETS[DATE_FIELDS]={YEAR_OFFSET, MONTH_OFFSET, DAY_OFFSET};

/**
 * @brief array of function pointers to return the current temperature in UNIT index
 */
double (*temperatureUnit[2])()={&celsius,&celsius_to_fahrenheit};
/**
 * @}
 */

/**
 * @ingroup DATA_STORAGE_STATIC_VARIABLES
 * @{
 * @brief index that represents the current field to change
 */
static short fieldToChange;
/**
 *
 * @brief represents the unit of temperature
 */
static unsigned int unit;
/**
 *
 * @brief auxiliar variable to save the unit of temperature
 */
static unsigned int aux;

/**
 * @}
 */

void init_data_st(){
	fieldToChange=0;
	RTC_GetValue(&dateTime);
	readFromFlash(&unit);
	if(unit>FAHRENHEIT)
		unit=CELSIUS;
	aux=unit;
}

void backup_dateTime(){
	fieldToChange=0;
	RTC_GetValue(&dateTime);
}

void send_time(){
	send_dateTime(TIME_MASK);
}

void send_date(){
	send_dateTime(DATE_MASK);
}

void send_temp_unit(){
	unit=aux;
	writeToFlash(&unit,sizeof(unit));
	fieldToChange=0;
}

void send_dateTime(short mask){
	fieldToChange=0;
	RTC_SetMaskedValue(&dateTime,mask);
}

void dateTimeToString(char *str){
	RTC_GetValue(&dateTime);
	sprintf(str,"%02d/%02d/%04d %02d%c%02d",dateTime.tm_mday,dateTime.tm_mon+1, dateTime.tm_year+1900, dateTime.tm_hour,SEC_CHARACTER[dateTime.tm_sec%2],dateTime.tm_min);
}

void TemperatureAndPressureToString(char *str){
	aux=unit;
	measure();
	sprintf(str,"%3.2f%c %03.1fkPa ",(*temperatureUnit[unit])(),TEMPERATURE_UNIT[unit],current_press/1000.0);
}

void get_Time(char* str){
	sprintf(str,"%02d:%02d", dateTime.tm_hour, dateTime.tm_min);
}

void get_Date(char* str){
	sprintf(str,"%02d/%02d/%04d", dateTime.tm_mday,dateTime.tm_mon+1, dateTime.tm_year+1900);
}

void change_time(int val){
	(*TIME_PTRS[fieldToChange])+=val;
	if((*TIME_PTRS[fieldToChange])<0)(*TIME_PTRS[fieldToChange])=MAX_TIMES[fieldToChange]-1;
	(*TIME_PTRS[fieldToChange])=(*TIME_PTRS[fieldToChange])%MAX_TIMES[fieldToChange];
}

void change_date(int val){
	(*DATE_PTRS[fieldToChange])+=val;
	int max=MAX_DATES[fieldToChange];
	if(fieldToChange==2)
		max=MAX_DAYS_MAP[dateTime.tm_mon]+ (dateTime.tm_mon==FEBRUARY && ((dateTime.tm_year%4==0 && dateTime.tm_year%100!=0) || dateTime.tm_year%400==0)?1:0); //definir o valor máximo de dias.
	if((*DATE_PTRS[fieldToChange])<DATE_OFFSETS[fieldToChange])
		(*DATE_PTRS[fieldToChange])=max;
	(*DATE_PTRS[fieldToChange])=(*DATE_PTRS[fieldToChange])%(max+1);
	if((*DATE_PTRS[fieldToChange])<DATE_OFFSETS[fieldToChange])
		(*DATE_PTRS[fieldToChange])=DATE_OFFSETS[fieldToChange];
}

void change_temp_unit(int val){
	aux+=val;
	if(aux<0)
		aux=FAHRENHEIT;
	aux%=2;
}

int nextField(int type){
	return type-(++fieldToChange);
}

int get_CurrentField(){
	return fieldToChange;
}

double celsius(){
	return current_temp;
}

double celsius_to_fahrenheit(){
	return current_temp*(9.0/5.0)+32.0;
}

void get_Temperature(char *str){
	measure();
	sprintf(str,"%3.2f%c",(*temperatureUnit[aux])(),TEMPERATURE_UNIT[aux]);
}
