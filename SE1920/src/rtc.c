/*
 * rtc.c
 *
 *  Created on: 23/10/2019
 *      Author: A38866
 */

#include "rtc.h"
#include <stdlib.h>

void init_RTC(time_t seconds){
	struct tm *aux;
	aux=gmtime(&seconds);
	LPC_RTC->CCR=INIT_VAL_RTC;
	RTC_SetValue(aux);
}

void RTC_GetValue(struct tm *dateTime){
	dateTime->tm_sec=(LPC_RTC->CTIME0&SEC_BITS);
	dateTime->tm_min=((LPC_RTC->CTIME0&(MIN_BITS<<MIN_POSITION))>>MIN_POSITION);
	dateTime->tm_hour=(((LPC_RTC->CTIME0&(HOUR_BITS<<HOUR_POSITION))>>HOUR_POSITION));
	dateTime->tm_wday=((LPC_RTC->CTIME0&(DOW_BITS<<DOW_POSITION))>>DOW_POSITION);
	dateTime->tm_mday=(LPC_RTC->CTIME1&DOM_BITS);
	dateTime->tm_mon=((LPC_RTC->CTIME1&(MONTH_BITS<<MONTH_POSITION))>>MONTH_POSITION)-MONTH_ADJUSTMENT;
	dateTime->tm_year=((LPC_RTC->CTIME1&(YEAR_BITS<<YEAR_POSITION))>>YEAR_POSITION);
	dateTime->tm_yday=(LPC_RTC->CTIME2&DOY_BITS)-DOY_ADJUSTMENT;
}

void RTC_SetMaskedValue(struct tm *dateTime, short mask){
	LPC_RTC->CCR|=CLKEN_DISABLE;
	if((mask & SEC_MASK)>0)
		LPC_RTC->SEC=(dateTime->tm_sec)%MAX_SEC;
	if((mask & MIN_MASK)>0)
		LPC_RTC->MIN=dateTime->tm_min;
	if((mask & HOUR_MASK)>0)
		LPC_RTC->HOUR=dateTime->tm_hour;
	if((mask & DOM_MASK)>0)
		LPC_RTC->DOM=dateTime->tm_mday;
	if((mask & DOW_MASK)>0)
		LPC_RTC->DOW=dateTime->tm_wday;
	if((mask & DOY_MASK)>0)
		LPC_RTC->DOY=(dateTime->tm_yday)+MONTH_ADJUSTMENT;
	if((mask & MONTH_MASK)>0)
		LPC_RTC->MONTH=(dateTime->tm_mon)+DOY_ADJUSTMENT;
	if((mask & YEAR_MASK)>0)
		LPC_RTC->YEAR=(dateTime->tm_year)%MAX_YEAR;
	LPC_RTC->CCR|=CLKEN_ENABLE;
}

void RTC_SetValue(struct tm *dateTime){
	LPC_RTC->CCR|=CLKEN_DISABLE;
	LPC_RTC->SEC=(dateTime->tm_sec)%MAX_SEC;
	LPC_RTC->MIN=dateTime->tm_min;
	LPC_RTC->HOUR=dateTime->tm_hour;
	LPC_RTC->DOM=dateTime->tm_mday;
	LPC_RTC->DOW=dateTime->tm_wday;
	LPC_RTC->DOY=(dateTime->tm_yday)+MONTH_ADJUSTMENT;
	LPC_RTC->MONTH=(dateTime->tm_mon)+DOY_ADJUSTMENT;
	LPC_RTC->YEAR=(dateTime->tm_year)%MAX_YEAR;
	LPC_RTC->CCR|=CLKEN_ENABLE;
}

void RTC_SetSconds(time_t seconds){
	init_RTC(seconds);
}

time_t RTC_GetSeconds(void){
	struct tm dateTime;
	RTC_GetValue(&dateTime);
	time_t ret=mktime(&dateTime);
	return ret;
}
