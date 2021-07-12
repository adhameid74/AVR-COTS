/**
 * @file TWI_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 23-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void TWI_voidInit()
{
	TWBR = 2;
	TWSR = 0;
	TWAR = ((u8)ECU_SLAVE_ADDRESS << 1);
	#if GENERAL_CALL_RECOGNITION == DISABLED
		CLR_BIT(TWAR, SPCR_SPIE);
	#elif GENERAL_CALL_RECOGNITION == ENABLED
		SET_BIT(TWAR, TWAR_TWGCE);
	#else
		#error "Wrong Configuration Of GENERAL_CALL_RECOGNITION"
	#endif
	SET_BIT(TWCR, TWCR_TWEA);
	SET_BIT(TWCR, TWCR_TWEN);
}

void TWI_voidDisableAck()
{
	CLR_BIT(TWCR, TWCR_TWEA);
}

void TWI_voidEnableAck()
{
	SET_BIT(TWCR, TWCR_TWEA);
}

u8 TWI_u8SendByteSynch(u8 Copy_u8SlaveAddress, u8 Copy_u8Data)
{
	if( SendStartCondition() )
	{
		return ERROR;
	}
	if( SendSlaveAddress(Copy_u8SlaveAddress, WRITE) )
	{
		return ERROR;
	}
	TWDR = Copy_u8Data;
	SET_BIT(TWCR, TWCR_TWINT);
	while( GET_BIT(TWCR, TWCR_TWINT) == 0 );
	if( MSTR_WR_BYTE_ACK != (TWSR & 0xF8) )
	{
		return ERROR;
	}
	SendStopCondition();
	return NO_ERROR;
}

u8 TWI_u8SendByteAsynch(u8 Copy_u8SlaveAddress, u8 Copy_u8Data, void (*Copy_ptrCallBack)(void))
{
	AsynchStatus = START_CONDITION_STATE;
	TWI_CallBack = Copy_ptrCallBack;
	DataByte = Copy_u8Data;
	SlaveAddress = Copy_u8SlaveAddress<<1;
	SET_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	SET_BIT(TWCR, TWCR_TWIE);
	return NO_ERROR;
}

u8 TWI_u8ReceiveByteSynch(u8 Copy_u8SlaveAddress, u8* Copy_u8Data)
{
	if( SendStartCondition() )
	{
		return ERROR;
	}
	if( SendSlaveAddress(Copy_u8SlaveAddress, READ) )
	{
		return ERROR;
	}
	while( GET_BIT(TWCR, TWCR_TWINT) == 0 );
	if( MSTR_RD_BYTE_WITH_ACK != (TWSR & 0xF8) )
	{
		return ERROR;
	}
	*Copy_u8Data = TWDR;
	SendStopCondition();
	return NO_ERROR;
}

static u8 SendStartCondition()
{
	SET_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	while( GET_BIT(TWCR, TWCR_TWINT) == 0 );
	if( START_ACK != (TWSR & 0xF8) )
	{
		return ERROR;
	}
	return NO_ERROR;
}

static u8 SendRepeatedStart()
{
	SET_BIT(TWCR, TWCR_TWSTA);
	SET_BIT(TWCR, TWCR_TWINT);
	while( GET_BIT(TWCR, TWCR_TWINT) == 0 );
	if( REP_START_ACK != (TWSR & 0xF8) )
	{
		return ERROR;
	}
	return NO_ERROR;
}

static u8 SendSlaveAddress(u8 Copy_u8Address, u8 Copy_u8Direction)
{
	CLR_BIT(TWCR, TWCR_TWSTA);
	Copy_u8Address = Copy_u8Address<<1;
	Copy_u8Address |= Copy_u8Direction;
	TWDR = Copy_u8Address;
	SET_BIT(TWCR, TWCR_TWINT);
	while( GET_BIT(TWCR, TWCR_TWINT) == 0 );
	if(Copy_u8Direction == READ)
	{
		if( SLAVE_ADD_AND_RD_ACK != (TWSR & 0xF8) )
		{
			return ERROR;
		}
	}
	else
	{
		if( SLAVE_ADD_AND_WR_ACK != (TWSR & 0xF8) )
		{
			return ERROR;
		}
	}
	return NO_ERROR;
}

static void SendStopCondition()
{
	SET_BIT(TWCR, TWCR_TWSTO);
	SET_BIT(TWCR, TWCR_TWINT);
}

void __vector_19() __attribute__((signal));
void __vector_19()
{
	if(AsynchStatus == START_CONDITION_STATE)
	{
		if(START_ACK == (TWSR & 0xF8))
		{
			CLR_BIT(TWCR, TWCR_TWSTA);
			TWDR = SlaveAddress;
			AsynchStatus = SLAVE_ADDRESS_STATE;
			SET_BIT(TWCR, TWCR_TWINT);
		}
	}
	else if(AsynchStatus == SLAVE_ADDRESS_STATE)
	{
		if(SLAVE_ADD_AND_WR_ACK == (TWSR & 0xF8))
		{
			TWDR = DataByte;
			AsynchStatus = SENDING_BYTE_STATE;
			SET_BIT(TWCR, TWCR_TWINT);
		}
	}
	else if(AsynchStatus == SENDING_BYTE_STATE)
	{
		if(MSTR_WR_BYTE_ACK == (TWSR & 0xF8))
		{
			SET_BIT(TWCR, TWCR_TWSTO);
			AsynchStatus = STOP_CONDITION_STATE;
			SET_BIT(TWCR, TWCR_TWINT);
		}
	}
	else if(AsynchStatus == STOP_CONDITION_STATE)
	{
		SET_BIT(TWCR, TWCR_TWINT);
		CLR_BIT(TWCR, TWCR_TWIE);
		AsynchStatus = 0;
		TWI_CallBack();
	}
}
