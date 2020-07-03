/*
 * e2prom_task.h
 *
 *  Created on: 25/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#ifndef PROJECTTASKS_E2PROM_TASK_H_
#define PROJECTTASKS_E2PROM_TASK_H_

#include "project_tasks.h"
#include "my_types.h"

#define E2PROM_TASK_NAME 	"E2prom"
#define E2PROM_STACK_SIZE 	(5*configMINIMAL_STACK_SIZE)

#define E2PROM_QUEUE_SIZE 	5

#define WAIT_TO_WRITE		2000
#define WAIT_TO_READ		5000

enum E2PROM_CMD{
	WRITE =0,
	READ
};

typedef struct{
	unsigned short cmd;
	unsigned short addr;
	unsigned short size;
	unsigned short *buff;
}E2PROM_MSG_TYPEDEF;


void e2prom_task();

bool get_stored_data(unsigned short addr, unsigned short *buff, unsigned short size);

bool set_stored_data(unsigned short addr, unsigned short *buff, unsigned short size);

#endif /* PROJECTTASKS_E2PROM_TASK_H_ */
