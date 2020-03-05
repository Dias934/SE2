/**
* @file		I2C.h
* @brief	Contains the I2C function utility.
* @version	1.1
* @date		5 Mar 2020
* @author	Ricardo Romano, Manuel Dias
* @numbers  43924, 38866
*/

#ifndef I2C_H_
#define I2C_H_

#include "LPC17xx.h"

enum I2C_BUS{
	I2C_0 =0,
	I2C_1,
	I2C_2
};
/** @defgroup I2C I2C
 * This package provides the core capabilities for I2C functions.
 * @{
 */
/** @defgroup I2C_Public_Functions I2C Public Functions
 * @{
*/
void init_I2C(void);
/**
 * @brief set I2C transfers configurations
 */
int I2C_ConfigTransfer(int frequency, int bitData, int mode);

/**
 * @}
 * @}
 */
#endif /* I2C_H_ */
