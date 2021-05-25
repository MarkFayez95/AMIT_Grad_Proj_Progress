/*
 * LED.c
 *
 * Created: 19/03/2021 11:59:49 AM
 *  Author: Mark Fayez
 */ 

#include "LED.h"


void LED_Init(uint8 LED)
{
	switch(LED)
	{
		case LED0:
			DIO_SetPinDir(LED0_PORT, LED0_PIN, DIO_PIN_INPUT);
		break;
		
		case LED1:
			DIO_SetPinDir(LED1_PORT, LED1_PIN, DIO_PIN_INPUT);
		break;
		
		case LED2:
			DIO_SetPinDir(LED2_PORT, LED2_PIN, DIO_PIN_INPUT);
		break;
		
		case ALL_LEDS:
			DIO_SetPinDir(LED0_PORT, LED0_PIN, DIO_PIN_INPUT);
			DIO_SetPinDir(LED1_PORT, LED1_PIN, DIO_PIN_INPUT);
			DIO_SetPinDir(LED2_PORT, LED2_PIN, DIO_PIN_INPUT);
		break;
		
		default:
		break;
	}
	
}
#ifdef CALLBACK_INT_ENABLE
	void LED0_Init(void)
	{
		DIO_SetPinDir(LED0_PORT, LED0_PIN, DIO_PIN_INPUT);
	}
	void LED1_Init(void)
	{
		DIO_SetPinDir(LED1_PORT, LED1_PIN, DIO_PIN_INPUT);
	}
	void LED2_Init(void)
	{
		DIO_SetPinDir(LED2_PORT, LED2_PIN, DIO_PIN_INPUT);
	}
#endif

#ifndef CALLBACK_INT_ENABLE
	void LED_ON(uint8 LED)
	{
		switch(LED)
		{
			case LED0:
			DIO_SetPinValue(LED0_PORT, LED0_PIN, DIO_PIN_HIGH);
			break;
			
			case LED1:
			DIO_SetPinValue(LED1_PORT, LED1_PIN, DIO_PIN_HIGH);
			break;
			
			case LED2:
			DIO_SetPinValue(LED2_PORT, LED2_PIN, DIO_PIN_HIGH);
			break;
			
			default:
			break;
		}
	}
#endif
#ifdef CALLBACK_INT_ENABLE
	void LED0_ON(void)
	{
		DIO_SetPinValue(LED0_PORT, LED0_PIN, DIO_PIN_HIGH);
	}
	void LED1_ON(void)
	{
		DIO_SetPinValue(LED1_PORT, LED1_PIN, DIO_PIN_HIGH);
	}
	void LED2_ON(void)
	{
		DIO_SetPinValue(LED2_PORT, LED2_PIN, DIO_PIN_HIGH);
	}
#endif

#ifndef CALLBACK_INT_ENABLE
	void LED_OFF(uint8 LED)
	{
		switch(LED)
		{
			case LED0:
			DIO_SetPinValue(LED0_PORT, LED0_PIN, DIO_PIN_LOW);
			break;
			
			case LED1:
			DIO_SetPinValue(LED1_PORT, LED1_PIN, DIO_PIN_LOW);
			break;
			
			case LED2:
			DIO_SetPinValue(LED2_PORT, LED2_PIN, DIO_PIN_LOW);
			break;
			
			default:
			break;
		}
	}
#endif
#ifdef CALLBACK_INT_ENABLE
	void LED0_OFF(void)
	{
		DIO_SetPinValue(LED0_PORT, LED0_PIN, DIO_PIN_LOW);
	}
	void LED1_OFF(void)
	{
		DIO_SetPinValue(LED1_PORT, LED1_PIN, DIO_PIN_LOW);
	}
	void LED2_OFF(void)
	{
		DIO_SetPinValue(LED2_PORT, LED2_PIN, DIO_PIN_LOW);
	}
#endif

#ifndef CALLBACK_INT_ENABLE
	void LED_Toggle(uint8 LED)
	{
		switch(LED)
		{
			case LED0:
			DIO_TogglePin(LED0_PORT, LED0_PIN);
			break;
			
			case LED1:
			DIO_TogglePin(LED1_PORT, LED1_PIN);
			break;
			
			case LED2:
			DIO_TogglePin(LED2_PORT, LED2_PIN);
			break;
			
			default:
			break;
		}
	}
#endif
#ifdef CALLBACK_INT_ENABLE
	void LED0_Toggle(void)
	{
		DIO_TogglePin(LED0_PORT, LED0_PIN);
	}
	void LED1_Toggle(void)
	{
		DIO_TogglePin(LED1_PORT, LED1_PIN);
	}
	void LED2_Toggle(void)
	{
		DIO_TogglePin(LED2_PORT, LED2_PIN);
	}
#endif