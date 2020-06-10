/*
 * 24AA256.c
 *
 *  Created on: 13/03/2020
 *      Author: A38866
 */

#include "24AA256.h"
#include "string.h"
#include "wait.h"
#include "stdlib.h"

uint32_t timeout=0;

int init_24AA256(unsigned short id_addr){
	I2C_InitBus(I2C_CHOSEN_BUS);
	return 1;
}

int byte_write(unsigned short addr, unsigned short data){
	if(addr> MAX_ADDR)
		return OUT_OF_BOUNDS;
	int ret=I2C_ConfigTransfer(I2C_FAST_FREQUENCY, HALF_DUTY, I2C_CHOSEN_BUS);
	if(ret==CONFIG_OK){
		unsigned short tx[]={addr>>8,addr,data};
		ret=I2C_Write(SLA_ADDR| I2C_W, tx, 3,I2C_CHOSEN_BUS);
		if(ret==WRITE_OK)
			wait_ms(BYTE_TRANSF_TIME);
	}
	return ret;
}

int execute_page_write(unsigned short addr, unsigned short * tx_buffer, unsigned short length){
	int ret=0;
	unsigned short tx[2+length];
	tx[0]=addr>>8;
	tx[1]=addr;
	for(int i=0;i<length;i++)
		tx[2+i]=tx_buffer[i];
	ret=I2C_Write(SLA_ADDR| I2C_W, tx, 2+length,I2C_CHOSEN_BUS);
	return ret;
}

int page_write(unsigned short addr, unsigned short * tx_buffer, unsigned short length){
	if(addr>MAX_ADDR || MAX_ADDR-addr<length)
		return OUT_OF_BOUNDS;
	int ret=I2C_ConfigTransfer(I2C_FAST_FREQUENCY, HALF_DUTY, I2C_CHOSEN_BUS);
	if(ret==CONFIG_OK){
		unsigned short page_avai=addr/PAGE_SIZE; 		//gets the address of the beggining page
		page_avai=PAGE_SIZE-addr-page_avai*PAGE_SIZE; 	//calculate the available size on that page
		if(length<=page_avai) 							//if this write is smaller than the page availability of the current page
			ret=execute_page_write(addr,tx_buffer,length);
		else{ 											//multiple page write in different pages
			unsigned short size=page_avai;
			ret=execute_page_write(addr,tx_buffer,size);
			timeout=0;
			addr+=page_avai;
			for(int i=0;ret==WRITE_OK && i*PAGE_SIZE+page_avai<length;i++){
				timeout=wait_elapsed(timeout);
				while(get_i2c_state(I2C_CHOSEN_BUS)!=0 && wait_elapsed(timeout)<=TRANSF_TIMEOUT);
				if(wait_elapsed(timeout)>TRANSF_TIMEOUT)
					return TIMEOUT_ERROR;
				timeout=0;
				if(tx_successful(I2C_CHOSEN_BUS)==UNSUCC)
					return UNSUCC;
				if(length-i*PAGE_SIZE-page_avai>PAGE_SIZE)
					size=PAGE_SIZE;
				else
					size=length-i*PAGE_SIZE-page_avai;
				wait_ms(BYTE_TRANSF_TIME);
				ret=execute_page_write(addr,&(tx_buffer[i*PAGE_SIZE+page_avai]),size);
				addr+=size;
			}
			while(get_i2c_state(I2C_CHOSEN_BUS)!=0);
		}
	}
	return ret;
}

int current_read(unsigned short *rx){
	int ret=I2C_ConfigTransfer(I2C_FAST_FREQUENCY, HALF_DUTY, I2C_CHOSEN_BUS);
	if(ret==CONFIG_OK)
		ret=I2C_OnlyRead(SLA_ADDR, rx, 1, I2C_CHOSEN_BUS);
	return ret;
}

int random_read(unsigned short addr, unsigned short *rx){
	int ret=I2C_ConfigTransfer(I2C_FAST_FREQUENCY, HALF_DUTY, I2C_CHOSEN_BUS);
	if(ret==CONFIG_OK){
		unsigned short tx[]={addr>>8,addr};
		ret=I2C_WriteRead(SLA_ADDR, tx, 2, rx, 1, I2C_CHOSEN_BUS);
	}
	return ret;
}

int sequential_read(unsigned short addr, unsigned short * rx_buffer, unsigned short length){
	int ret=I2C_ConfigTransfer(I2C_FAST_FREQUENCY, HALF_DUTY, I2C_CHOSEN_BUS);
	if(ret==CONFIG_OK){
		unsigned short tx[]={addr>>8,addr};
		ret=I2C_WriteRead(SLA_ADDR, tx, 2, rx_buffer, length, I2C_CHOSEN_BUS);
	}
	return ret;
}

int is_reading(){
	int ret=get_i2c_state(I2C_CHOSEN_BUS);
	if(ret==0)
		return rx_successful(I2C_CHOSEN_BUS);
	return READING;
}

