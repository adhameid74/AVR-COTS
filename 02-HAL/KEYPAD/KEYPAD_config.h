/**************************************************************/
/**************************************************************/
/***********	Author: 	Adham Eid	***********************/
/***********	Component: 	KEYPAD	    ***********************/
/***********	Layer: 		HAL			***********************/
/***********	Version: 	1.00		***********************/
/**************************************************************/
/**************************************************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define NO_KEY_PRESSED				0xFF

#define KEYPAD_u8_PORT				DIO_u8_PORTA

#define KEYPAD_u8_C4				DIO_u8_PIN3
#define KEYPAD_u8_C3				DIO_u8_PIN2
#define KEYPAD_u8_C2				DIO_u8_PIN1
#define KEYPAD_u8_C1				DIO_u8_PIN0
#define KEYPAD_u8_R1				DIO_u8_PIN4
#define KEYPAD_u8_R2				DIO_u8_PIN5
#define KEYPAD_u8_R3				DIO_u8_PIN6
#define KEYPAD_u8_R4				DIO_u8_PIN7

#define KEYPAD_u8_KEYS_ARRAY		{{1,2,3,4} , {5,6,7,8} , {9,10,11,12} , {13,14,15,16}}

#endif
