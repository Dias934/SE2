   /*
 * ViewLCDText.c
 *
 *  Created on: 10/03/2020
 *      Author: A38866
 */

#include "viewLCDText.h"
#include "ProjectTasks/view_task.h"
#include "mem_allocation.h"
#include <string.h>

void view_init(char * s){
	send_to_view(VIEW_INIT, s, strlen(s) , 1);
}

void view_init_result(char * s){
	send_to_view(VIEW_INIT_RESULTS, s, strlen(s) , 1);
}

void view_normal(DATA_TYPEDEF data){
	send_to_view(VIEW_NORMAL, &data, sizeof(DATA_TYPEDEF) , 1);
}

void view_select_maintenance(short idx, DATA_TYPEDEF data){
	void *args=my_malloc(sizeof(short)+sizeof(DATA_TYPEDEF));
	memcpy(args, &idx, sizeof(short));
	memcpy(args+sizeof(short), &data, sizeof(DATA_TYPEDEF));
	send_to_view(VIEW_SELECT_MAINTENANCE, args, sizeof(short)+sizeof(DATA_TYPEDEF) , 1);
	my_free(args);
}

void view_time_maintenance(short field, struct tm calendar){
	void *args=my_malloc(sizeof(short)+sizeof(struct tm));
	memcpy(args, &field, sizeof(short));
	memcpy(args+sizeof(short), &calendar, sizeof(struct tm));
	send_to_view(VIEW_TIME_MAINTENANCE, args, sizeof(short)+sizeof(struct tm) , 1);
	my_free(args);
}

void view_calendar_maintenance(short field, struct tm calendar){
	void *args=my_malloc(sizeof(short)+sizeof(struct tm));
	memcpy(args, &field, sizeof(short));
	memcpy(args+sizeof(short), &calendar, sizeof(struct tm));
	send_to_view(VIEW_CALENDAR_MAINTENANCE, args, sizeof(short)+sizeof(struct tm) , 1);
	my_free(args);
}

void view_temperature_unit_maintenance(unsigned short unit){
	send_to_view(VIEW_TEMPERATURE_MAINTENANCE, &unit, sizeof(unsigned short) , 1);
}
