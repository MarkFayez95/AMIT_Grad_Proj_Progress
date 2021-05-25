/*
 * SPI.c
 *
 * Created: 24/04/2021 11:54:41 AM
 *  Author: Mark Fayez
 */ 

#include "SPI.h"

void SPI_Master_Init(void)
{
	//MISO
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_6,DIO_PIN_INPUT);
	//MOSI
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_5,DIO_PIN_OUTPUT);
	//CLK
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_7,DIO_PIN_OUTPUT);
	//SS
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_4,DIO_PIN_OUTPUT);
	
	// Set Master & Set Clk Presc & Enable SPI Peripheral
	SPI->SPCR |= (1<<MSTR);
	SPI->SPCR |= (1<<SPR1) | (1<<SPR0);
	SPI->SPCR |= (1<<SPE);
	
	DIO_SetPinValue(DIO_PORTB,DIO_PIN_4,DIO_PIN_HIGH);
	
	_delay_ms(30);
}
void SPI_Slave_Init(void)
{
	//MISO
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_6,DIO_PIN_OUTPUT);
	//MOSI
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_5,DIO_PIN_INPUT);
	//CLK
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_7,DIO_PIN_INPUT);
	//SS
	DIO_SetPinDir(DIO_PORTB,DIO_PIN_4,DIO_PIN_INPUT);
	
	// Enable SPI Peripheral
	SPI->SPCR |= (1<<SPE);
}

void SPI_Master_InitTrans(void)
{
	// Clear the SS to have the slaves ready to receive data
	DIO_SetPinValue(DIO_PORTB,DIO_PIN_4,DIO_PIN_LOW);
	_delay_ms(30);
}
void SPI_Master_TermTrans(void)
{
	// Set SS to terminate transmission to slaves
	DIO_SetPinValue(DIO_PORTB,DIO_PIN_4,DIO_PIN_HIGH);
}

uint8 SPI_Master_Transiver(uint8 data)
{
	uint8 Received_Data = 0;
	SPI_Master_InitTrans();
	SPI->SPDR = data;
	while(GetBit(SPI->SPSR,SPIF) == 0);
	
	Received_Data = SPI->SPDR;
	SPI_Master_TermTrans();
	return Received_Data;
	
}

uint8 SPI_Slave_Transiver(uint8 data)
{
	uint8 Received_Data = 0;
	
	SPI->SPDR = data;
	while(GetBit(SPI->SPSR,SPIF) == 0);
	
	Received_Data = SPI->SPDR;
	
	return Received_Data;
	
}