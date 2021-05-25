/*
 * Button.c
 *
 * Created: 20/03/2021 9:43:21 AM
 *  Author: Mark Fayez
 */ 
#include "Button.h"

#define F_CPU 16000000
#include "util/delay.h"

void Button_Init(uint8 Button)
{
	switch(Button)
	{
		case BUTTON0:
			DIO_SetPinDir(Button0_Port, Button0_Pin, DIO_PIN_OUTPUT);
		break;
		
		case BUTTON1:
		DIO_SetPinDir(Button1_Port, Button1_Pin, DIO_PIN_OUTPUT);
		break;
		
		case BUTTON2:
		DIO_SetPinDir(Button2_Port, Button2_Pin, DIO_PIN_OUTPUT);
		break;
		
		default:
		break;
	}
}

uint8 Button_GetValue(uint8 Button)
{
	uint8 Value = 0;
	uint8 DeBounce = 0;
	
	
	switch(Button)
	{
		case BUTTON0:
			DIO_ReadPinValue(Button0_Port, Button0_Pin, &Value);
			DIO_ReadPinValue(Button0_Port, Button0_Pin, &DeBounce);
			while(DeBounce == 1)
				DIO_ReadPinValue(Button0_Port, Button0_Pin, &DeBounce);
		break;
		
		case BUTTON1:
			DIO_ReadPinValue(Button1_Port, Button1_Pin, &Value);
			DIO_ReadPinValue(Button1_Port, Button1_Pin, &DeBounce);
			while(DeBounce == 1)
				DIO_ReadPinValue(Button1_Port, Button1_Pin, &DeBounce);
		break;
		
		case BUTTON2:
			DIO_ReadPinValue(Button2_Port, Button2_Pin, &Value);
			DIO_ReadPinValue(Button2_Port, Button2_Pin, &DeBounce);
			while(DeBounce == 1)
				DIO_ReadPinValue(Button2_Port, Button2_Pin, &DeBounce);
		break;
		
		default:
		break;
	}
	
	_delay_ms(10);
	
	return Value;
	
}