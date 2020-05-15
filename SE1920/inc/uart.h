/**
* @file		UART.h
* @brief	Contains the sensor interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/


#ifndef UART_H_
#define UART_H_
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

/** @defgroup UART UART0
 * This package provides the core capabilities for UART protocol.
 * @{
 * @defgroup UART_Public_CONFIG_CONSTANTS UART0 Public Configuration Constants
 * @{
 */

#define PCLK_UART0_BIT_POS 6
#define PCLK_CCLK_H 1
#define PCLK_CCLK_L 2

#define BUFFER_SIZE 1<<10
/**
 * @brief UART0 PCLK configuration High value
 */
#define UART0_PCLK_CONFIG_H PCLK_CCLK_H<<PCLK_UART0_BIT_POS
/**
 * @brief UART0 PCLK configuration Low value
 */
#define UART0_PCLK_CONFIG_L PCLK_CCLK_L<<PCLK_UART0_BIT_POS

#define UART0_FUNC_H 1
#define UART0_FUNC_L 2
#define PINSEL_UART0_BIT_POS 4
/**
 * @brief UART0 PINSEL configuration High value
 */
#define UART0_PINSEL_CONFIG_H (UART0_FUNC_H|(UART0_FUNC_H<<2))<<PINSEL_UART0_BIT_POS
/**
 * @brief UART0 PINSEL configuration Low value
 */
#define UART0_PINSEL_CONFIG_L (UART0_FUNC_L|(UART0_FUNC_L<<2))<<PINSEL_UART0_BIT_POS

#define UART0_PULL_UP_L 3
#define PINMODE_UART0_BIT_POS 4
/**
 * @brief UART0 PINMODE configuration value
 */
#define UART0_PINMODE_CONFIG_L (UART0_PULL_UP_L|(UART0_PULL_UP_L<<2))<<PINMODE_UART0_BIT_POS

#define UART0_OD_NORMAL_L 1
#define PINMODE_OD_BIT_POS 2
/**
 * @brief UART0 Open drain mode configuration value
 */
#define UART0_PINMODE_OD_CONFIG_L (UART0_OD_NORMAL_L |(UART0_OD_NORMAL_L<<1))<<PINMODE_OD_BIT_POS
/**
 * @brief FCR functionalities bit positions
 */
enum FCR_BIT_POS{
	FIFO_EN=0,
	RX_FIFO_EN,
	TX_FIFO_EN,
	DMA_MODE_SELECT,
	RX_TRIGGER_LEVEL=6
};

enum RX_TRIGGER_VALUES{
	LVL0=0,
	LVL1,
	LVL2,
	LVL3
};

/**
 * @brief LCR functionalities bit positions
 */
enum LCR_BIT_POS{
	WLR=0,
	STOP_BIT_SELECT=2,
	PARITY_EN,
	PARITY_SELECT,
	BREAK_CTRL=6,
	DLAB
};
/**
 * @brief LSR functionalities bit positions
 */
enum LSR_BIT_POS{
	RDR=0,
	OE,
	PE,
	FE,
	BI,
	THRE,
	TEMT,
	RXFE
};
/**
 * @brief ACR functionalities bit positions
 */
enum ACR_BIT_POS{
	START=0,
	MODE,
	AUTORESTART,
	ABEOINTCLR=8,
	ABTOINTCLR
};
/**
 * @brief FDR functionalities bit positions
 */
enum FDR_BIT_POS{
	DIVADDVAL=0,
	MULVAL=4
};

enum IER_BIT_POS{
	RBR_INT_EN=0,
	THRE_INT_EN,
	RX_LS_INT_EN,
	ABEO_INT_EN=8,
	ABTO_INT_EN
};
/**
 * @brief TXEN bit position
 */
#define TXEN_BIT_POS 7
/**
 * @}
 */
/**
 * @brief Word lengths available
 */
enum WORD_LENGTH_SELECT{
	FIVE_CH=0,
	SIX_CH,
	SEVEN_CH,
	EIGHT_CH,
};

enum INT_ID_VALUES{
	THRE_INT=1,
	RDA,
	RLS,
	CTI=6
};


/**
 * @brief UART0 FCR->FIFO configuration value
 */
#define UART_FCR_FIFO_EN (1<<FIFO_EN)
/**
 * @brief UART0 FCR->RX configuration value
 */
#define UART_FCR_RX_RS (1<<RX_FIFO_EN)
/**
 * @brief UART0 FCR->TX configuration value
 */
#define UART_FCR_TX_RS (1<<TX_FIFO_EN)

/**
 * @brief UART0 LSR->RDR configuration value
 */
#define UART_LSR_RDR (1<<RDR)
/**
 * @brief UART0 LSR->THRE configuration value
 */
#define UART_LSR_THRE (1<<THRE)
/**
 * @brief UART0 TER->TXEN configuration value
 */
#define UART_TER_TXEN (1<<TXEN_BIT_POS)

#define UART_TER_MASK 0x40

#define NO_CONTENT 0x45
/**
 * @brief UART0 LCR->DLAB enable configuration value
 */
#define UART_LCR_DLAB_EN (1<<DLAB)
/**
 * @brief UART0 LCR->BREAK enable configuration value
 */
#define UART_LCR_BREAK_EN (1<<BREAK_CTRL)
/**
 * @brief UART0 LCR->BITMASK configuration value
 */
#define UART_LCR_BITMASK 0xF
/**
 * @brief UART0 LCR->Word Length (8-bit) configuration value
 */
#define UART_LCR_WLEN8 (EIGHT_CH<<WLR)

#define UART_FCR_TRG_LEV0 (LVL0<<RX_TRIGGER_LEVEL)

#define UART_IER_BITMASK 0x307

#define UART_IER_RBRINT_EN (1<< RBR_INT_EN)

#define UART_IER_RLSINT_EN (1<<RX_LS_INT_EN)

#define UART_IER_THRE_EN (1<<THRE_INT_EN)


#define UART_IIR_MASK 0x03CF

#define UART_IIR_INTID_POS 1

#define UART_IIR_INTID_MASK (0x7<<UART_IIR_INTID_POS)

#define UART_IIR_INTID_RDA_MASK (RDA<<UART_IIR_INTID_POS)

#define UART_IIR_INTID_CTI_MASK (CTI<<UART_IIR_INTID_POS)

#define UART_IIR_INTSTAT_NOT_PEND 1




/**
 * @brief Fractional Divider table size
 */
#define TABLE_SIZE 18*4

/**
 * @}
 * @defgroup UART_Public_FUNCTIONS UART0 Public Functions
 * @{
*/
/**
 * @brief Initialize the UART0 protocol functions
 * @param unsigned int baud rate
 * @return bool value that represents the success of the initialization
 */
bool UART_Initialize(unsigned int baud, bool interrupt);
/**
 * @brief Check if its a char value
 * @return bool value that is tru if its a char
 */
bool UART_IsChar(void);
/**
 * @brief Read from UART
 * @return unsigned char value containing the readed values
 */
unsigned char UART_ReadChar(void);
/**
 * @brief Gets a char from UART
 * @param unsigned char pointer that will contain the readed value
 * @return bool value representing the success of the function
 */
bool UART_GetChar(char *ch);
/**
 * @brief Writes a char value into UART
 * @param unsigned char contain the value to write
 */
void UART_WriteChar(char ch);
/**
 * @brief Writes a string into UART
 * @param char pointer containing the string value to write
 */
void UART_WriteString(char *str);

/**
 * @brief Writes a text into UART
 * @param char pointer containing the text to be written to UART
 * @return bool value representing the success of the function
 */
bool UART_Printf(char *format, ...);

/**
 * @brief Writes len characters of buffer to UART buffer
 * @param unsigned char pointer containing the buffer
 * @param int with buffer size
 * @return uint32_t value representing the number of bytes written to the UART buffer
 */
uint32_t UART_WriteBuffer(char *buffer, int len);

/**
 * @brief Reads UART buffer len characters and writes to the buffer
 * @param unsigned char pointer containing the buffer
 * @param uint32_t with buffer size
 * @return uint32_t value representing the number of bytes written to the buffer
 */
uint32_t UART_ReadBuffer(char *buffer, uint32_t len);

void UART_Flush();
/**
 * @}
 * @}
 */
#endif /* UART_H_ */
