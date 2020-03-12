/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, André Dias, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "init_menu.h"

int main(void) {
	void *(*menu_execute)()=&start_inits;
    while(1) {
    	menu_execute=menu_execute();
    }
    return 0 ;
}
