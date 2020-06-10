/*
 * lcd_task.c
 *
 *  Created on: 09/06/2020
 *      Author: Manuel Dias, Ricardo Romano
 */

#include "project_tasks.h"

void LCD_Task(){
	init_LCDText();
	char str[16];
	while(1){
		xQueueReceive(LCD_Queue, str, portMAX_DELAY);
		LCDText_Clear();
		LCDText_WriteString(str);
		wait_ms(300);
	}
}
