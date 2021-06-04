/*
 * LED.c
 *
 * Created: 19/03/2021 11:59:49 AM
 *  Author: Mark Fayez
 */ 

#include "LED.h"


#ifdef LEDS_VOID_INPUT_FUNCTIONS
	void LED0_Init(void)
	{
		DIO_SetPinDir(LED0_PORT, LED0_PIN, DIO_PIN_OUTPUT);
	}
	void LED1_Init(void)
	{
		DIO_SetPinDir(LED1_PORT, LED1_PIN, DIO_PIN_OUTPUT);
	}
	void LED2_Init(void)
	{
		DIO_SetPinDir(LED2_PORT, LED2_PIN, DIO_PIN_OUTPUT);
	}

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

void LED_Init(uint8 LED)
{
	switch(LED)
	{
		case LED0:
			DIO_SetPinDir(LED0_PORT, LED0_PIN, DIO_PIN_OUTPUT);
		break;
		
		case LED1:
			DIO_SetPinDir(LED1_PORT, LED1_PIN, DIO_PIN_OUTPUT);
		break;
		
		case LED2:
			DIO_SetPinDir(LED2_PORT, LED2_PIN, DIO_PIN_OUTPUT);
		break;
		
		case ALL_LEDS:
			DIO_SetPinDir(LED0_PORT, LED0_PIN, DIO_PIN_OUTPUT);
			DIO_SetPinDir(LED1_PORT, LED1_PIN, DIO_PIN_OUTPUT);
			DIO_SetPinDir(LED2_PORT, LED2_PIN, DIO_PIN_OUTPUT);
		break;
		
		default:
		break;
	}

}
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

