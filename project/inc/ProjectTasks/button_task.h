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

extern TaskHandle_t *Button_Task;

void buttons_task();

#endif /* PROJECTTASKS_BUTTON_TASK_H_ */
