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

LCD_CMD_TYPEDEF* cmd;

void view_init(char * s){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_INIT;
	cmd->args=my_malloc(strlen(s));
	memcpy(cmd->args, s, strlen(s)+1);
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}

void view_init_result(char * s){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_INIT_RESULTS;
	cmd->args=my_malloc(strlen(s));
	memcpy(cmd->args, s, strlen(s)+1);
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}

void view_normal(DATA_TYPEDEF data){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_NORMAL;
	cmd->args=my_malloc(sizeof(DATA_TYPEDEF));
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}

void view_select_maintenance(short idx){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_SELECT_MAINTENANCE;
	cmd->args=my_malloc(sizeof(short));
	memcpy(cmd->args, &idx, sizeof(short));
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}

void view_time_maintenance(short field, struct tm *calendar){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_TIME_MAINTENANCE;
	cmd->args=my_malloc(sizeof(short) + sizeof(struct tm));
	memcpy(cmd->args, &field, sizeof(short));
	memcpy(cmd->args+sizeof(short), &calendar, sizeof(struct tm));
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}

void view_calendar_maintenance(short field, struct tm *calendar){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_CALENDAR_MAINTENANCE;
	cmd->args=my_malloc(sizeof(short) + sizeof(struct tm));
	memcpy(cmd->args, &field, sizeof(short));
	memcpy(cmd->args+sizeof(short), &calendar, sizeof(struct tm));
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}

void view_temperature_unit_maintenance(){
	cmd=my_malloc(sizeof(LCD_CMD_TYPEDEF));
	cmd->cmd=VIEW_TEMPERATURE_MAINTENANCE;
	xQueueSend(View_Queue, cmd, portMAX_DELAY);
	my_free(cmd);
}
