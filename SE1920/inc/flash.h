/**
* @file		button.h
* @brief	Contains the buttons interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/
#ifndef FLASH_H_
#define FLASH_H_

#include "iap.h"
/** @defgroup FLASH Flash
 * This package provides the core capabilities for Flash functions.
 * @{
 */
/** @defgroup Flash_Public_Constants Flash Public Constants
 * @{
*/
/**
 * @brief sector that will be used
 */
#define SECTOR_MAX 29

#define SECTOR_THRESHOLD 16

/**
 * @brief initial address from sector 29
 */
#define SECTOR_INTERVAL_4K 0x00001000
#define SECTOR_INTERVAL_32K 0x00008000

enum INIT_STATS{
	SECTOR_FOUND,
	SECTOR_AVAILABLE,
	SECTOR_NOT_FOUND
};
/**
 * @}
 */
/** @defgroup Flash_Public_Functions Flash Public Functions
 * @{
*/
/**
 * @brief writes from ptr with size size at the memory flash sector 29
 * @parameters void* ptr sorce data address, unsigned int size number of bytes
 */
void writeToFlash(void* ptr, unsigned int size);
/**
 * @brief read from flash sector 29 and writes at ptr
 * @parameters void* ptr sorce data address
 */
void readFromFlash(void* ptr);
/**
 * @}
 * @}
 */
#endif /* FLASH_H_ */
