/**
* @file		BMP280.h
* @brief	Contains the sensor interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/

#ifndef ESP01_H_
#define ESP01_H_

#ifdef __USE_CMSIS
#include "peripherals.h" //o uart está incluido nesta lib
#include "LPC17xx.h"
#endif

#define RST_PIN 8
#define RST_CONF_POS (RST_PIN*2)
#define GPIO_FUNC_L 0x3

#define RST_WAITING_TIME 100
#define FILL_INTERVAL 250

#define MINIMUM_TIMEOUT 1000 //for commands that doesn't need timeout and they might get stuck
#define CWLAP_TIMEOUT 15000
#define WAIT_WRAP_RETURN_TIMEOUT 5000
#define WAIT_SENDING_RESPONSE_TIMEOUT 30000

#define CMD_START "AT"

#define CMD_RST "+RST"
#define CMD_GMR "+GMR"
#define CMD_SET_CWMODE_CUR "+CWMODE_CUR="
#define CMD_EX_CWLAP "+CWLAP"
#define CMD_SET_CWJAP_CUR "+CWJAP_CUR="
#define CMD_QUERY_CWJAP_CUR "+CWJAP_CUR?"
#define CMD_CWQAP "+CWQAP"
#define CMD_CIPSTATUS "+CIPSTATUS"
#define CMD_CIPSTART "+CIPSTART="
#define CMD_SET_CIPSEND "+CIPSEND="
#define CMD_EX_CIPSEND "+CIPSEND"
#define CMD_EX_CIPCLOSE "+CIPCLOSE"
#define CMD_CIFSR "+CIFSR"

#define CMD_END "\r\n"

#define RESPONSE_END "OK\r\n"
#define RESPONSE_END_SIZE 4

#define SEND_RESPONSE "> "
#define SEND_RESPONSE_SIZE 2

#define RECEIVED_DATA_RESPONSE "+IPD,"
#define RECEIVED_DATA_RESPONSE_SIZE 5


enum ESP_CMD_STATE{
	AT_IDLE=0,
	AT_POWER_UP,
	AT,
	AT_RST,
	AT_GMR,
	AT_SET_CWMODE_CUR,
	AT_EX_CWLAP,
	AT_SET_CWJAP_CUR,
	AT_QUERY_CWJAP_CUR,
	AT_CWQAP,
	AT_CIPSTATUS,
	AT_CIPSTART,
	AT_SET_CIPSEND,
	AT_EX_CIPCLOSE,
	AT_CIFSR
};

extern int ESP_mode;

void init_ESP01(int baudRate);

void test_AT();

void reset_AT();

void version_AT();

void WIFI_mode_curr_AT(int mode);

void WIFI_list_AT();

void set_WIFI_conn_AP(char * ssid, char * pwd);

void query_WIFI_conn_AP();

void quit_WIFI_conn_AP();

void point_conn_status();

void start_point_conn(char * type, char * remote_ip, int remote_port);

void send_data(int length, char * data);

void execute_close_point_conn();

void get_local_IP_addr();

int feedback_CMD(char * data, int len);

#endif /* ESP01_H_ */
