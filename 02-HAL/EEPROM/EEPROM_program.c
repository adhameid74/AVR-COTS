/**
 * @file EEPROM_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 01-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

u8 EEPROM_u8WriteByte(u16 Copy_u16Location, u8 Copy_u8Data)
{
    u8 Local_u8EEPROMAddress = ((Copy_u16Location>>8)&3) | (A2_PIN<<2) | (EEPROM_FIXED_ADDRESS);
	if( TWI_u8SendStartCondition() )
	{
		return ERROR;
	}
    if( TWI_u8SendSlaveAddress(Local_u8EEPROMAddress, TWI_WRITE) )
	{
		return ERROR;
	}
    if( TWI_u8SendByte((u8)Copy_u16Location) )
	{
		return ERROR;
	}
    if( TWI_u8SendByte(Copy_u8Data) )
	{
		return ERROR;
	}
	TWI_voidSendStopCondition();
    // Delay 10 ms
	return NO_ERROR;
}

u8 EEPROM_u8ReadByte(u16 Copy_u16Location, u8* Copy_pu8Data)
{
    u8 Local_u8EEPROMAddress = ((Copy_u16Location>>8)&3) | (A2_PIN<<2) | (EEPROM_FIXED_ADDRESS);
	if( TWI_u8SendStartCondition() )
	{
		return ERROR;
	}
    if( TWI_u8SendSlaveAddress(Local_u8EEPROMAddress, TWI_WRITE) )
	{
		return ERROR;
	}
    if( TWI_u8SendByte((u8)Copy_u16Location) )
	{
		return ERROR;
	}
	if( TWI_u8SendRepeatedStart() )
	{
		return ERROR;
	}
    if( TWI_u8SendSlaveAddress(Local_u8EEPROMAddress, TWI_READ) )
	{
		return ERROR;
	}
    if( TWI_u8ReceiveByte(Copy_pu8Data) )
	{
		return ERROR;
	}
    TWI_voidSendStopCondition();
    // Delay 10ms
    return NO_ERROR;
}
