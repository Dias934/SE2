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
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ntp_packets.h"

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
				printf("\n status: %d\n",point_conn_status());
			else if(i==11)
				start_point_conn("UDP","iot-se1920.ddns.net",8090);
			else if(i==12)
				printf("\n status: %d\n",point_conn_status());
			else if(i==13)
				send_data(strlen("GET / \r\n\r\n"),"GET / \r\n\r\n");
			else if(i==17)
				printf("\n status: %d\n",point_conn_status());
			else if(i==18)
				point_conn_status();
			i++;
		}
		s=feedback_CMD(data, len);
		if(s!=0)
			printf("%s", data);
	}
}

void test_NTP_Single(){
	init_ESP01(115200);
	int len=100;
	char *data=malloc(len);
	Pntp_packet packet=malloc(PACKET_SIZE);
	uint32_t s = 0;
	int i=0;
	while (1) {
		if(ESP_mode==AT_IDLE){
			int status=point_conn_status();
			switch(status){
			case NO_AP: set_WIFI_conn_AP("MEO-788DA","D1ASP4SS"); break;
			case TRANS_DISC:
			case AP_AND_IP_OBTN:
			case TRANS_CONN:{
				if(i%4==0)
					set_mult(SINGLE);
				if(i%4==1)
					start_point_single_conn("UDP","pool.ntp.org", 123);
				else if(i%4==2){
					init_packet(packet);
					send_data_single((char*)packet, PACKET_SIZE);
					while(ESP_mode!=AT_IDLE)
						s=feedback_CMD((char*)packet, 48);
					correct_answer_packet(packet);
					char str[50];
					uitoa(packet->txTm_s, str, 10);
					printf("\n s:%s \n", str);
				}
				else
					execute_close_conn();
				i++;
				break;
				}
			}
		}
		s=feedback_CMD(data, len);
		if(s!=0)
			printf("%s\n", data);
	}
}

void test_NTP_Mult(){
	init_ESP01(115200);
	int len=100;
	char *data=malloc(len);
	Pntp_packet packet=malloc(PACKET_SIZE);
	uint32_t s = 0;
	int i=0;
	while (1) {
		if(ESP_mode==AT_IDLE){
			int status=point_conn_status();
			switch(status){
			case NO_AP: set_WIFI_conn_AP("MEO-788DA","D1ASP4SS"); break;
			case TRANS_DISC:
			case AP_AND_IP_OBTN:
			case TRANS_CONN:{
				if(i==0)
					set_mult(MULTIPLE);
				else if(i%6==1)
					start_point_mult_conn("UDP","pool.ntp.org", 123, ID0);
				else if(i%6==2)
					start_point_mult_conn("UDP","pool.ntp.org", 123, ID1);
				else if(i%6==3 || i%6==4){
					init_packet(packet);
					if(i%6==3)
						send_data_mult((char*)packet, PACKET_SIZE, ID0);
					else
						send_data_mult((char*)packet, PACKET_SIZE, ID1);
					while(ESP_mode!=AT_IDLE)
						s=feedback_CMD((char*)packet, 48);
					correct_answer_packet(packet);
					char str[50];
					uitoa(packet->txTm_s, str, 10);
					printf("\n s:%s \n", str);
					time_t time=packet->txTm_s;
					struct tm *utc;
					utc=gmtime(&time);
					printf("%d/%d/%d %d:%d:%d\n", utc->tm_mday, utc->tm_mon+1, utc->tm_year+1830, utc->tm_hour+1, utc->tm_min, utc->tm_sec);
				}
				else{
					if(i%6==5)
						execute_close_point_conn(ID0);
					else
						execute_close_point_conn(ID1);
				}
				i++;
				break;
				}
			}
		}
		s=feedback_CMD(data, len);
		if(s!=0)
			printf("%s\n", data);
	}
}

int main(void) {
	init_peripherals();
	//test_ESP();
	test_NTP_Single();
	//test_NTP_Mult();
	return 0 ;
}



