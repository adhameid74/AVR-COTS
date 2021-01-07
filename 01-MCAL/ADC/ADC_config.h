/***********************************************************
************************************************************
				Author: 		Adham Eid
				Component:		ADC
				File:			CONFIG
				Layer:			MCAL
				Version:		1.00
************************************************************
***********************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/**********************************************************/
/* Options:
 * 1- ADC_u8_AREF
 * 2- ADC_u8_AVCC
 * 3- ADC_u8_INTERNAL_2_56_VOLT
 */
#define ADC_REF_SELECTION			ADC_u8_AVCC
/**********************************************************/
/* Options:
 * 1- ADC_u8_RESULT_8_BITS
 * 2- ADC_u8_RESULT_10_BITS
 */
#define ADC_RESULT					ADC_u8_RESULT_8_BITS
/**********************************************************/
/* Options:
 * 1- DIVIDE_BY_2
 * 2- DIVIDE_BY_4
 * 3- DIVIDE_BY_8
 * 4- DIVIDE_BY_16
 * 5- DIVIDE_BY_32
 * 6- DIVIDE_BY_64
 * 7- DIVIDE_BY_128
 */
#define ADC_PRESCALER_SELECTION		DIVIDE_BY_128
/**********************************************************/
/* Options:
 * 1- ENABLE
 * 2- DISABLE
 */
#define ADC_EN						ENABLE
/**********************************************************/
#endif
