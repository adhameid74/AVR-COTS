#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI_u8_INT0					6
#define EXTI_u8_INT1					7
#define EXTI_u8_INT2					5

#define EXTI_u8_SENSE_LOW_LEVEL			0
#define EXTI_u8_SENSE_ON_CHANGE			1
#define EXTI_u8_SENSE_FALLING_EDGE		2
#define EXTI_u8_SENSE_RISING_EDGE		3

void EXTI_voidINT0Init();
void EXTI_voidINT1Init();
void EXTI_voidINT2Init();

void EXTI_voidSetSenseControl(u8 Copy_u8INT, u8 Copy_u8Sense);
void EXTI_voidEnableINT(u8 Copy_u8INT);
void EXTI_voidDisableINT(u8 Copy_u8INT);

#endif
