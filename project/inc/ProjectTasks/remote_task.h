/*
 * remote_task.h
 *
 *  Created on: 01/07/2020
 *      Author: Manuel
 */

#ifndef PROJECTTASKS_REMOTE_TASK_H_
#define PROJECTTASKS_REMOTE_TASK_H_

#include "project_tasks.h"
#include "my_types.h"

#define REMOTE_TASK_NAME "Remote"
#define REMOTE_STACK_SIZE (configMINIMAL_STACK_SIZE*10)

enum REMOTE_TASK{
	CHANGE_TIME=0,
	SEND_DATA
};

void remote_task();

bool time_request(time_t *time);

bool send_to_remote(DATA_TYPEDEF data);

#endif /* PROJECTTASKS_REMOTE_TASK_H_ */
