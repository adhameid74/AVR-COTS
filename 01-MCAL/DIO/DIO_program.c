#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_register.h"
#include "DIO_config.h"
#include "DIO_private.h"


u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	u8 Local_u8ErrorState = NO_ERROR;
	if (Copy_u8Pin>DIO_u8_NUMBER_OF_PINS)
	{
		Local_u8ErrorState = ERROR;	
	}
	else
	{
		if (Copy_u8Value == DIO_u8_PIN_LOW)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8_PORTA: CLR_BIT(PORTA,Copy_u8Pin); break;
				case DIO_u8_PORTB: CLR_BIT(PORTB,Copy_u8Pin); break;
				case DIO_u8_PORTC: CLR_BIT(PORTC,Copy_u8Pin); break;
				case DIO_u8_PORTD: CLR_BIT(PORTD,Copy_u8Pin); break;
				default: Local_u8ErrorState = ERROR; break;
			}
		}
		else if (Copy_u8Value == DIO_u8_PIN_HIGH)
		{
			switch(Copy_u8Port)
			{
				case DIO_u8_PORTA: SET_BIT(PORTA,Copy_u8Pin); break;
				case DIO_u8_PORTB: SET_BIT(PORTB,Copy_u8Pin); break;
				case DIO_u8_PORTC: SET_BIT(PORTC,Copy_u8Pin); break;
				case DIO_u8_PORTD: SET_BIT(PORTD,Copy_u8Pin); break;
				default: Local_u8ErrorState = ERROR; break;
			}
		}
		else
		{
			Local_u8ErrorState = ERROR;
		}
	}
	return Local_u8ErrorState;
}

u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	u8 Local_u8ErrorState = NO_ERROR;
	switch(Copy_u8Port)
	{
		case DIO_u8_PORTA: PORTA = Copy_u8Value; break;
		case DIO_u8_PORTB: PORTB = Copy_u8Value; break;
		case DIO_u8_PORTC: PORTC = Copy_u8Value; break;
		case DIO_u8_PORTD: PORTD = Copy_u8Value; break;
		default: Local_u8ErrorState = ERROR; break;
	}
	return Local_u8ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8* Copy_u8Value)
{
	u8 Local_u8ErrorState = NO_ERROR;
	if (Copy_u8Value==NULL)
	{
		Local_u8ErrorState = NULL_POINTER_ERROR;
		return Local_u8ErrorState;
	}
	switch(Copy_u8Port)
	{
		case DIO_u8_PORTA: *Copy_u8Value = GET_BIT(PINA,Copy_u8Pin); break;
		case DIO_u8_PORTB: *Copy_u8Value = GET_BIT(PINB,Copy_u8Pin); break;
		case DIO_u8_PORTC: *Copy_u8Value = GET_BIT(PINC,Copy_u8Pin); break;
		case DIO_u8_PORTD: *Copy_u8Value = GET_BIT(PIND,Copy_u8Pin); break;
		default: Local_u8ErrorState = ERROR; break;
	}
	return Local_u8ErrorState;
}

u8 DIO_u8GetPortValue(u8 Copy_u8Port, u8* Copy_u8Value)
{
	u8 Local_u8ErrorState = NO_ERROR;
	if (Copy_u8Value==NULL)
	{
		Local_u8ErrorState = NULL_POINTER_ERROR;
		return Local_u8ErrorState;
	}
	switch(Copy_u8Port)
	{
		case DIO_u8_PORTA: *Copy_u8Value = PINA; break;
		case DIO_u8_PORTB: *Copy_u8Value = PINB; break;
		case DIO_u8_PORTC: *Copy_u8Value = PINC; break;
		case DIO_u8_PORTD: *Copy_u8Value = PIND; break;
		default: Local_u8ErrorState = ERROR; break;
	}
	return Local_u8ErrorState;
}
