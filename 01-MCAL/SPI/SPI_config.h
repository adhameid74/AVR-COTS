/**
 * @file SPI_config.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 19-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/**
 * Options:
 * DISABLED, ENABLED
 */
#define INTERRUPT_ENABLE			DISABLED

/**
 * Options:
 * LSB_FIRST, MSB_FIRST
 */
#define DATA_ORDER					LSB_FIRST

/**
 * Options:
 * MASTER, SLAVE
 */
#define SPI_MODE					MASTER

/**
 * Options:
 * RISING, FALLING
 */
#define LEADING_EDGE				RISING

/**
 * Options:
 * SAMPLE_FIRST, SETUP_FIRST
 */
#define CLOCK_PHASE					SETUP_FIRST

/**
 * Options:
 * 4, 16, 64, 128
 */
#define CLOCK_DIVISION_FACTOR		16

/**
 * Options:
 * DISABLED, ENABLED
 */
#define DOUBLE_SPEED				DISABLED

#define TIMEOUT						10000

#endif
