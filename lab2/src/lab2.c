/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, André Dias, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "peripherals.h"
#include "stdio.h"
#include "string.h"

void withoutInterrupt(){
	UART_Initialize(9600,false);
	int tstCh = '0';
	while (1) {
		LCDText_Locate(0, 0);
		turn_on_led();
		UART_WriteChar(tstCh);
		if (++tstCh > '9') tstCh = '0';
		turn_off_led();
		LCDText_Printf("rx = %c\n", UART_ReadChar());
	}
}

void withInterrupt(){
	int dlen = sizeof("Hello world. How you doing? This is just to test a very long sentence...");
	UART_Initialize(115200,true);
	while (1) {
		char *data=malloc(100);
		UART_WriteBuffer("Hello world. How you doing? This is just to test a very long sentence...",dlen);
		wait_ms(10);
		UART_ReadBuffer(data, dlen);
		printf("%s\n", data);
		free(data);
	}
}

int main(void) {
	init_peripherals();
	//withoutInterrupt();
	withInterrupt();
	return 0 ;
}



