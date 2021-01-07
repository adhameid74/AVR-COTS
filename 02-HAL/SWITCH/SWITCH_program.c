#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SWITCH_interface.h"

u8 SWITCH_u8IsPressed(SWITCH_t* SWITCH)
{
	u8 Local_u8SwitchState;
	DIO_u8GetPinValue(SWITCH->PORT, SWITCH->PIN, &Local_u8SwitchState);
	if(SWITCH->ACTIVE_STATE==Local_u8SwitchState)
	{
		return SWITCH_u8_PRESSED;
	}
	else
	{
		return SWITCH_u8_NOT_PRESSED;
	}
}
