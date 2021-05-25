/*
 * LCD_CFG.h
 *
 * Created: 26/03/2021 1:14:13 PM
 *  Author: Mark Fayez
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include "DIO.h"

#define	LCD_MODE 4

#if LCD_MODE == 4

#define		LCD_4BIT_MODE_CMD_PORT		DIO_PORTB
#define		LCD_4BIT_MODE_DATA_PORT		DIO_PORTA
#define		LCD_4BIT_MODE_DATA_BUS		PORTA

#define		LCD_RS_PIN		DIO_PIN_1
#define		LCD_RW_PIN		DIO_PIN_2
#define		LCD_E_PIN		DIO_PIN_3

#elif LCD_MODE == 8

#define		LCD_8BIT_MODE_CMD_PORT		DIO_PORTA
#define		LCD_8BIT_MODE_DATA_PORT		DIO_PORTB
#define		LCD_8BIT_MODE_DATA_BUS		PORTB

#define		LCD_RS_PIN		DIO_PIN_1
#define		LCD_RW_PIN		DIO_PIN_2
#define		LCD_E_PIN		DIO_PIN_3

#endif

#define		LCD_D0_PIN		DIO_PIN_0
#define		LCD_D1_PIN		DIO_PIN_1
#define		LCD_D2_PIN		DIO_PIN_2
#define		LCD_D3_PIN		DIO_PIN_3
#define		LCD_D4_PIN		DIO_PIN_4
#define		LCD_D5_PIN		DIO_PIN_5
#define		LCD_D6_PIN		DIO_PIN_6
#define		LCD_D7_PIN		DIO_PIN_7

#endif /* LCD_CFG_H_ */