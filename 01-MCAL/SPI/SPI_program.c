/**
 * @file SPI_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 19-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void SPI_voidInit()
{
	#if INTERRUPT_ENABLE == DISABLED
		CLR_BIT(SPCR, SPCR_SPIE);
	#elif INTERRUPT_ENABLE == ENABLED
		SET_BIT(SPCR, SPCR_SPIE);
	#else
		#error "Wrong Configuration Of INTERRUPT_ENABLE"
	#endif

	#if DATA_ORDER == LSB_FIRST
		SET_BIT(SPCR, SPCR_DORD);
	#elif DATA_ORDER == MSB_FIRST
		CLR_BIT(SPCR, SPCR_DORD);
	#else
		#error "Wrong Configuration Of DATA_ORDER"
	#endif

	#if SPI_MODE == MASTER
		SET_BIT(SPCR, SPCR_MSTR);
	#elif SPI_MODE == SLAVE
		CLR_BIT(SPCR, SPCR_MSTR);
	#else
		#error "Wrong Configuration Of SPI_MODE"
	#endif

	#if LEADING_EDGE == RISING
		CLR_BIT(SPCR, SPCR_CPOL);
	#elif LEADING_EDGE == FALLING
		SET_BIT(SPCR, SPCR_CPOL);
	#else
		#error "Wrong Configuration Of LEADING_EDGE"
	#endif

	#if CLOCK_PHASE == SAMPLE_FIRST
		CLR_BIT(SPCR, SPCR_CPHA);
	#elif CLOCK_PHASE == SETUP_FIRST
		SET_BIT(SPCR, SPCR_CPHA);
	#else
		#error "Wrong Configuration Of CLOCK_PHASE"
	#endif

	#if CLOCK_DIVISION_FACTOR == 4
		CLR_BIT(SPCR, SPCR_SPR0);
		CLR_BIT(SPCR, SPCR_SPR1);
	#elif CLOCK_DIVISION_FACTOR == 16
		SET_BIT(SPCR, SPCR_SPR0);
		CLR_BIT(SPCR, SPCR_SPR1);
	#elif CLOCK_DIVISION_FACTOR == 64
		CLR_BIT(SPCR, SPCR_SPR0);
		SET_BIT(SPCR, SPCR_SPR1);
	#elif CLOCK_DIVISION_FACTOR == 128
		SET_BIT(SPCR, SPCR_SPR0);
		SET_BIT(SPCR, SPCR_SPR1);
	#else
		#error "Wrong Configuration Of CLOCK_DIVISION_FACTOR"
	#endif

	#if DOUBLE_SPEED == DISABLED
		CLR_BIT(SPSR, SPSR_SPI2X);
	#elif DOUBLE_SPEED == ENABLED
		SET_BIT(SPSR, SPSR_SPI2X);
	#else
		#error "Wrong Configuration Of DOUBLE_SPEED"
	#endif

	SET_BIT(SPCR, SPCR_SPE);

}

u8 SPI_u8TransceiveSynch(u8 Copy_u8TransmittedData, u8* Copy_pu8ReceivedData)
{
    u16 Local_u16Timer = 0;
    if(Copy_pu8ReceivedData == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    SPDR = Copy_u8TransmittedData;
    while( ((GET_BIT(SPSR, SPSR_SPIF)) == 0) && (Local_u16Timer != TIMEOUT) )
    {
    	Local_u16Timer++;
    }
    if(Local_u16Timer == TIMEOUT)
    {
        return TIMEOUT_ERROR;
    }
    *Copy_pu8ReceivedData = SPDR;
    return NO_ERROR;
}
