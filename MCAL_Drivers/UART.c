/*
 * UART.c
 *
 * Created: 05/05/2021 5:08:24 PM
 *  Author: Mark Fayez
 */ 
#include "UART.h"


void UART_Init(void)
{
	// Set Tx Pin as output 
	DDRD |= (1<<PIN0);
	
	// Set Rx Pin as input
	DDRD &= ~(1<<PIN1);
	
	// enable Tx and Rx
	UCSRB |= (1<<TXEN) | (1<<RXEN);
	
	// Choose UCSRC Register then set data size to be 8 bits
	UCSRC |= (1<<UCSRC_URSEL) | (1<<UCSZ0) | (1<<UCSZ1); 
	
	// Set Baud Rate
	UBRRL = ( UART_Clk_Sor / (UART_Presc * Baud_Rate_Hundred) ) - 1;
}

void UART_Tx(uint8 data)
{
	UDR = data;
	while ( GetBit(UCSRA,TXCIE) == 0 );
	ClearBit(UCSRA,TXCIE);
}

uint8 UART_Rx(void)
{
	while (GetBit(UCSRA,RXCIE) == 0);
	ClearBit(UCSRA,RXCIE);
	return UDR;
}

// Maximum characters for this function is 255 character
void UART_TxString(uint8* str)
{
	uint8 count=0;
	
	while(str[count] != '\0')
	{
		UART_Tx(str[count]);
		count ++;
	}
}
