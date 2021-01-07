#include "STD_TYPES.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"

u8 LCD_u8Position = 0;

void LCD_voidInit()
{
	#if LCD_u8_MODE == LCD_u8_8BIT_MODE

	_delay_ms(100);

	LCD_voidSendCommand(0b00111000);
	_delay_us(100);
	LCD_voidSendCommand(0b00001100);
	_delay_us(100);
	LCD_voidClear();
	_delay_ms(2);

	#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

	_delay_ms(100);
	
	LCD_voidSendCommand(0b00100000);
	LCD_voidSendCommand(0b00100000);
	LCD_voidSendCommand(0b10000000);
	_delay_us(100);
	LCD_voidSendCommand(0);
	LCD_voidSendCommand(0b11000000);
	_delay_us(100);
	LCD_voidClear();
	_delay_ms(2);

	#endif
}

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_LOW);
	
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Command);
	
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
}

void LCD_voidSendData(u8 Copy_u8Data)
{
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_RS_PIN,DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_RW_PIN,DIO_u8_PIN_LOW);
	
	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Data);
	
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_E_PIN,DIO_u8_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_u8_CTR_PORT,LCD_u8_E_PIN,DIO_u8_PIN_LOW);
}

void LCD_voidClear()
{
	LCD_u8Position = 0;
	#if LCD_u8_MODE == LCD_u8_8BIT_MODE

	LCD_voidSendCommand(LCD_u8_CLEAR);

	#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

	LCD_voidSendCommand(LCD_u8_CLEAR);
	LCD_voidSendCommand((LCD_u8_CLEAR&0b00001111)<<4);

	#endif
}

void LCD_voidWriteChar(u8 Copy_u8Data)
{
	LCD_u8Position++;
	if((LCD_u8Position>16) && (LCD_u8Position<100))
	{
		LCD_voidGotoXY(LCD_u8_SECOND_LINE, LCD_u8_COL_1);
		LCD_u8Position = 101;
	}
	else if(LCD_u8Position>116)
	{
		LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_COL_1);
		LCD_u8Position = 1;
	}

	#if LCD_u8_MODE == LCD_u8_8BIT_MODE

	LCD_voidSendData(Copy_u8Data);

	#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

	LCD_voidSendData(Copy_u8Data);
	LCD_voidSendData((Copy_u8Data&0b00001111)<<4);

	#endif
}

void LCD_voidWriteString(const char* Copy_String)
{
	while(*Copy_String != '\0')
	{
		LCD_u8Position++;
		if((LCD_u8Position>16) && (LCD_u8Position<100))
		{
			LCD_voidGotoXY(LCD_u8_SECOND_LINE, LCD_u8_COL_1);
			LCD_u8Position = 101;
		}
		else if(LCD_u8Position>116)
		{
			LCD_voidGotoXY(LCD_u8_FIRST_LINE, LCD_u8_COL_1);
			LCD_u8Position = 1;
		}

		#if LCD_u8_MODE == LCD_u8_8BIT_MODE

		LCD_voidSendData(*Copy_String);

		#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

		LCD_voidSendData(*Copy_String);
		LCD_voidSendData(((*Copy_String)&0b00001111)<<4);

		#endif
		Copy_String++;
	}
}

void LCD_voidWriteNumber(s32 Copy_s32Num)
{
	u32 Local_u32ReservedNum = 1;
	if (Copy_s32Num>=0)
	{
		while(Copy_s32Num!=0)
		{
			Local_u32ReservedNum = Local_u32ReservedNum*10 + Copy_s32Num%10;
			Copy_s32Num /= 10;
		}
		do
		{
			#if LCD_u8_MODE == LCD_u8_8BIT_MODE

			LCD_voidWriteChar(Local_u32ReservedNum%10+'0');

			#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

			LCD_voidWriteChar(Local_u32ReservedNum%10+'0');
			LCD_voidWriteChar(((Local_u32ReservedNum%10+'0')&0b00001111)<<4);

			#endif
			Local_u32ReservedNum /= 10;
		}while(Local_u32ReservedNum!=1);
	}
	else
	{
		Copy_s32Num *= -1;
		while(Copy_s32Num!=0)
		{
			Local_u32ReservedNum = Local_u32ReservedNum*10 + Copy_s32Num%10;
			Copy_s32Num /= 10;
		}
		#if LCD_u8_MODE == LCD_u8_8BIT_MODE

		LCD_voidWriteChar('-');

		#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

		LCD_voidWriteChar('-');
		LCD_voidWriteChar((('-')&0b00001111)<<4);

		#endif
		do
		{
			#if LCD_u8_MODE == LCD_u8_8BIT_MODE

			LCD_voidWriteChar(Local_u32ReservedNum%10+'0');

			#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

			LCD_voidWriteChar(Local_u32ReservedNum%10+'0');
			LCD_voidWriteChar(((Local_u32ReservedNum%10+'0')&0b00001111)<<4);

			#endif
			Local_u32ReservedNum /= 10;
		}while(Local_u32ReservedNum!=1);
	}
}

void LCD_voidGotoXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8Address;

	LCD_u8Position = Copy_u8XPos*100+Copy_u8YPos;

	if(Copy_u8XPos==LCD_u8_FIRST_LINE)
	{
		Local_u8Address = Copy_u8YPos;
	}
	else
	{
		Local_u8Address = 0x40 + Copy_u8YPos;
	}

	Local_u8Address|=1<<7;

	#if LCD_u8_MODE == LCD_u8_8BIT_MODE

	LCD_voidSendCommand(Local_u8Address);

	#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

	LCD_voidSendCommand(Local_u8Address);
	LCD_voidSendCommand((Local_u8Address&0b00001111)<<4);

	#endif
}

void LCD_voidDisplaySpecialChar(u8* Copy_u8Pattern, u8 Copy_u8BlockNumber, u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8Address, Local_u8Counter;

	Local_u8Address = Copy_u8BlockNumber*8;
	Local_u8Address|=1<<6;

	#if LCD_u8_MODE == LCD_u8_8BIT_MODE

	LCD_voidSendCommand(Local_u8Address);

	#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

	LCD_voidSendCommand(Local_u8Address);
	LCD_voidSendCommand((Local_u8Address&0b00001111)<<4);

	#endif

	for(Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
	{
		#if LCD_u8_MODE == LCD_u8_8BIT_MODE

		LCD_voidSendData(Copy_u8Pattern[Local_u8Counter]);

		#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

		LCD_voidSendData(Copy_u8Pattern[Local_u8Counter]);
		LCD_voidSendData(((Copy_u8Pattern[Local_u8Counter])&0b00001111)<<4);

		#endif
	}
	LCD_voidGotoXY(Copy_u8XPos, Copy_u8YPos);

	#if LCD_u8_MODE == LCD_u8_8BIT_MODE

	LCD_voidSendData(Copy_u8BlockNumber);

	#elif LCD_u8_MODE == LCD_u8_4BIT_MODE

	LCD_voidSendData(Copy_u8BlockNumber);
	LCD_voidSendData((Copy_u8BlockNumber&0b00001111)<<4);

	#endif
}
