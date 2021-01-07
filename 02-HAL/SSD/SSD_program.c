#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SSD_interface.h"
#include "SSD_private.h"

void SSD_voidDisplayNumber(SSD_t* SSD, u8 Copy_u8Number)
{
	u8 Local_u8Numbers[10] = {SSD_u8_ZERO, SSD_u8_ONE, SSD_u8_TWO, SSD_u8_THREE, SSD_u8_FOUR, SSD_u8_FIVE, SSD_u8_SIX, SSD_u8_SEVEN, SSD_u8_EIGHT, SSD_u8_NINE};
	DIO_u8SetPinValue(SSD->SSD_ENABLE_PORT, SSD->SSD_ENABLE_PIN, SSD->SSD_MODE);
	if(SSD_u8_COMMON_ANODE==SSD->SSD_MODE)
	{
		DIO_u8SetPortValue(SSD->SSD_PORT, Local_u8Numbers[Copy_u8Number]);
	}
	else
	{
		DIO_u8SetPortValue(SSD->SSD_PORT, !Local_u8Numbers[Copy_u8Number]);
	}
}

void SSD_voidDisplayPattern(SSD_t* SSD, u8 Copy_u8Pattern)
{
	DIO_u8SetPinValue(SSD->SSD_ENABLE_PORT, SSD->SSD_ENABLE_PIN, SSD->SSD_MODE);
	DIO_u8SetPortValue(SSD->SSD_PORT, Copy_u8Pattern);
}
