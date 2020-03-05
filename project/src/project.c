/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, André Dias, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "menu.h"

int main(void) {
	void *(*menu_execute)()=&init_menu;
    while(1) {
    	menu_execute=menu_execute();
    }
    return 0 ;
}
