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

TaskHandle_t *View_Task;
QueueHandle_t View_Queue;
LCD_CMD_TYPEDEF lcd_cmd;

static char str[16];

//static char * MAINTENANCE_CHANGE_TITLE[]={"Change Time","Change Date","Change Temp. Un"};

static char TEMPERATURE_UNIT[2]={'C','F'};

static char SEC_CHARACTER[2]={' ',':'};

//static void (*select_format[])()={&format_time, &format_calendar, &format_temperature_unit};


void view_task(){
	if(View_Queue == NULL)
		View_Queue= xQueueCreate(10, sizeof(LCD_CMD_TYPEDEF));
	taskENTER_CRITICAL();
	init_peripherals();
	taskEXIT_CRITICAL();
	while(1){
		xQueueReceive(View_Queue, &lcd_cmd, portMAX_DELAY);
		switch(lcd_cmd.cmd){
			case VIEW_INIT: view_task_init(lcd_cmd.args); break;
			case VIEW_INIT_RESULTS: view_task_init_result(lcd_cmd.args); break;
			case VIEW_NORMAL: view_task_normal(*((DATA_TYPEDEF *)lcd_cmd.args)); break;
			case VIEW_TEST: view_test(*((int *)lcd_cmd.args) ); break;
		}
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
	format_full_calendar(&data.cal, str, SEC_CHARACTER[data.cal.tm_sec%2]);
	LCDText_WriteString(str);
	LCDText_Locate(1,0);
	format_temperature_pressure(data.sensor_info.temp, data.sensor_info.press, str, TEMPERATURE_UNIT[data.unit]);
	LCDText_WriteString(str);
}

void view_task_select_maintenance(short idx){

}

void view_task_time_maintenance(short field, struct tm *calendar){

}

void view_task_calendar_maintenance(short field, struct tm *calendar){

}

void view_task_temperature_unit_maintenance(){

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
