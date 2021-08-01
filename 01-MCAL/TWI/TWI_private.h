/**
 * @file TWI_private.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 23-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define TWCR 				*((volatile u8*)0x56)
#define TWCR_TWINT			7
#define TWCR_TWEA			6
#define TWCR_TWSTA			5
#define TWCR_TWSTO			4
#define TWCR_TWWC			3
#define TWCR_TWEN			2
#define TWCR_TWIE			0

#define TWDR 				*((volatile u8*)0x23)

#define TWAR 				*((volatile u8*)0x22)
#define TWAR_TWGCE			0

#define TWSR 				*((volatile u8*)0x21)
#define TWSR_TWS7			7
#define TWSR_TWS6			6
#define TWSR_TWS5			5
#define TWSR_TWS4			4
#define TWSR_TWS3			3
#define TWSR_TWPS1			1
#define TWSR_TWPS0			0

#define TWBR 				*((volatile u8*)0x20)

#define DISABLED			1
#define ENABLED				2

#define START_ACK                0x08
#define REP_START_ACK            0x10
#define SLAVE_ADD_AND_WR_ACK     0x18
#define SLAVE_ADD_AND_RD_ACK     0x40
#define MSTR_WR_BYTE_ACK         0x28
#define MSTR_RD_BYTE_WITH_ACK    0x50
#define MSTR_RD_BYTE_WITH_NACK   0x58
#define SLAVE_ADD_RCVD_RD_REQ    0xA8
#define SLAVE_ADD_RCVD_WR_REQ    0x60
#define SLAVE_DATA_RECEIVED      0x80
#define SLAVE_BYTE_TRANSMITTED   0xB8

#define START_CONDITION_STATE		1
#define SLAVE_ADDRESS_STATE			2
#define SENDING_BYTE_STATE			3
#define STOP_CONDITION_STATE		4

static u8 AsynchStatus = 0;
static void (*TWI_CallBack)(void) = NULL;
static u8 DataByte;
static u8 SlaveAddress;

#endif
