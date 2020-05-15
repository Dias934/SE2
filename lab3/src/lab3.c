/*
===============================================================================
 Name        : project.c
 Author      : $(Ricardo Romano, Manuel Dias)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "peripherals.h"
#include "ESP01.h"
#include "stdio.h"
#include "string.h"

void test_ESP(){
	init_ESP01(115200);
	int len=200;
	char *data=malloc(len);
	uint32_t s = 0;
	int i=0;
	while (1) {
		if(ESP_mode==AT_IDLE){
			if(i==0)
				test_AT();
			else if(i==1)
				version_AT();
			else if(i==2)
				WIFI_mode_curr_AT(1);
			else if(i==3)
				WIFI_list_AT();
			else if(i==4)
				query_WIFI_conn_AP();
			else if(i==5)
				printf("\n status: %d\n",point_conn_status());
			else if(i==6)
				set_WIFI_conn_AP("MEO-788DA","D1ASP4SS");
			else if(i==7)
				point_conn_status();
			else if(i==11)
				start_point_conn("TCP","iot-se1920.ddns.net",8090);
			else if(i==12)
				point_conn_status();
			else if(i==13)
				send_data(strlen("GET / \r\n\r\n"),"GET / \r\n\r\n");
			else if(i==17)
				execute_close_point_conn();
			else if(i==18)
				point_conn_status();
			i++;
		}
		s=feedback_CMD(data, len);
		if(s!=0)
			printf("%s", data);
	}
}

int main(void) {
	init_peripherals();
	test_ESP();
	return 0 ;
}



