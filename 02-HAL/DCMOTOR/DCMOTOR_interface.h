#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

typedef struct
{
	u8 AD_PIN;
	u8 BC_PIN;
	u8 PORT;
} DC_MOTOR_t;

void DCMOTOR_voidRotateClockWise(DC_MOTOR_t* MOTOR);
void DCMOTOR_voidRotateCounterClockWise(DC_MOTOR_t* MOTOR);
void DCMOTOR_voidBreak(DC_MOTOR_t* MOTOR);

#endif
