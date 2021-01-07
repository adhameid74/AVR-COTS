/**************************************************************/
/**************************************************************/
/***********	Author: 	Adham Eid	***********************/
/***********	Component: 	KEYPAD	    ***********************/
/***********	Layer: 		HAL			***********************/
/***********	Version: 	1.00		***********************/
/**************************************************************/
/**************************************************************/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"

u8 KEYPAD_u8GetPressedKey()
{
	u8 Local_u8RowIndex, Local_u8ColIndex, Local_u8State;
	u8 Local_u8KeyPadArr[KEYPAD_u8_NUM_OF_ROWS][KEYPAD_u8_NUM_OF_COL] = KEYPAD_u8_KEYS_ARRAY;
	u8 Local_u8RowPins[KEYPAD_u8_NUM_OF_ROWS] = {KEYPAD_u8_R1,KEYPAD_u8_R2,KEYPAD_u8_R3,KEYPAD_u8_R4};
	u8 Local_u8ColPins[KEYPAD_u8_NUM_OF_COL] = {KEYPAD_u8_C1,KEYPAD_u8_C2,KEYPAD_u8_C3,KEYPAD_u8_C4};

	for(Local_u8ColIndex = 0; Local_u8ColIndex < KEYPAD_u8_NUM_OF_COL; Local_u8ColIndex++)
	{
		DIO_u8SetPinValue(KEYPAD_u8_PORT, Local_u8ColPins[Local_u8ColIndex], DIO_u8_PIN_LOW);

		for(Local_u8RowIndex = 0; Local_u8RowIndex < KEYPAD_u8_NUM_OF_ROWS; Local_u8RowIndex++)
		{
			DIO_u8GetPinValue(KEYPAD_u8_PORT, Local_u8RowPins[Local_u8RowIndex], &Local_u8State);
			if(DIO_u8_PIN_LOW == Local_u8State)
			{
				while(DIO_u8_PIN_LOW == Local_u8State)
				{
					DIO_u8GetPinValue(KEYPAD_u8_PORT, Local_u8RowPins[Local_u8RowIndex], &Local_u8State);
				}
				return Local_u8KeyPadArr[Local_u8RowIndex][Local_u8ColIndex];
			}
		}
		DIO_u8SetPinValue(KEYPAD_u8_PORT, Local_u8ColPins[Local_u8ColIndex], DIO_u8_PIN_HIGH);
	}
	return NO_KEY_PRESSED;
}
