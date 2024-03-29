/**************************************************************/
/**************************************************************/
/***********	Author: 	Adham Eid	***********************/
/***********	Component: 	PORT	    ***********************/
/***********	Layer: 		MCAL		***********************/
/***********	Version: 	1.00		***********************/
/**************************************************************/
/**************************************************************/

#ifndef PORT_PRIVATE_H_
#define PORT_PRIVATE_H_

#define CONC(BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0)				CONC_HELPER(BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0)
#define CONC_HELPER(BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0)		0b##BIT7##BIT6##BIT5##BIT4##BIT3##BIT2##BIT1##BIT0

#define PORTA_DIR			CONC(PORTA_u8_PIN7_DIR, PORTA_u8_PIN6_DIR, PORTA_u8_PIN5_DIR, PORTA_u8_PIN4_DIR, PORTA_u8_PIN3_DIR, PORTA_u8_PIN2_DIR, PORTA_u8_PIN1_DIR, PORTA_u8_PIN0_DIR)
#define PORTB_DIR			CONC(PORTB_u8_PIN7_DIR, PORTB_u8_PIN6_DIR, PORTB_u8_PIN5_DIR, PORTB_u8_PIN4_DIR, PORTB_u8_PIN3_DIR, PORTB_u8_PIN2_DIR, PORTB_u8_PIN1_DIR, PORTB_u8_PIN0_DIR)
#define PORTC_DIR			CONC(PORTC_u8_PIN7_DIR, PORTC_u8_PIN6_DIR, PORTC_u8_PIN5_DIR, PORTC_u8_PIN4_DIR, PORTC_u8_PIN3_DIR, PORTC_u8_PIN2_DIR, PORTC_u8_PIN1_DIR, PORTC_u8_PIN0_DIR)
#define PORTD_DIR			CONC(PORTD_u8_PIN7_DIR, PORTD_u8_PIN6_DIR, PORTD_u8_PIN5_DIR, PORTD_u8_PIN4_DIR, PORTD_u8_PIN3_DIR, PORTD_u8_PIN2_DIR, PORTD_u8_PIN1_DIR, PORTD_u8_PIN0_DIR)

#define PORTA_INIT_VALUE	CONC(PORTA_u8_PIN7_INIT_VALUE, PORTA_u8_PIN6_INIT_VALUE, PORTA_u8_PIN5_INIT_VALUE, PORTA_u8_PIN4_INIT_VALUE, PORTA_u8_PIN3_INIT_VALUE, PORTA_u8_PIN2_INIT_VALUE, PORTA_u8_PIN1_INIT_VALUE, PORTA_u8_PIN0_INIT_VALUE)
#define PORTB_INIT_VALUE	CONC(PORTB_u8_PIN7_INIT_VALUE, PORTB_u8_PIN6_INIT_VALUE, PORTB_u8_PIN5_INIT_VALUE, PORTB_u8_PIN4_INIT_VALUE, PORTB_u8_PIN3_INIT_VALUE, PORTB_u8_PIN2_INIT_VALUE, PORTB_u8_PIN1_INIT_VALUE, PORTB_u8_PIN0_INIT_VALUE)
#define PORTC_INIT_VALUE	CONC(PORTC_u8_PIN7_INIT_VALUE, PORTC_u8_PIN6_INIT_VALUE, PORTC_u8_PIN5_INIT_VALUE, PORTC_u8_PIN4_INIT_VALUE, PORTC_u8_PIN3_INIT_VALUE, PORTC_u8_PIN2_INIT_VALUE, PORTC_u8_PIN1_INIT_VALUE, PORTC_u8_PIN0_INIT_VALUE)
#define PORTD_INIT_VALUE	CONC(PORTD_u8_PIN7_INIT_VALUE, PORTD_u8_PIN6_INIT_VALUE, PORTD_u8_PIN5_INIT_VALUE, PORTD_u8_PIN4_INIT_VALUE, PORTD_u8_PIN3_INIT_VALUE, PORTD_u8_PIN2_INIT_VALUE, PORTD_u8_PIN1_INIT_VALUE, PORTD_u8_PIN0_INIT_VALUE)


#endif