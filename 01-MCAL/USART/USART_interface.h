/**
 * @file USART_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 16-01-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit();
u8 USART_u8SendDataSynch(u16 Copy_u16Data);
u8 USART_u8ReceiveDataSynch(u16* Copy_pu16Data);
u8 USART_u8SendArraySynch(u16* Copy_au16Data, u8 Copy_u8Size);
u8 USART_u8ReceiveArraySynch(u16* Copy_au16Data, u8 Copy_u8Size);

#endif