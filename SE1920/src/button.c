/*
 * button.c
 *
 *  Created on: 03/10/2019
 *      Author: A38866
 */

#include <button.h>

BUTTONS_STATE_TYPEDEF buttons_state={0,0,0};

void init_BUTTON(void){
	LPC_PINCON->PINSEL4 &=~((PINCFG_PULLUP<<PINCFG_UP_BUTTON) | (PINCFG_PULLUP<<PINCFG_DOWN_BUTTON) | (PINCFG_PULLUP<<PINCFG_ENTER_BUTTON));
	LPC_PINCON->PINMODE4 &=~((PINCFG_PULLUP<<PINCFG_UP_BUTTON) | (PINCFG_PULLUP<<PINCFG_DOWN_BUTTON) | (PINCFG_PULLUP<<PINCFG_ENTER_BUTTON));
	LPC_GPIO2->FIODIR |=(0<<UP_BUTTON_PIN)|(0<<DOWN_BUTTON_PIN)|(0<<ENTER_BUTTON_PIN);
}

int BUTTON_Hit(void){
	uint32_t bitmap=LPC_GPIO2->FIOPIN & BUTTONS_MASK;
	bitmap= ~(bitmap^(~BUTTONS_MASK)); //trocar para lógica positiva
	return bitmap;
}

int BUTTON_Read(void){
	uint32_t bitmap=0;
	while(bitmap==0) bitmap=BUTTON_Hit();
	return bitmap;
}

void BUTTON_check(uint32_t val, short *button){
	if(*button == NOT_PRESSED){
		if(val>0) *button=PRESSED;
	}
	else if(*button == PRESSED){
		if(val>0) *button=PRESSING;
		else *button=RELEASED;
	}
	else if(*button == PRESSING){
		if(val==0) *button=RELEASED;
	}
	else if(*button == RELEASED){
		if(val>0) *button=PRESSED;
		else *button=NOT_PRESSED;
	}
}

int BUTTON_GetButtonsEvents(void){
	uint32_t bitmap=BUTTON_Hit();
	uint32_t a_mask[3]={UP_BUTTON_MASK, DOWN_BUTTON_MASK, ENTER_BUTTON_MASK,};
	for(int i=0;i<3;i++)
		BUTTON_check(bitmap&a_mask[i],(&buttons_state.up)+i);
	return buttons_state.up | buttons_state.down<<2 | buttons_state.enter<<4;
}
