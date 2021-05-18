/***********************************************************
************************************************************
				Author: 		Adham Eid
				Component:		ADC
				File:			INTERFACE
				Layer:			MCAL
				Version:		1.00
************************************************************
***********************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_u8_AREF						1
#define ADC_u8_AVCC						2
#define ADC_u8_INTERNAL_2_56_VOLT		3

#define ADC_u8_RESULT_8_BITS			1
#define ADC_u8_RESULT_10_BITS			2

#define ADC_u8_CHANNEL_0				0
#define ADC_u8_CHANNEL_1				1
#define ADC_u8_CHANNEL_2				2
#define ADC_u8_CHANNEL_3				3
#define ADC_u8_CHANNEL_4				4
#define ADC_u8_CHANNEL_5				5
#define ADC_u8_CHANNEL_6				6
#define ADC_u8_CHANNEL_7				7
#define ADC_u8_CHANNEL_0_0_10x			8
#define ADC_u8_CHANNEL_1_0_10x			9
#define ADC_u8_CHANNEL_0_0_200x			10
#define ADC_u8_CHANNEL_1_0_200x			11
#define ADC_u8_CHANNEL_2_2_10x			12
#define ADC_u8_CHANNEL_3_2_10x			13
#define ADC_u8_CHANNEL_2_2_200x			14
#define ADC_u8_CHANNEL_3_2_200x			15
#define ADC_u8_CHANNEL_0_1_1x			16
#define ADC_u8_CHANNEL_1_1_1x			17
#define ADC_u8_CHANNEL_2_1_1x			18
#define ADC_u8_CHANNEL_3_1_1x			19
#define ADC_u8_CHANNEL_4_1_1x			20
#define ADC_u8_CHANNEL_5_1_1x			21
#define ADC_u8_CHANNEL_6_1_1x			22
#define ADC_u8_CHANNEL_7_1_1x			23
#define ADC_u8_CHANNEL_0_2_1x			24
#define ADC_u8_CHANNEL_1_2_1x			25
#define ADC_u8_CHANNEL_2_2_1x			26
#define ADC_u8_CHANNEL_3_2_1x			27
#define ADC_u8_CHANNEL_4_2_1x			28
#define ADC_u8_CHANNEL_5_2_1x			29

#define DIVIDE_BY_2						1
#define DIVIDE_BY_4						2
#define DIVIDE_BY_8						3
#define DIVIDE_BY_16					4
#define DIVIDE_BY_32					5
#define DIVIDE_BY_64					6
#define DIVIDE_BY_128					7

void ADC_voidInit();
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_u16ptrResult, u32 Copy_u32TimeOut);
u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel, void (*ISR)(void));
u8 ADC_u8SetReference(u8 Copy_u8Reference);
u8 ADC_u8SetResultNumOfBits(u8 Copy_u8NumOfBits);
void ADC_voidEnable();
void ADC_voidDisable();
u8 ADC_u8SetPrescalerFactor(u8 Copy_u8Factor);

#endif
