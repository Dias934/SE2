/*
 * button_task.h
 *
 *  Created on: 15/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#ifndef PROJECTTASKS_BUTTON_TASK_H_
#define PROJECTTASKS_BUTTON_TASK_H_

#include "project_tasks.h"

#define BUTTON_TASK_NAME "Button"
#define BUTTON_STACK_SIZE (configMINIMAL_STACK_SIZE)

#define WAIT_FOR_BUTTON_TIMEOUT 10


void buttons_task();

void get_buttons_map(int *button_map);

#endif /* PROJECTTASKS_BUTTON_TASK_H_ */
