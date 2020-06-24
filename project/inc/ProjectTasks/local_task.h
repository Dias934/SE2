/*
 * local_task.h
 *
 *  Created on: 15/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#ifndef PROJECTTASKS_LOCAL_TASK_H_
#define PROJECTTASKS_LOCAL_TASK_H_

#include "project_tasks.h"

#define WAIT_FOR_BUTTON_TIMEOUT 10

#define LOCAL_TASK_NAME "Local"
#define LOCAL_STACK_SIZE (configMINIMAL_STACK_SIZE*2)

#define END_LOCAL_INIT "End  Local Init"

extern TaskHandle_t *Local_Task;

void local_task();

#endif /* PROJECTTASKS_LOCAL_TASK_H_ */
