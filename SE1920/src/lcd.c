#include "lcd.h"

short row;
short col;

static void LCDText_Send_4bits(int  rs, int data){
	if(rs==DATA)
		LPC_GPIO1->FIOSET|=(1<<LCD_RS);
	else
		LPC_GPIO1->FIOCLR|=(1<<LCD_RS);
	LPC_GPIO0->FIOCLR|= (0xF<<LCD_DB4);
	LPC_GPIO0->FIOSET|= ((0xF&data)<<LCD_DB4);
	LPC_GPIO1->FIOSET|=(1<<LCD_ENABLE);
	wait_ChronoUs(1);
	LPC_GPIO1->FIOCLR|=(1<<LCD_ENABLE);
	wait_ChronoUs(1);
}

static void LCDText_Write_4bits(int rs, int data){
	LCDText_Send_4bits(rs,data>>4); //sends high part
	LCDText_Send_4bits(rs,data);    //sends low part
	wait_ChronoUs(37);
}

void init_LCDText(void){
	LPC_PINCON->PINSEL1 &=~((3<<PINCFG_DB4) | (3<<PINCFG_DB5) | (3<<PINCFG_DB6) | (3<<PINCFG_DB7));
	LPC_PINCON->PINSEL3 &=~((3<<PINCFG_ENABLE) | (3<<PINCFG_RS));
	LPC_GPIO0->FIODIR|=(1<<LCD_DB4)|(1<<LCD_DB5)|(1<<LCD_DB6)|(1<<LCD_DB7);
	LPC_GPIO1->FIODIR|=(1<<LCD_ENABLE)|(1<<LCD_RS);
	wait_ms(40);
	LCDText_Send_4bits(COMMAND,INIT_VAL);
	wait_ms(5); //wait mote than 4.1ms
	LCDText_Send_4bits(COMMAND,INIT_VAL);
	wait_ChronoUs(100);
	LCDText_Send_4bits(COMMAND,INIT_VAL);
	LCDText_Send_4bits(COMMAND,(FUNCTION_SET_CMD | FOUR_BIT<<DL_POSITION)>>4); //8 bit command. Set datalength to 4bits write mode
	wait_ChronoUs(37); //waiting time
	LCDText_Write_4bits(COMMAND, FUNCTION_SET_CMD | FOUR_BIT<<DL_POSITION | TWO_LINES<<N_POSITION | TEN_DOT_FONT<<F_POSITION);
	LCDText_Write_4bits(COMMAND, DISPLAY_CONTROL_CMD | DISPLAY_OFF<<D_POSITION | CURSOR_OFF<<C_POSITION | BLINK_CURSOR_OFF<<B_POSITION);
	LCDText_Write_4bits(COMMAND, CLEAR_DISPLAY_CMD);
	LCDText_Write_4bits(COMMAND, ENTRY_MODE_SET_CMD | INCREMENT<<I_D_POSITION | SHIFT_ENABLE<<S_POSITION);
	LCDText_Write_4bits(COMMAND, RETURN_HOME_CMD);
	wait_ms(2); //home command requires at least 1.52ms of execution time
	LCDText_Write_4bits(COMMAND, DISPLAY_CONTROL_CMD | DISPLAY_ON<<D_POSITION | CURSOR_OFF<<C_POSITION | BLINK_CURSOR_OFF<<B_POSITION);
	row=0;
	col=0;
}

void LCDText_WriteChar(char ch){
	if(ch=='\n'){
		col=0;
		row=(row+1)%2;
	}
	else LCDText_Write_4bits(DATA,ch);
	col++;
	if(col>=16){
		col=0;
		if(row==0) row=1;
		else row=0;
		LCDText_Locate(row,col);
	}
}

void LCDText_WriteString(char *str){
	for (short i= 0; str[i]!= '\0'; ++i)
		LCDText_WriteChar(str[i]);
}

void LCDText_Locate(int r, int column){
	LCDText_Write_4bits(COMMAND, SET_DDRAM_ADDR_CMD | (r<<ROW_POSITION) | (column&MAX_COL_VALUE));
	row=r;
	col=column;
}

void LCDText_Cursor(int state){
	if(state>0)
		LCDText_Write_4bits(COMMAND, DISPLAY_CONTROL_CMD | DISPLAY_ON<<D_POSITION | CURSOR_ON<<C_POSITION | BLINK_CURSOR_OFF<<B_POSITION);
	else
		LCDText_Write_4bits(COMMAND, DISPLAY_CONTROL_CMD | DISPLAY_ON<<D_POSITION | CURSOR_OFF<<C_POSITION | BLINK_CURSOR_OFF<<B_POSITION);
}

void LCDText_Clear(void){
	LCDText_Write_4bits(COMMAND, CLEAR_DISPLAY_CMD);
	row=0;
	col=0;
	wait_ms(5);// The clear display command send the cursor home too
}

void LCDText_Printf(char *fmt, ...){
	va_list valist;
	va_start(valist,fmt);
	char str[MAX_CHAR];
	int ret=vsprintf(str, fmt, valist);
	if(ret<0 || ret>MAX_CHAR)
		LCDText_WriteString("Printf fmt fail");
	else LCDText_WriteString(str);
}

void LCDText_PrintBinary(int bin){
	LCDText_Clear();
	char str[MAX_CHAR];
	itoa(bin,str,2);
	LCDText_WriteString(str);
}




