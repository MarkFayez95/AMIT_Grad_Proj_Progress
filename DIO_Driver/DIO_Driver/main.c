/*
 * DIO_Driver.c
 *
 * Created: 25/05/2021 7:51:32 PM
 * Author : Mark Fayez
 */ 

#define F_CPU 16000000

#include "LED.h"
#include "Button.h"
#include <Util/delay.h>


int main(void)
{
	LED_Init(LED0);
	LED_Init(LED1);
	LED_Init(LED2);
	
	Button_Init(BUTTON0);
	Button_Init(BUTTON1);
	Button_Init(BUTTON2);
	
	/* Replace with your application code */
	while (1)
	{
		if(Button_GetValue(BUTTON0) == 1)
		{
			LED_Toggle(LED0);
			_delay_ms(500);
			LED_Toggle(LED0);
		}
		else if(Button_GetValue(BUTTON1) == 1)
		{
			LED_Toggle(LED1);
			_delay_ms(500);
			LED_Toggle(LED1);
		}
		else if(Button_GetValue(BUTTON2) == 1)
		{
			LED_Toggle(LED2);
			_delay_ms(500);
			LED_Toggle(LED2);
		}
		
	}
}
