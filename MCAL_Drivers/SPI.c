/*
 * SPI.c
 *
 * Created: 24/04/2021 11:54:41 AM
 *  Author: Mark Fayez
 */ 

#include "Smart_Home_Sys_Config.h"
#include "SPI.h"

void SPI_Master_Init(void)
{
	//MISO
	DIO_SetPinDir(SPI_PORT,SPI_MISO_PIN,DIO_PIN_INPUT);
	//MOSI
	DIO_SetPinDir(SPI_PORT,SPI_MOSI_PIN,DIO_PIN_OUTPUT);
	//CLK
	DIO_SetPinDir(SPI_PORT,SPI_CLK_PIN,DIO_PIN_OUTPUT);
	//SS
	DIO_SetPinDir(SPI_PORT,SPI_SS_PIN,DIO_PIN_OUTPUT);
	
	// Set Master  & Set the polarity of the transmission to setup then sample
	SPI->SPCR |= (1<<MSTR) | (1<<CPHA);;
	
	// Set Clk Presc Osc/128
	SPI->SPCR |= (1<<SPR1) | (1<<SPR0);
	

	// Make the least significant bit to be transmitted first. i.e shift right
	//SPI->SPCR |= (1<<DORD);

	// Enable SPI Peripheral
	SPI->SPCR |= (1<<SPE);
	
	DIO_SetPinValue(SPI_PORT,SPI_SS_PIN,DIO_PIN_HIGH);
	
	_delay_ms(MASTER_SS_SET_DELAY_MS);
}

void SPI_Master_InitTrans(void)
{
	// Clear the SS to have the slaves ready to receive data
	DIO_SetPinValue(SPI_PORT,SPI_SS_PIN,DIO_PIN_LOW);
	_delay_ms(MASTER_SS_SET_DELAY_MS);
}

void SPI_Master_TermTrans(void)
{
	_delay_ms(MASTER_SS_SET_DELAY_MS);

	// Set SS to terminate transmission to slaves
	DIO_SetPinValue(SPI_PORT,SPI_SS_PIN,DIO_PIN_HIGH);
}

uint8 SPI_Transiver(uint8 data)
{
	uint8 Received_Data = 0;
	
	#if SPI_ROLE == SPI_MASTER
		// Clear SS Pin to start transmission
		SPI_Master_InitTrans();
		
		// write to SPDR of the Master to start the transmission and clock
		SPI->SPDR = data;
		
		// Hault on the end of transmission flag
		while(GetBit(SPI->SPSR,SPIF) == 0);
		
		// Read the received data from the SPI Data Register.
		Received_Data = SPI->SPDR;

		// Set the SS Pin once more to mark end of the transmission.
		SPI_Master_TermTrans();
	#elif SPI_ROLE == SPI_SLAVE
		SPI->SPDR = data;
		
		while(GetBit(SPI->SPSR,SPIF) == 0);

		Received_Data = SPI->SPDR;
	#endif /* SPI_ROLE */

	return Received_Data;
}

void SPI_Slave_Init(void)
{
	//MISO
	DIO_SetPinDir(SPI_PORT,SPI_MISO_PIN,DIO_PIN_OUTPUT);
	//MOSI
	DIO_SetPinDir(SPI_PORT,SPI_MOSI_PIN,DIO_PIN_INPUT);
	//CLK
	DIO_SetPinDir(SPI_PORT,SPI_CLK_PIN,DIO_PIN_INPUT);
	//SS
	DIO_SetPinDir(SPI_PORT,SPI_SS_PIN,DIO_PIN_INPUT);
	
	// Enable SPI Peripheral & Set the polarity of the transmission to setup then sample
	SPI->SPCR |= (1<<SPE) | (1<<CPHA);

	//make the least significant bit to be transmitted first. i.e shift right
	//SPI->SPCR |= (1<<DORD);		
}