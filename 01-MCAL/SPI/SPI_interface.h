/**
 * @file SPI_interface.h
 * @author Adham Eid (adhameid0@gmail.com)
 * @brief 
 * @version 1.0
 * @date 19-05-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidInit();
u8 SPI_u8TransceiveSynch(u8 Copy_u8TransmittedData, u8* Copy_pu8ReceivedData);

#endif
