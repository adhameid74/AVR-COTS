#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DCMOTOR_interface.h"

void DCMOTOR_voidRotateClockWise(DC_MOTOR_t* MOTOR)
{
	DIO_u8SetPinValue(MOTOR->PORT, MOTOR->AD_PIN, DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(MOTOR->PORT, MOTOR->BC_PIN, DIO_u8_PIN_HIGH);
}

void DCMOTOR_voidRotateCounterClockWise(DC_MOTOR_t* MOTOR)
{
	DIO_u8SetPinValue(MOTOR->PORT, MOTOR->BC_PIN, DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(MOTOR->PORT, MOTOR->AD_PIN, DIO_u8_PIN_HIGH);
}

void DCMOTOR_voidBreak(DC_MOTOR_t* MOTOR)
{
	DIO_u8SetPinValue(MOTOR->PORT, MOTOR->BC_PIN, DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(MOTOR->PORT, MOTOR->AD_PIN, DIO_u8_PIN_LOW);
}
