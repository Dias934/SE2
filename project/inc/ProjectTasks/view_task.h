/*
 * lcd_task.h
 *
 *  Created on: 15/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#ifndef PROJECTTASKS_VIEW_TASK_H_
#define PROJECTTASKS_VIEW_TASK_H_

#include <data_center.h>
#include "project_tasks.h"


#define VIEW_TASK_NAME "View"
#define VIEW_STACK_SIZE (configMINIMAL_STACK_SIZE*3)


extern TaskHandle_t *View_Task;


typedef struct{
	short cmd;
	void *args;
}LCD_CMD_TYPEDEF;

enum VIEW_CASES{
	VIEW_INIT=0,
	VIEW_INIT_RESULTS,
	VIEW_NORMAL,
	VIEW_SELECT_MAINTENANCE,
	VIEW_TIME_MAINTENANCE,
	VIEW_CALENDAR_MAINTENANCE,
	VIEW_TEMPERATURE_MAINTENANCE,
	VIEW_TEST
};

void view_task();

void view_task_init(char * s);

void view_task_init_result(char * s);

void view_task_normal();

void view_task_select_maintenance(short idx);

void view_task_time_maintenance(short field, struct tm *calendar);

void view_task_calendar_maintenance(short field, struct tm *calendar);

void view_task_temperature_unit_maintenance();

void view_test(int button);

#endif /* PROJECTTASKS_VIEW_TASK_H_ */
