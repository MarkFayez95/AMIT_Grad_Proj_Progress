/*
 * LCD.h
 *
 * Created: 26/03/2021 1:13:54 PM
 *  Author: Mark Fayez
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "LCD_CFG.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void LCD_Init (void);
void LCD_WriteCommand (uint8 cmd);
void LCD_WriteChar (uint8 data);
void LCD_WriteInteger (sint32 num);
void LCD_WriteString(uint8* str);
void LCD_GoToLocation(uint8 row, uint8 col);
void LCD_Clear (void);


#endif /* LCD_H_ */