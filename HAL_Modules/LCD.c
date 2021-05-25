/*
 * LCD.c
 *
 * Created: 26/03/2021 1:13:42 PM
 *  Author: Mark Fayez
 */ 
#include "LCD.h"

void LCD_Init (void)
{
	#if LCD_MODE == 4
	
	DIO_SetPinDir(LCD_4BIT_MODE_CMD_PORT, LCD_RS_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_MODE_CMD_PORT, LCD_RW_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN , DIO_PIN_OUTPUT);
	
	DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT, LCD_D4_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT, LCD_D5_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT, LCD_D6_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT, LCD_D7_PIN , DIO_PIN_OUTPUT);
	
	_delay_ms(100);
	
	LCD_WriteCommand(0x33);
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);
	
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x01);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x02);
	
	#elif LCD_MODE == 8
	
	DIO_SetPinDir(LCD_8BIT_MODE_CMD_PORT, LCD_RS_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_8BIT_MODE_CMD_PORT, LCD_RW_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN , DIO_PIN_OUTPUT);
	
	DIO_SetPortDir(LCD_8BIT_MODE_DATA_PORT, DIO_PORT_OUTPUT);
	
	_delay_ms(100);
	
	LCD_WriteCommand(0x38);
	
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x01);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x02);
	
	#endif
}

void LCD_WriteCommand (uint8 cmd)
{
	
	#if LCD_MODE == 4
	
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	LCD_4BIT_MODE_DATA_BUS = (cmd & 0xf0) | (LCD_4BIT_MODE_DATA_BUS & 0x0f);
	
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	LCD_4BIT_MODE_DATA_BUS = (cmd << 4) | (LCD_4BIT_MODE_DATA_BUS & 0x0f);
	
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	#elif LCD_MODE == 8
	
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	LCD_8BIT_MODE_DATA_BUS = cmd;
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	#endif
}

void LCD_WriteChar (uint8 data)
{
	#if LCD_MODE == 4
	
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	LCD_4BIT_MODE_DATA_BUS = (data & 0xf0) | (LCD_4BIT_MODE_DATA_BUS & 0x0f);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	LCD_4BIT_MODE_DATA_BUS = (data << 4) | (LCD_4BIT_MODE_DATA_BUS & 0x0f);
	
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	#elif LCD_MODE == 8
	
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	LCD_8BIT_MODE_DATA_BUS = data;
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_8BIT_MODE_CMD_PORT, LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	#endif
	
}


/*  Assignment  */
void LCD_WriteInteger (sint32 num)
{
	sint32 temp_num;
	uint16 increment_temp_num = 0;
	sint8 counter = 0; // adjusting variable to be signed solve the last loop going infinite
	
	if (num < 0)
	{
		LCD_WriteChar('-');
		temp_num = num * -1;
	}
	else
		temp_num = num;
	
	if(temp_num == 0)
	{
		LCD_WriteChar('0');
	}
	else
	{
		while (temp_num > 0 && counter < 10)
		{
			increment_temp_num = ((increment_temp_num * 10) + (temp_num % 10));
			temp_num /= 10;
			counter++;
		}
		counter--;
		while(counter>=0)
		{
			LCD_WriteChar('0' + (increment_temp_num % 10));
			increment_temp_num /= 10;
			counter--;
		}
	}
}
/******************/

void LCD_WriteString(uint8* str)
{
	uint8 Str_count = 0;
	while (str[Str_count] != '\0')
	{
		LCD_WriteChar (str[Str_count]);
		Str_count++;
	}
}

void LCD_GoToLocation(uint8 row, uint8 col)
{
	uint8 rows[2] = {0x80,0xc0};
	
	LCD_WriteCommand(rows[row]+col);
	
}

void LCD_Clear (void)
{
	LCD_WriteCommand(0x01);
}

