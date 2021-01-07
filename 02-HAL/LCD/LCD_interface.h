#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_u8_4BIT_MODE		0
#define LCD_u8_8BIT_MODE		1

#define LCD_u8_FIRST_LINE		0
#define LCD_u8_SECOND_LINE		1

#define LCD_u8_CLEAR 			0b00000001

#define LCD_u8_COL_1			0
#define LCD_u8_COL_2			1
#define LCD_u8_COL_3			2
#define LCD_u8_COL_4			3
#define LCD_u8_COL_5			4
#define LCD_u8_COL_6			5
#define LCD_u8_COL_7			6
#define LCD_u8_COL_8			7
#define LCD_u8_COL_9			8
#define LCD_u8_COL_10			9
#define LCD_u8_COL_11			10
#define LCD_u8_COL_12			11
#define LCD_u8_COL_13			12
#define LCD_u8_COL_14			13
#define LCD_u8_COL_15			14
#define LCD_u8_COL_16			15


void LCD_voidInit();
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidClear();
void LCD_voidWriteChar(u8 Copy_u8Data);
void LCD_voidWriteString(const char* Copy_String);
void LCD_voidWriteNumber(s32 Copy_s32Num);
void LCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos);
void LCD_voidDisplaySpecialChar(u8* Copy_u8Pattern, u8 Copy_u8BlockNumber, u8 Copy_u8XPos, u8 Copy_u8YPos);

#endif
