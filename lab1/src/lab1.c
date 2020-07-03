/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, André Dias, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <24AA256.h>
#include "peripherals.h"
#include "stdio.h"

void byte_test();

void multiple_byte_test();

int main(void) {
	//byte_test();
	multiple_byte_test();
    return 0 ;
}

void byte_test(){
	unsigned short i=0;
	unsigned short r=0;
	init_peripherals();
	init_24AA256(1);
	LCDText_Cursor(CURSOR_ON);
	while(1) {
		LCDText_Locate(0, 0);
		byte_write(6, i);
		LCDText_PrintBinary(i);
		LCDText_Locate(1, 0);
		random_read(6, &r);
		while(is_reading()!=DONE);
		LCDText_PrintBinary(r);
		wait_ms(250);
		i++;
	}
}

void multiple_byte_test(){
	init_peripherals();
	init_24AA256(1);
	unsigned short size=20;
	unsigned short addr=0x1F;
	unsigned short tx[size];
	unsigned short rx[size];
	unsigned short r=0;
	while(1) {
		for(int i=0;i<size;i++){
			tx[i]=r;
			r++;
			r%=256;
		}
		int ret=page_write(addr, tx, size);
		if(ret==WRITE_OK){
			printf("Writing done.\n");
			wait_ms(500);
			sequential_read(addr, rx, size);
			printf("Reading...\n");
			while(is_reading()!=SUCCESSFUL);
			int count=0;
			for(int i=0;i<size;i++){
				if(tx[i]!=rx[i]){
					count++;
					printf("idx: %d -> tx= %d, rx= %d\n", i, tx[i], rx[i]);
				}
			}
			if(count==0)
				printf("TEST PASSED!\n");
			else
				printf("TEST FAILED!\n");
			wait_ms(2000);
		}
		else{
			printf("ERROR %d",ret);
		}
	}
}
