/***********************************************************
************************************************************
				Author: 		Adham Eid
				Component:		ADC
				File:			PROGRAM
				Layer:			MCAL
				Version:		1.00
************************************************************
***********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERROR.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

static void (*ADC_ptrfuncISR)(void) = NULL;

void ADC_voidInit()
{
	// ADC Reference Voltage Selection
#if ADC_REF_SELECTION == ADC_u8_AREF

	CLEAR_BIT(ADMUX, ADMUX_REFS1);
	CLEAR_BIT(ADMUX, ADMUX_REFS0);

#elif ADC_REF_SELECTION == ADC_u8_AVCC

	CLEAR_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);

#elif ADC_REF_SELECTION == ADC_u8_INTERNAL_2_56_VOLT

	SET_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);

#else

#error Wrong Configuration Of ADC_REF_SELECTION

#endif

	// ADC Left Adjust Result Selection
#if ADC_RESULT == ADC_u8_RESULT_8_BITS

	SET_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_RESULT == ADC_u8_RESULT_10_BITS

	CLEAR_BIT(ADMUX, ADMUX_ADLAR);

#else

#error Wrong Configuration Of ADC_RESULT

#endif

	// ADC Prescaler Selection
	ADCSRA &= PRESCALER_SELECTION_BIT_MASK;
	ADCSRA |= ADC_PRESCALER_SELECTION;

	// ADC Enable/Disable Selection
#if ADC_EN == ENABLE

	SET_BIT(ADCSRA, ADCSRA_ADEN);

#elif ADC_EN == DISABLE

	CLEAR_BIT(ADCSRA, ADCSRA_ADEN);

#else

#error Wrong Configuration of ADC_EN

#endif
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_u16ptrResult, u32 Copy_u32TimeOut)
{
	u32 Local_u32Counter = 0;
	// Check the pointer validity
	if(NULL == Copy_u16ptrResult)
	{
		return NULL_POINTER_ERROR;
	}
	// ADC channel selection
	if(ADC_u8_CHANNEL_5_2_1x<Copy_u8Channel)
	{
		return ERROR;
	}
	ADMUX &= CHANNEL_SELECTION_BIT_MASK;
	ADMUX |= Copy_u8Channel;
	// ADC conversion starting
	SET_BIT(ADCSRA, ADCSRA_ADSC);
	// Waiting until conversion is done or until timeout
	while((GET_BIT(ADCSRA, ADCSRA_ADIF) == 0) && Copy_u32TimeOut>Local_u32Counter)
	{
		Local_u32Counter++;
	}
	// Check if the conversion is done or exceeded the time limit
	if(Copy_u32TimeOut<=Local_u32Counter)
	{
		return TIMEOUT_ERROR;
	}
	// Clearing the ADC interrupt flag
	SET_BIT(ADCSRA, ADCSRA_ADIF);

	// Returning the result
#if ADC_RESULT == ADC_u8_RESULT_8_BITS

	*Copy_u16ptrResult = ADCH;

#elif ADC_RESULT == ADC_u8_RESULT_10_BITS

	*Copy_u16ptrResult = ADC;

#endif
	return NO_ERROR;
}

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel, void (*ISR)(void))
{
	// Check the pointer validity
	if(NULL == ISR)
	{
		return NULL_POINTER_ERROR;
	}
	ADC_ptrfuncISR = ISR;
	// ADC channel selection
	if(ADC_u8_CHANNEL_5_2_1x<Copy_u8Channel)
	{
		return ERROR;
	}
	ADMUX &= CHANNEL_SELECTION_BIT_MASK;
	ADMUX |= Copy_u8Channel;
	// ADC conversion starting
	SET_BIT(ADCSRA, ADCSRA_ADSC);
	// ADC interrupt enable
	SET_BIT(ADCSRA, ADCSRA_ADIE);
	return NO_ERROR;
}

u8 ADC_u8SetReference(u8 Copy_u8Reference)
{
	if(ADC_u8_AREF == Copy_u8Reference)
	{
		CLEAR_BIT(ADMUX, ADMUX_REFS1);
		CLEAR_BIT(ADMUX, ADMUX_REFS0);
		return NO_ERROR;
	}
	else if(ADC_u8_AVCC == Copy_u8Reference)
	{
		CLEAR_BIT(ADMUX, ADMUX_REFS1);
		SET_BIT(ADMUX, ADMUX_REFS0);
		return NO_ERROR;
	}
	else if(ADC_u8_INTERNAL_2_56_VOLT == ADC_REF_SELECTION)
	{
			SET_BIT(ADMUX, ADMUX_REFS1);
			SET_BIT(ADMUX, ADMUX_REFS0);
			return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 ADC_u8SetResultNumOfBits(u8 Copy_u8NumOfBits)
{
	if(ADC_u8_RESULT_8_BITS == Copy_u8NumOfBits)
	{
		SET_BIT(ADMUX, ADMUX_ADLAR);
		return NO_ERROR;
	}
	else if(ADC_u8_RESULT_10_BITS == Copy_u8NumOfBits)
	{
		CLEAR_BIT(ADMUX, ADMUX_ADLAR);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

void ADC_voidEnable()
{
	SET_BIT(ADCSRA, ADCSRA_ADEN);
}

void ADC_voidDisable()
{
	CLEAR_BIT(ADCSRA, ADCSRA_ADEN);
}

u8 ADC_u8SetPrescalerFactor(u8 Copy_u8Factor)
{
	if(DIVIDE_BY_128<Copy_u8Factor)
	{
		return ERROR;
	}
	ADCSRA &= PRESCALER_SELECTION_BIT_MASK;
	ADCSRA |= Copy_u8Factor;
	return NO_ERROR;
}

void __vector_16() __attribute__((signal));
void __vector_16()
{
	if(NULL != ADC_ptrfuncISR)
	{
		ADC_ptrfuncISR();
	}
}
