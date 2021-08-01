/**
 * @file EEPROM_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 01-08-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

u8 EEPROM_u8WriteByte(u16 Copy_u16Location, u8 Copy_u8Data);
u8 EEPROM_u8ReadByte(u16 Copy_u16Location, u8* Copy_pu8Data);

#endif