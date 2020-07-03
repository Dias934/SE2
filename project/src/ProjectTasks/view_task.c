/*
 * lcd_task.c
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include <ProjectTasks/view_task.h>
#include "peripherals.h"
#include "init_menu.h"
#include "format_view.h"
#include <string.h>

TaskHandle_t *View_Task;
QueueHandle_t View_Queue;

static char str[16];

static char * MAINTENANCE_CHANGE_TITLE[]={"Change Time","Change Date","Change Temp. Un"};

//static void (*select_format[])()={&format_time, &format_calendar, &format_temperature_unit};


void view_task(){
	View_Queue= xQueueCreate(10, sizeof(CMD_TYPEDEF));
	CMD_TYPEDEF lcd_cmd;
	taskENTER_CRITICAL();
	init_peripherals();
	taskEXIT_CRITICAL();
	while(1){
		xQueueReceive(View_Queue, &lcd_cmd, portMAX_DELAY);
		switch(lcd_cmd.cmd){
			case VIEW_INIT: view_task_init(lcd_cmd.args); wait_ms(300); break;
			case VIEW_INIT_RESULTS: view_task_init_result(lcd_cmd.args); wait_ms(300); break;
			case VIEW_NORMAL: view_task_normal(*((DATA_TYPEDEF *)lcd_cmd.args)); break;
			case VIEW_TEST: view_test(*((int *)lcd_cmd.args) ); break;
			case VIEW_SELECT_MAINTENANCE: view_task_select_maintenance(lcd_cmd.args); break;
			case VIEW_TIME_MAINTENANCE: view_task_time_maintenance(lcd_cmd.args); break;
			case VIEW_CALENDAR_MAINTENANCE: view_task_calendar_maintenance(lcd_cmd.args); break;
			case VIEW_TEMPERATURE_MAINTENANCE: view_task_temperature_unit_maintenance(*((unsigned short *)lcd_cmd.args)); break;
		}
		if(lcd_cmd.args_size>0)
			my_free(lcd_cmd.args);
	}
}




void view_task_init(char * s){
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	LCDText_WriteString("Initializing:");
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	LCDText_WriteString(s);
}

void view_task_init_result(char * s){
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	LCDText_WriteString(s);
}

void view_task_normal(DATA_TYPEDEF data){
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	format_full_calendar(data.cal, str);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_temperature_pressure(data.sensor_info.temp, data.sensor_info.press, str, data.unit);
	LCDText_WriteString(str);
}

void view_task_select_maintenance(void * args){
	short idx=0;
	DATA_TYPEDEF data;
	memcpy(&idx, args, sizeof(short));
	memcpy(&data, args+sizeof(short), sizeof(DATA_TYPEDEF));
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	if(idx<2)
		sprintf(str,"%s%5c",MAINTENANCE_CHANGE_TITLE[idx],' ');
	else
		sprintf(str,"%s",MAINTENANCE_CHANGE_TITLE[idx]);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	switch(idx){
		case TIME_MAINT: format_time(data.cal, str); break;
		case CAL_MAINT:	format_calendar(data.cal, str); break;
		case TEMP_UNIT_MAINT: format_temperature_unit(str, data.unit); break;
	}
	LCDText_WriteString(str);
}

void view_task_time_maintenance(void * args){
	short field=0;
	struct tm calendar;
	memcpy(&field, args, sizeof(short));
	memcpy(&calendar, args+sizeof(short), sizeof(struct tm));
	LCDText_Locate(0,0);
	sprintf(str,"%s%5c",MAINTENANCE_CHANGE_TITLE[0],' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_time_maintenance(calendar, str);
	LCDText_WriteString(str);
	LCDText_Locate(1,field*3+1);
	LCDText_Cursor(CURSOR_ON);
}

void view_task_calendar_maintenance(void * args){
	short field=0;
	struct tm calendar;
	memcpy(&field, args, sizeof(short));
	memcpy(&calendar, args+sizeof(short), sizeof(struct tm));
	LCDText_Locate(0,0);
	sprintf(str,"%s%5c",MAINTENANCE_CHANGE_TITLE[1],' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_calendar_maintenance(calendar, str);
	LCDText_WriteString(str);
	if(field==0)
		LCDText_Locate(1,9);
	else
		LCDText_Locate(1,7-field*3);
	LCDText_Cursor(CURSOR_ON);
}

void view_task_temperature_unit_maintenance(unsigned short unit){
	LCDText_Locate(0,0);
	sprintf(str,"%s",MAINTENANCE_CHANGE_TITLE[2]);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_temperature_unit(str, unit);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	LCDText_Cursor(CURSOR_ON);
}

void view_test(int button){
	LCDText_Cursor(CURSOR_OFF);
	LCDText_Locate(0,0);
	sprintf(str,"%16c", ' ');
	LCDText_WriteString(str);
	LCDText_Locate(0,0);
	sprintf(str,"b: %d",button);
	LCDText_WriteString(str);
}

void send_to_view(int cmd_idx, void * args, int args_size, int terminator){
	if(View_Queue != NULL){
		CMD_TYPEDEF * cmd=my_malloc(sizeof(CMD_TYPEDEF));
		cmd->cmd=cmd_idx;
		cmd->args_size=args_size;
		if(args_size>0){
			cmd->args=my_malloc(args_size);
			memcpy(cmd->args, args, args_size + terminator);
		}
		xQueueSend(View_Queue, cmd, 1);
		my_free(cmd);
	}
}
