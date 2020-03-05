/**
* @file		iap.h
* @brief	Contains the IAP function utility.
* @version	1.1
* @date		12 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/


#ifndef IAP_H_
#define IAP_H_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
/** @defgroup IAP IAP
 * This package provides the core capabilities for IAP function.
 * @{
 */
/** @defgroup IAP_Public_Constants IAP Public Constants
 * @{
*/
/**
 *  @brief	IAP address function
*/
#define IAP_LOCATION 0x1FFF1FF1
/**
 * @brief Memory address for save the sectors(32KB)
 */
#define SRAM_LOCATION 0x2007C000
/**
 * @defgroup IAP_Public_Memory_Constant IAP Public Memory Constants
 * @{
 */
/**
 * @brief 1KB
 */
#define ONE_K 1024
/**
 * @brief 4KB
 */
#define FOUR_K 4*ONE_K
/**
 * @brief 32KB
 */
#define THIRTY_TWO_K 32*ONE_K

/**
 * @}
 * @defgroup IAP_Public_ENUMS IAP Public Enums
 * @{
*/
/**
 * @brief possible returns from IAP function
 */
enum IAP_STATUS{
	CMD_SUCCESS,
	INVALID_COMMAND,
	SRC_ADDR_ERROR,
	DST_ADDR_ERROR,
	SRC_ADDR_NOT_MAPPED,
	DST_ADDR_NOT_MAPPED,
	COUNT_ERROR,
	INVALID_SECTOR,
	SECTOR_NOT_BLANK,
	SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
	COMPARE_ERROR,
	BUSY
};
/**
 * @brief possible commands for IAP function
 */
enum IAP_COMMAND_CODES{
	PREPARE_FOR_WRITE =50,
	COPY_RAM_FLASH,
	ERASE,
	BLANK_CHECK,
	READ_PART_ID,
	READ_BOOT_VERSION,
	COMPARE,
	REINVOKE_ISP,
	READ_SERIAL_NUMBER
};

/**
 * @}
 * @}
 * @defgroup IAP_Public_Functions IAP Public Functions
 * @{
*/
/**
 * @brief represent the IAP function address
 */
typedef void (*IAP)(unsigned int [],unsigned int[]);

/**
 * @brief erase the memory from the memory between address startSector and endSector
 * @return the value from the IAP function
 */
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector);
/**
 * @brief write data from dstAddr at srAddr with size Bytes
 * @return the value from the IAP function
 */
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size);
/**
 * @brief verifies if the data at dstAddr is the same as at srcAddr
 * @return the value from the IAP function
 */
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size);
/**
 * @brief verifies if the sector is empty
 * @return the value from the IAP function
 */
unsigned int FLASH_BlankSectors(unsigned int startSector, unsigned int endSector);
/**
 * @}
 * @}
 */

#endif /* IAP_H_ */
