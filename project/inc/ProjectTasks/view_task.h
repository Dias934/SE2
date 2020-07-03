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
#define VIEW_PRIORITY 	5

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

void view_task_normal(DATA_TYPEDEF data);

void view_task_select_maintenance(void *args);

void view_task_time_maintenance(void *args);

void view_task_calendar_maintenance(void *args);

void view_task_temperature_unit_maintenance(unsigned short unit);

void view_test(int button);

void send_to_view(int cmd_idx, void * args, int args_size, int terminator);

#endif /* PROJECTTASKS_VIEW_TASK_H_ */
