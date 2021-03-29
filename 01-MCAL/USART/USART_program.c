/**
 * @file USART_program.c
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 16-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "STD_TYPES"
#include "BIT_MATH"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

void USART_voidInit()
{
    u8 UCSRC_VALUE = 0;
    SET_BIT(UCSRC_VALUE, UCSRC_URSEL);

    CLR_BIT(UCSRA, UCSRA_MPCM);
    CLR_BIT(UCSRA, UCSRA_U2X);

    #if RX_INTERRUPT == ENABLED
        SET_BIT(UCSRB, UCSRB_RXCIE);
    #elif RX_INTERRUPT == DISABLED
        CLR_BIT(UCSRB, UCSRB_RXCIE);
    #else
        #error "Wrong Configuration Of RX_INTERRUPT"
    #endif

    #if TX_INTERRUPT == ENABLED
        SET_BIT(UCSRB, UCSRB_TXCIE);
    #elif TX_INTERRUPT == DISABLED
        CLR_BIT(UCSRB, UCSRB_TXCIE);
    #else
        #error "Wrong Configuration Of TX_INTERRUPT"
    #endif

    #if DATA_REGISTER_EMPTY_INTERRUPT == ENABLED
        SET_BIT(UCSRB, UCSRB_UDRIE);
    #elif DATA_REGISTER_EMPTY_INTERRUPT == DISABLED
        CLR_BIT(UCSRB, UCSRB_UDRIE);
    #else
        #error "Wrong Configuration Of DATA_REGISTER_EMPTY_INTERRUPT"
    #endif

    #if DATA_SIZE == 5
        CLR_BIT(UCSRC_VALUE, UCSRC_UCSZ0);
        CLR_BIT(UCSRC_VALUE, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
    #elif DATA_SIZE == 6
        SET_BIT(UCSRC_VALUE, UCSRC_UCSZ0);
        CLR_BIT(UCSRC_VALUE, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
    #elif DATA_SIZE == 7
        CLR_BIT(UCSRC_VALUE, UCSRC_UCSZ0);
        SET_BIT(UCSRC_VALUE, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
    #elif DATA_SIZE == 8
        SET_BIT(UCSRC_VALUE, UCSRC_UCSZ0);
        SET_BIT(UCSRC_VALUE, UCSRC_UCSZ1);
        CLR_BIT(UCSRB, UCSRB_UCSZ2);
    #else
        #error "Wrong Configuration Of DATA_SIZE"
    #endif

    #if USART_MODE == ASYNCHRONOUS
        CLR_BIT(UCSRC_VALUE, UCSRC_UMSEL);
    #elif USART_MODE == SYNCHRONOUS
        SET_BIT(UCSRC_VALUE, UCSRC_UMSEL);
        #if CLOCK_POLARITY == TX_ON_RISING
            CLR_BIT(UCSRC_VALUE, UCSRC_UCPOL);
        #elif CLOCK_POLARITY == TX_ON_FALLING
            SET_BIT(UCSRC_VALUE, UCSRC_UCPOL);
        #else
            #error "Wrong Configuration Of UCSRC_UCPOL"
        #endif
    #else
        #error "Wrong Configuration Of USART_MODE"
    #endif

    #if PARITY_MODE == DISABLED
        CLR_BIT(UCSRC_VALUE, UCSRC_UPM0);
        CLR_BIT(UCSRC_VALUE, UCSRC_UPM1);
    #elif PARITY_MODE == EVEN
        CLR_BIT(UCSRC_VALUE, UCSRC_UPM0);
        SET_BIT(UCSRC_VALUE, UCSRC_UPM1);
    #elif PARITY_MODE == ODD
        SET_BIT(UCSRC_VALUE, UCSRC_UPM0);
        SET_BIT(UCSRC_VALUE, UCSRC_UPM1);
    #else
        #error "Wrong Configuration Of PARITY_MODE"
    #endif

    #if STOP_BITS == 1
        CLR_BIT(UCSRC_VALUE, UCSRC_USBS);
    #elif STOP_BITS == 2
        SET_BIT(UCSRC_VALUE, UCSRC_USBS);
    #else
        #error "Wrong Configuration Of STOP_BITS"
    #endif

    #if BAUD_RATE == 2400
        UBRRL = 207;
    #elif BAUD_RATE == 4800
        UBRRL = 103;
    #elif BAUD_RATE == 9600
        UBRRL = 51;
    #else
        #error "Wrong Configuration Of BAUD_RATE"
    #endif

    UCSRC = UCSRC_VALUE;

    #if RX_ENABLE == ENABLED
        SET_BIT(UCSRB, UCSRB_RXEN);
    #elif RX_ENABLE == DISABLED
        CLR_BIT(UCSRB, UCSRB_RXEN);
    #else
        #error "Wrong Configuration Of RX_ENABLE"
    #endif

    #if TX_ENABLE == ENABLED
        SET_BIT(UCSRB, UCSRB_TXEN);
    #elif TX_ENABLE == DISABLED
        CLR_BIT(UCSRB, UCSRB_TXEN);
    #else
        #error "Wrong Configuration Of TX_ENABLE"
    #endif
}

u8 USART_u8SendDataSynch(u16 Copy_u16Data)
{
    u16 Local_u16Timer = 0;
    while( ((GET_BIT(UCSRA, UCSRA_UDRE)) == 0) && (Local_u16Timer != TX_TIMEOUT) )
    {
        Local_u16Timer++;
    }
    if(Local_u16Timer == TX_TIMEOUT)
    {
        return TIMEOUT_ERROR;
    }
    #if DATA_SIZE == 9
        if( (GET_BIT(Copy_u16Data, 8)) == 1 )
        {
            SET_BIT(UCSRB, UCSRB_TXB8);
            CLR_BIT(Copy_u16Data, 8);
        }
    #endif
    UDR == Copy_u16Data;
    return NO_ERROR;
}

u8 USART_u8ReceiveDataSynch(u16* Copy_pu16Data)
{
    u16 Local_u16Timer = 0;
    if(Copy_pu16Data == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    *Copy_pu16Data = 0;
    while( ((GET_BIT(UCSRA, UCSRA_RXC)) == 0) && (Local_u16Timer != RX_TIMEOUT) )
    {
        Local_u16Timer++;
    }
    if(Local_u16Timer == RX_TIMEOUT)
    {
        return TIMEOUT_ERROR;
    }
    #if DATA_SIZE == 9
        if( (GET_BIT(UCSRB, UCSRB_RXB8)) == 1 )
        {
            SET_BIT((*Copy_pu16Data), 8);
        }
    #endif
    *Copy_pu16Data |= UDR;
}

u8 USART_u8SendArraySynch(u16* Copy_au16Data, u8 Copy_u8Size)
{
    u8 Local_u8ErrorState = NO_ERROR;
    if(Copy_au16Data == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    for (u8 Local_u8Counter = 0; Local_u8Counter < Copy_u8Size; Local_u8Counter++)
    {
        Local_u8ErrorState = USART_u8SendDataSynch(Copy_au16Data[Local_u8Counter]);
        if(Local_u8ErrorState != NO_ERROR)
        {
            return Local_u8ErrorState;
        }
    }
    return Local_u8ErrorState;
}

u8 USART_u8ReceiveArraySynch(u16* Copy_au16Data, u8 Copy_u8Size)
{
    u8 Local_u8ErrorState = NO_ERROR;
    if(Copy_au16Data == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    for (u8 Local_u8Counter = 0; Local_u8Counter < Copy_u8Size; Local_u8Counter++)
    {
        Local_u8ErrorState = USART_u8ReceiveDataSynch(Copy_au16Data[Local_u8Counter]);
        if(Local_u8ErrorState != NO_ERROR)
        {
            return Local_u8ErrorState;
        }
    }
    return Local_u8ErrorState;

}
