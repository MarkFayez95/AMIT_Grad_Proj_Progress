/*
 * UART.c
 *
 * MCAL Layer Driver that command the UART Peripheral.
 * Role in architecture: setting the hardware and commanding it to acheive a communication over UART with external devices.
 * It's ECU dependant.
 * 
 * Created: 05/05/2021 5:08:24 PM
 *  Author: Mark Fayez
 */ 
#include "Smart_Home_Sys_Config.h"
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
	// put data in UART Data Register
	UDR = data;
	// Hault on the end of Transmission flag.
	while ( GetBit(UCSRA,TXC) == UART_Flag_Down );

	// Clear the transmission flag
	ClearBit(UCSRA,TXC);
}

uint8 UART_Rx(void)
{
	// wait for flag from UART that data is received.
	while (GetBit(UCSRA,RXC) == UART_Flag_Down);

	// clear the flag.
	ClearBit(UCSRA,RXC);

	// return the data in the UART data register.
	return UDR;
}

// Maximum characters for this function is 255 character
void UART_RxString(uint8* str)
{
	uint8 Count = 0;
	// receive a character from UART by calling the UAR Receive byte function
	str[Count]=UART_Rx();

	// while received byte is not an end of packet (NULL terminator) keep receiving data concatenating it to the array.
	while((str[Count] != '\0') && (Count < 255))
	{
		Count++;
		str[Count] = UART_Rx();
	}
}

// Maximum characters for this function is 255 character
void UART_TxString(uint8* str)
{
	uint8 count=0;
	
	// while current byte is not an end of packet (NULL terminator) keep sending data bytes from the array.
	while((str[count] != '\0') && (Count < 255))
	{
		// this uses the UART Transmit byte earlier developed.
		UART_Tx(str[count]);
		count ++;
	}
}
