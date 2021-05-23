/**
 * @file SPI_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 19-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

#define SPDR 				*((volatile u8*)0x2F)

#define SPSR 				*((volatile u8*)0x2E)
#define SPSR_SPIF			7
#define SPSR_WCOL			6
#define SPSR_SPI2X			0

#define SPCR 				*((volatile u8*)0x2C)
#define SPCR_SPIE			7
#define SPCR_SPE			6
#define SPCR_DORD			5
#define SPCR_MSTR			4
#define SPCR_CPOL			3
#define SPCR_CPHA			2
#define SPCR_SPR1			1
#define SPCR_SPR0			0

#define DISABLED			1
#define ENABLED				2

#define LSB_FIRST			1
#define MSB_FIRST			2

#define MASTER				1
#define SLAVE				2

#define RISING				1
#define FALLING				2

#define SAMPLE_FIRST		1
#define SETUP_FIRST			2

#endif
