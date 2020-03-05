/*
 * spi.h
 *
 *  Created on: 07/11/2019
 *      Author: A38866
 */

#ifndef SPI_H_
#define SPI_H_

#include "LPC17xx.h"

#define SPI_FUNCTION 3

#define PINSEL_SCK_BIT_POS 30
#define PINSEL_MISO_BIT_POS 2
#define PINSEL_MOSI_BIT_POS 4

#define PCLK_SPI_BIT_POSITION 16 //PCLKSEL0
#define PCLK_CCLK_FUNCTION_L 2 //set PCLK to CCLK with negative logic

#define BIT_ENABLE_BIT_POSITION 2
#define BITS_MODE 1

#define BITS_BIT_POSITION 8
#define BITS_MASK 0xF

#define MASTER_MODE_BIT_POSITION 5
#define MASTER_MODE 1

#define LSBF_BIT_POSITION 6
#define MSB_MODE_L 1 //MSB mode of LSBF with negative logic

#define CPHA_CPOL_BIT_POSITION 3
#define CPHA_CPOL_BIT_MASK 0x3

enum CPHA_CPOL_VALUES{
	CPHA_CPOL_LL=0,
	CPHA_CPOL_HL,
	CPHA_CPOL_LH,
	CPHA_CPOL_HH
};


#define CUSTOM_CONFIG_TRANSFER 0
#define DEFAULT_FREQUENCY 1
#define DEFAULT_DATABIT DEFAULT_FREQUENCY<<1
#define DEFAULT_MODE DEFAULT_FREQUENCY<<2

enum BITS{
	EIGHT_BITS=8,
	NINE_BITS,
	TEN_BITS,
	ELEVEN_BITS,
	TWELVE_BITS,
	THIRTEEN_BITS,
	FOURTEEN_BITS,
	FIFTEEN_BITS,
	SIXTEEN_BITS=0
};

#define ABRT 1
#define MODF 2
#define ROVR 4
#define WCOL 8
#define SPIF 16



void init_spi(void);
/* Faz a iniciação do controlador e configura os respetivos pinos. */

int SPI_ConfigTransfer(int frequency, int bitData, int mode);
/* Configura o ritmo de envio/receção, o numero de bits de dados e o modo (CPOL, CPHA). */

int SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int length);
/* Realiza uma transferência. Retorna sucesso ou erro na transferência. */

#endif /* SPI_H_ */
