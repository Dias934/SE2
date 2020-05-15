/*
 * ESP01.c
 *
 *  Created on: 05/05/2020
 *      Author: Manuel Dias e Ricardo Romano
 */
#include "ESP01.h"
#include "string.h"

int ESP_mode;
uint32_t passed_time;	//time has passed since sending the command
uint32_t timeout;		//timeout threshold
uint32_t fill_interval; //counter to let the buffer fill with data
int response_idx;		//index of response, in case the response comes splitted
int n_bytes;			//number of bytes remaining of a send response

void reset_mode(){
	UART_Flush();
	ESP_mode=AT_IDLE;
	passed_time=0;
	timeout=MINIMUM_TIMEOUT;
	fill_interval=0;
	response_idx=0;
}

void init_ESP01(int baudRate){
	UART_Initialize(baudRate, true);
	LPC_PINCON->PINSEL0&=~(GPIO_FUNC_L<<RST_CONF_POS);
	LPC_GPIO0->FIODIR|=(1<<RST_PIN);
	LPC_GPIO0->FIOSET=(1<<RST_PIN);
	LPC_GPIO0->FIOCLR=(1<<RST_PIN);
	wait_ms(RST_WAITING_TIME);
	LPC_GPIO0->FIOSET=(1<<RST_PIN);
	wait_ms(2000);
	reset_mode();
}

int check_response(int bytes, char* data, int resp_size, char *resp){
	for(int i=0; i<bytes; i++){
		if(data[i]==resp[response_idx]){
			if(++response_idx==resp_size)
				return i;
		}
		else
			response_idx=0;
	}
	return -1;
}

int read_cmd_response(char * data, int len){
	int bytes=0;
	if(wait_elapsed(passed_time)>timeout){	//if timeout expires
		bytes= (int) UART_ReadBuffer(data, len);
		reset_mode();
	}
	else{	//timeout has not expires
		if(fill_interval!=0){	//if the current cmd needs time to fill the buffer
			if(wait_elapsed(fill_interval)> FILL_INTERVAL){	//if the fill interval has passed
				bytes= (int) UART_ReadBuffer(data, len);
				fill_interval=wait_elapsed(0);
			}
		}
		else	//if the current cmd doesn't need time to fill the buffer
			bytes= (int) UART_ReadBuffer(data, len);
	}
	return bytes;
}

int send_response(char * data, int len){
	int bytes=read_cmd_response(data, len);
	if(bytes != 0 ){	//if we received a message
		if(n_bytes<0){
			int idx=check_response(bytes, data, RECEIVED_DATA_RESPONSE_SIZE, RECEIVED_DATA_RESPONSE); //starting idx, filter "+IPD,"
			if(  idx >= 0){
				int end_idx=check_response(bytes, data, 1, ":"); //get number of bytes of message response
				char * str=malloc(end_idx-idx-1);
				memcpy(str, data+idx+1, end_idx-idx-1);
				n_bytes=atoi(str);
				n_bytes-=bytes-end_idx+1;
				data=data+end_idx+1;	//filter ESP command
			}
		}
		if((n_bytes-=bytes )<=0) //if we read all the data then go to IDLE mode
			reset_mode();
	}
	return bytes;
}

int ESP_cmd_response(char * data, int len){
	int bytes=read_cmd_response(data, len);
	if(bytes !=0 ){	//if we received a message
		if( check_response(bytes, data, RESPONSE_END_SIZE, RESPONSE_END) >= 0)
			reset_mode();
	}
	return bytes;
}

int feedback_CMD(char * data, int len){
	int bytes=0;
	switch(ESP_mode){
	case AT_IDLE: break;
	case AT_SET_CWJAP_CUR:{ //avoid printing the wifi password
		char * str=malloc(20);
		bytes=ESP_cmd_response(str, 20);
		free(str);
		break;
	}
	case AT_SET_CIPSEND: bytes=send_response(data, len); break;
	default: bytes=ESP_cmd_response(data, len);
	}
	if(bytes<len)	//ignore garbage
		data[bytes]=0;
	return bytes;
}

void test_AT(){
	if(ESP_mode==AT_IDLE){
		char aux[5];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(aux,CMD_END), strlen(aux));
		ESP_mode=AT;
		passed_time=wait_elapsed(0);
	}
}

void reset_AT(){
	if(ESP_mode==AT_IDLE){
		char aux[10];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_RST),CMD_END), strlen(aux));
		ESP_mode=AT_RST;
		passed_time=wait_elapsed(0);
	}
}

void version_AT(){
	if(ESP_mode==AT_IDLE){
		char aux[10];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_GMR),CMD_END), strlen(aux));
		ESP_mode=AT_GMR;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}

void WIFI_mode_curr_AT(int mode){
	if(ESP_mode==AT_IDLE){
		char * str=malloc(20);
		sprintf(str, "%d", mode);
		char aux[20];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(strcat(aux,CMD_SET_CWMODE_CUR),str),CMD_END),strlen(aux));
		ESP_mode=AT_SET_CWMODE_CUR;
		passed_time=wait_elapsed(0);
	}
}

void WIFI_list_AT(){
	if(ESP_mode==AT_IDLE){
		char aux[10];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_EX_CWLAP),CMD_END), strlen(aux));
		ESP_mode=AT_EX_CWLAP;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
		timeout=CWLAP_TIMEOUT;
	}
}

void set_WIFI_conn_AP(char * ssid, char * pwd){
	if(ESP_mode==AT_IDLE){
		char aux[17+strlen(ssid)+strlen(pwd)];
		strcpy(aux,CMD_START);
		strcat(aux,CMD_SET_CWJAP_CUR);
		strcat(strcat(strcat(strcat(aux,"\""),ssid),"\""),",");
		strcat(strcat(strcat(aux,"\""),pwd),"\"");
		UART_WriteBuffer(strcat(aux,CMD_END), strlen(aux));
		ESP_mode=AT_SET_CWJAP_CUR;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
		timeout=CWLAP_TIMEOUT;
	}
}

void query_WIFI_conn_AP(){
	if(ESP_mode==AT_IDLE){
		char aux[15];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_QUERY_CWJAP_CUR),CMD_END), strlen(aux));
		ESP_mode=AT_QUERY_CWJAP_CUR;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}

void quit_WIFI_conn_AP(){
	if(ESP_mode==AT_IDLE){
		char aux[10];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_CWQAP),CMD_END), strlen(aux));
		ESP_mode=AT_CWQAP;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}

void point_conn_status(){
	if(ESP_mode==AT_IDLE){
		char aux[13];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_CIPSTATUS),CMD_END), strlen(aux));
		ESP_mode=AT_CIPSTATUS;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}

void start_point_conn(char * type, char * remote_ip, int remote_port){
	if(ESP_mode==AT_IDLE){
		char * str=malloc(20);
		sprintf(str, "%d", remote_port);
		char aux[23+strlen(remote_ip)+strlen(str)];
		strcpy(aux,CMD_START);
		strcat(aux,CMD_CIPSTART);
		strcat(strcat(strcat(strcat(aux,"\""),type),"\""),",");
		strcat(strcat(strcat(strcat(aux,"\""),remote_ip),"\""),",");
		strcat(aux,str);
		UART_WriteBuffer(strcat(aux,CMD_END), strlen(aux));
		ESP_mode=AT_CIPSTART;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}

void send_data(int length, char * data){
	if(ESP_mode==AT_IDLE){
		char * str=malloc(20);
		sprintf(str, "%d", length);
		char aux[12+strlen(str)];
		strcat(strcat(strcpy(aux,CMD_START),CMD_SET_CIPSEND),str);
		UART_WriteBuffer(strcat(aux,CMD_END), strlen(aux));
		ESP_mode=AT_SET_CIPSEND;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
		timeout=WAIT_WRAP_RETURN_TIMEOUT;
		bool exit=false;
		int bytes=0;
		while(wait_elapsed(passed_time)<=timeout && !exit){
			if(wait_elapsed(fill_interval) > FILL_INTERVAL){
				bytes=UART_ReadBuffer(str, 20);
				if(check_response(bytes, str, SEND_RESPONSE_SIZE, SEND_RESPONSE)>=0){
					exit=true;
					UART_Flush();
					UART_WriteBuffer(data, strlen(data));
				}
				fill_interval=wait_elapsed(0);
			}
		}
		if(!exit)
			reset_mode();
		else{
			passed_time=wait_elapsed(0);
			fill_interval=wait_elapsed(0);
			timeout=WAIT_SENDING_RESPONSE_TIMEOUT;
			n_bytes=-1;
		}
	}
}

void execute_close_point_conn(){
	if(ESP_mode==AT_IDLE){
		char aux[13];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_EX_CIPCLOSE),CMD_END), strlen(aux));
		ESP_mode=AT_EX_CIPCLOSE;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}

void get_local_IP_addr(){
	if(ESP_mode==AT_IDLE){
		char aux[10];
		strcpy(aux,CMD_START);
		UART_WriteBuffer(strcat(strcat(aux,CMD_CIFSR),CMD_END), strlen(aux));
		ESP_mode=AT_CIFSR;
		passed_time=wait_elapsed(0);
		fill_interval=wait_elapsed(0);
	}
}
