/*
 * local_task.h
 *
 *  Created on: 15/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#ifndef PROJECTTASKS_LOCAL_TASK_H_
#define PROJECTTASKS_LOCAL_TASK_H_

#include "project_tasks.h"
#include "my_types.h"

#define LOCAL_TASK_NAME "Local"
#define LOCAL_STACK_SIZE (configMINIMAL_STACK_SIZE*2)

#define END_LOCAL_INIT "End Local Init"
#define INIT_WAIT_DELAY 10

void local_task();

void send_to_local(DATA_TYPEDEF data);

#endif /* PROJECTTASKS_LOCAL_TASK_H_ */
