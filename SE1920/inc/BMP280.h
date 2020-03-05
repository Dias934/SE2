/**
* @file		BMP280.h
* @brief	Contains the sensor interaction.
* @version	1.1
* @date		4 Out 2017
* @author	Ricardo Romano, André Dias, Manuel Dias
* @numbers  43924, 40619, 38866
*/

#ifndef BMP280_H_
#define BMP280_H_

#ifdef __USE_CMSIS
#include "peripherals.h"
#include "LPC17xx.h"
#endif

/** @defgroup BMP280 BMP
 * This package provides the core capabilities for sensor functions.
 * @{
 * @defgroup BMP280_Public_MEMORY_ACCESS BMP280 Public Memory Access
 * @{
 * @defgroup BMP280_Public_MEMORY_CONSTANTS BMP280 Public Memory Constants
 * @{
 */
/**
 * @brief sensor ID address
 *
 */

#define ID_ADDR 0xD0
/**
 *  @brief	sensor ID value
*/
#define ID_VALUE 0x58
/**
 *  @brief	sensor ID reset address
*/
#define RESET_ADDR 0xE0
/**
 *  @brief	sensor ID reset value
*/
#define RESET_VAL 0xB6
/**
 *  @brief	sensor measurement control address
*/
#define CTRL_MEAS_ADDR 0xF4

#define SPI3W_EN_BIT 0 //precisa de comentario
#define PWR_MODE_BIT 0 //precisa de comentario

/**
 *  @brief	first bit of OSR_P
*/
#define OSR_P_BIT 2
/**
 *  @brief	first bit of OSR_T
*/
#define OSR_T_BIT 5
/**
 *  @brief	sensor configuration address
*/
#define CONFIG_ADDR 0xF5

/**
 *  @brief	first bit of filter
*/
#define FILTER_BIT 2
/**
 *  @brief	first bit of T_SB
*/
#define T_SB_BIT 5

 /**
 * @}
 * @}
 * @defgroup BMP280_Public_SENSOR_DATA BMP280 Public Sensor Data
 * @{
 * @defgroup BMP280_Public_STRUCT BMP280 Public Struct
 * @{
 */
/**
 * @brief	used for calibrate sensor data
*/

typedef struct{
	unsigned short dig_T1;
	short dig_T2;
	short dig_T3;
	unsigned short dig_P1;
	short dig_P2;
	short dig_P3;
	short dig_P4;
	short dig_P5;
	short dig_P6;
	short dig_P7;
	short dig_P8;
	short dig_P9;
}bmp280_calib_data_Typedef;

/**
 * @}
 * @defgroup BMP280_Public_DATA_CONSTANTS BMP280 Public Data Constants
 * @{
 */
/**
 * @brief	sensor pressure data address
*/
#define PRESSURE_DATA_ADDR 0xF7
/**
 *  @brief	sensor temperature data address
*/
#define TEMPERATURE_DATA_ADDR 0xFA
/** @defgroup BMP280_Public_CALIBRATION_DATA_ADDRESS BMP280 Public Calibration data address range
 * @{
*/
#define CALIB_DATA_ADDR_INIT 0X88
#define CALIB_DATA_ADDR_END 0X9F
/** @defgroup BMP280_Public_CALIBRATION_TEMPERATURE_ADDRESS BMP280 Public Calibration temperature address range
 * @{
*/
#define CALIB_TEMP_ADDR_INIT 0x88
#define CALIB_TEMP_ADDR_END 0x8D
/**
 * @}
 * @defgroup BMP280_Public_CALIBRATION_PRESSURE_ADDRESS BMP280 Public Calibration pressure address range
 * @{
 */

#define CALIB_PRESS_ADDR_INIT 0x8E
#define CALIB_PRESS_ADDR_END 0x9F
/**
 * @}
 * @}
 * @}
 * @}
 * @defgroup BMP280_Public_SPI_CONSTANTS BMP280 Public SPI Constants
 * @{
 */

/**
 *  @brief	CS pin is Pin 9 of Port0 (default pin)
*/
#define CS_PIN 9

/**
 *  @brief	SPI frequency
*/
#define SPI_FREQUENCY 10000000
/**
 *  @brief	Write constant that insert 0 at bit 7 of SPI multiple byte write
*/
#define WR 0x7F
/**
 *  @brief	Read constant that insert 1 at bit 7 of SPI multiple byte read
*/
#define RD 0xFF
/**
 * @}
 * @defgroup BMP280_Public_GLOBAL_VARIABLES BMP280 Public Global variables
 * @{
 */


extern double current_temp;
extern double current_press;
/**
 * @}
 * @defgroup BMP280_Public_ENUMS BMP280 Public Enums
 * @{
 */
/**
 * @brief	refers to the sensor modes
 */

enum PWR_MODE{
	SLEEP_MODE=0,
	FORCED_MODE,
	NORMAL_MODE=3
};
/**
 *  @brief	refers to the sensor pressure measurement
*/
enum OSR_VAL{
	SKIPPED =0,
	OVERSAMPLE_ONE,
	OVERSAMPLE_TWO,
	OVERSAMPLE_FOUR,
	OVERSAMPLE_EIGHT,
	OVERSAMPLE_SIXTEEN
};
/**
 *  @brief	refers to the SPI write enable value
*/
enum SPI3W_EN_VAL{
	I2C=0,
	SPI
};
/**
 *  @brief	refers to the sensor filter settings
*/
enum FILTER_COEF_VAL{
	FILTER_OFF=0,
	FILTER_2,
	FILTER_4=4,
	FILTER_8,
	FILTER_16
};
/**
 *  @brief	refers to the sensor time settings
*/
enum T_SB_VAL{
	TIME_HALF_MS=0,
	TIME_62_HALF_MS,
	TIME_125_MS,
	TIME_250_MS,
	TIME_500_MS,
	TIME_1_SEC,
	TIME_2_SEC,
	TIME_4_SEC
};

/**
 * @}
 */

/**
 * @defgroup BMP280_Public_FUNCTIONS BMP280 Public Functions
 * @{
 */
/**
 * @brief Call this function only at the beginning of the program and only once
 */
void init_bmp280();
/**
 *  @return this function returns the sensor ID
*/
int get_chip_ID();
/**
 *  @brief	transform raw data into readable data
 *  @returns SPI state (Success/fail)
*/
int measure();
/**
 * @}
 * @}
 */
#endif /* BMP280_H_ */
