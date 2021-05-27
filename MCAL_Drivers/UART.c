/*
 * UART.c
 *
 * Created: 05/05/2021 5:08:24 PM
 *  Author: Mark Fayez
 */ 
#include "UART.h"


void UART_Init(void)
{
	// Set Tx Pin as output & Rx Pin as input
	DIO_SetPinDir(UART_PORT, UART_TX_PIN, DIO_PIN_OUTPUT);
	DIO_SetPinDir(UART_PORT,UART_RX_PIN, DIO_PIN_INPUT);
	
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
	while ( GetBit(UCSRA,TXCIE) == UART_Flag_Down );
	ClearBit(UCSRA,TXCIE);
}

uint8 UART_Rx(void)
{
	while (GetBit(UCSRA,RXCIE) == UART_Flag_Down);
	ClearBit(UCSRA,RXCIE);
	return UDR;
}
void UART_RxString(uint8* str)
{
	uint8 Count = 0;
	str[count]=UART_Rx();
	while(str[count] != '\0')
	{
		count++;
		str[count] = UART_Rx();
	}
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
