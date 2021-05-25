/*
 * Button.h
 *
 * Created: 20/03/2021 9:43:04 AM
 *  Author: Mark Fayez
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2

#include "DIO.h"

#define Button0_Port DIO_PORTB
#define Button0_Pin DIO_PIN_0

#define Button1_Port DIO_PORTD
#define Button1_Pin DIO_PIN_6

#define Button2_Port DIO_PORTD
#define Button2_Pin DIO_PIN_2

void Button_Init(uint8 Button);
uint8 Button_GetValue(uint8 Button);



#endif /* BUTTON_H_ */