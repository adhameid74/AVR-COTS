/**
 * @file USART_config.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 16-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/**
 * Options:
 * DISABLED, ENABLED
 */
#define RX_ENABLE								ENABLED
/**
 * Options:
 * DISABLED, ENABLED
 */
#define TX_ENABLE								ENABLED
/**
 * Options:
 * 5, 6, 7, 8
 */
#define DATA_SIZE								8
/**
 * Options:
 * ASYNCHRONOUS, SYNCHRONOUS
 */
#define USART_MODE								ASYNCHRONOUS
/**
 * NOTE: Select only in case of SYNCHRONOUS mode
 * Options:
 * TX_ON_RISING, RX_ON_FALLING
 */
#define CLOCK_POLARITY							TX_ON_RISING
/**
 * Options:
 * DISABLED, EVEN, ODD
 */

#define PARITY_MODE								DISABLED
/**
 * Options:
 * 1, 2
 */
#define STOP_BITS								1
/**
 * Options:
 * 2400, 4800, 9600
 */
#define BAUD_RATE                               9600

#define MAX_BUFFER_SIZE                         20

#define TX_TIMEOUT                              1000
#define RX_TIMEOUT                              1000

#endif
