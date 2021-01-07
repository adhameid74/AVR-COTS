#include "STD_TYPES.h"
#include "LED_interface.h"
#include "DIO_interface.h"

void LED_voidOn(LED_t* LED)
{
	DIO_u8SetPinValue(LED->LED_PORT, LED->LED_PIN, LED->LED_ACTIVE_STATE);
}

void LED_voidOff(LED_t* LED)
{
	DIO_u8SetPinValue(LED->LED_PORT, LED->LED_PIN, (-1*(LED->LED_ACTIVE_STATE)+1));
}
