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

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

static u16 USART_au16SendBuffer[MAX_BUFFER_SIZE];
static u16* USART_pu16ReceiveBuffer = NULL;
static u8 USART_u8SendIndex = 0;
static u8 USART_u8ReceiveIndex = 0;
static u8 USART_u8SendBufferSize = 0;
static u8 USART_u8ReceiveBufferSize = 0;
static void (*USART_SendCallBackFunc)(void) = NULL;
static void (*USART_ReceiveCallBackFunc)(void) = NULL;

void USART_voidInit()
{
    u8 UCSRC_VALUE = 0;
    SET_BIT(UCSRC_VALUE, UCSRC_URSEL);

    CLR_BIT(UCSRA, UCSRA_MPCM);
    CLR_BIT(UCSRA, UCSRA_U2X);

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

    #if MAX_BUFFER_SIZE <= 0
        #error "Wrong Configuration Of MAX_BUFFER_SIZE"
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
    return NO_ERROR;
}

u8 USART_u8SendBufferSynch(u16* Copy_au16Data, u8 Copy_u8Size)
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

u8 USART_u8ReceiveBufferSynch(u16* Copy_au16Data, u8 Copy_u8Size)
{
    u8 Local_u8ErrorState = NO_ERROR;
    if(Copy_au16Data == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    for (u8 Local_u8Counter = 0; Local_u8Counter < Copy_u8Size; Local_u8Counter++)
    {
        Local_u8ErrorState = USART_u8ReceiveDataSynch(&Copy_au16Data[Local_u8Counter]);
        if(Local_u8ErrorState != NO_ERROR)
        {
            return Local_u8ErrorState;
        }
    }
    return Local_u8ErrorState;
}

u8 USART_u8SendBufferAsynch(u16* Copy_au16Data, u8 Copy_u8Size, void (*CallBackFunc) (void))
{
    if(Copy_au16Data == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    if(CallBackFunc == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    if( (Copy_u8Size > MAX_BUFFER_SIZE) || (Copy_u8Size == 0) )
    {
        return ERROR;
    }
    USART_u8SendBufferSize = Copy_u8Size;
    for (u8 Local_u8Counter = 0; Local_u8Counter < Copy_u8Size; Local_u8Counter++)
    {
        USART_au16SendBuffer[Local_u8Counter] = Copy_au16Data[Local_u8Counter];
    }
    USART_SendCallBackFunc = CallBackFunc;
    USART_u8SendIndex = 0;
    SET_BIT(UCSRB, UCSRB_TXCIE);
    USART_u8SendDataSynch(USART_au16SendBuffer[USART_u8SendIndex]);
    return NO_ERROR;
}

u8 USART_u8ReceiveBufferAsynch(u16* Copy_au16Data, u8 Copy_u8Size, void (*CallBackFunc) (void))
{
    if(Copy_au16Data == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    if(CallBackFunc == NULL)
    {
        return NULL_POINTER_ERROR;
    }
    if( (Copy_u8Size > MAX_BUFFER_SIZE) || (Copy_u8Size == 0) )
    {
        return ERROR;
    }
    USART_u8ReceiveBufferSize = Copy_u8Size;
    USART_pu16ReceiveBuffer = Copy_au16Data;
    USART_ReceiveCallBackFunc = CallBackFunc;
    USART_u8ReceiveIndex = 0;
    SET_BIT(UCSRB, UCSRB_RXCIE);
    USART_u8ReceiveDataSynch(USART_pu16ReceiveBuffer);
    return NO_ERROR;
}

void __vector_13() __attribute__((signal));
void __vector_13()
{
    USART_u8ReceiveIndex++;
    if(USART_u8ReceiveIndex == (USART_u8ReceiveBufferSize))
    {
        CLR_BIT(UCSRB, UCSRB_RXCIE);
        USART_ReceiveCallBackFunc();
    }
    else
    {
        USART_u8ReceiveDataSynch(&USART_pu16ReceiveBuffer[USART_u8ReceiveIndex]);
    }
}

void __vector_14() __attribute__((signal));
void __vector_14()
{

}

void __vector_15() __attribute__((signal));
void __vector_15()
{
    USART_u8SendIndex++;
    if(USART_u8SendIndex == (USART_u8SendBufferSize))
    {
        CLR_BIT(UCSRB, UCSRB_TXCIE);
        USART_SendCallBackFunc();
    }
    else
    {
        USART_u8SendDataSynch(USART_au16SendBuffer[USART_u8SendIndex]);
    }
}
