/*
 * LCD.h
 *
 * Created: 26/03/2021 1:13:54 PM
 *  Author: Mark Fayez
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "LCD_CFG.h"

#define LCD_ROW_1   0
#define LCD_ROW_2   1
#define LCD_SHIFT_CURSOR    1

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <util/delay.h>

void LCD_Init (void);
void LCD_WriteCommand (uint8 cmd);
void LCD_WriteChar (uint8 data);
void LCD_WriteInteger (sint32 num);
void LCD_WriteString(uint8* str);
void LCD_GoToLocation(uint8 row, uint8 col);
void LCD_Clear (void);


#endif /* LCD_H_ */