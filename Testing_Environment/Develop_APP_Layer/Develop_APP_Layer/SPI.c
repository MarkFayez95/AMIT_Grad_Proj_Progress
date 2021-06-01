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
	DIO_SetPinDir(SPI_PORT,SPI_MISO_PIN,DIO_PIN_INPUT);
	//MOSI
	DIO_SetPinDir(SPI_PORT,SPI_MOSI_PIN,DIO_PIN_OUTPUT);
	//CLK
	DIO_SetPinDir(SPI_PORT,SPI_CLK_PIN,DIO_PIN_OUTPUT);
	//SS
	DIO_SetPinDir(SPI_PORT,SPI_SS_PIN,DIO_PIN_OUTPUT);
	
	// Set Master & Set Clk Presc
	SPI->SPCR |= (1<<MSTR);
	SPI->SPCR |= (1<<SPR1) | (1<<SPR0);
	

	// Make the least significant bit to be transmitted first. i.e shift right
	SPI->SPCR |= (1<<DORD);

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
	// Set SS to terminate transmission to slaves
	DIO_SetPinValue(SPI_PORT,SPI_SS_PIN,DIO_PIN_HIGH);
}

uint8 SPI_Transiver(uint8 data)
{
	uint8 Received_Data = 0;
	uint8 Trans_N_Started_counter = 1;
	
	#if SPI_ROLE == SPI_MASTER
		// Clear SS Pin to start transmission
		SPI_Master_InitTrans();
		
		// write to SPDR of the Master to start the transmission and clock
		SPI->SPDR = data;
		
		while(GetBit(SPI->SPSR,SPIF) == 0);
		Received_Data = SPI->SPDR;

		SPI_Master_TermTrans();
	#elif SPI_ROLE == SPI_SLAVE
		uint8 Check_Trans_start = 0;
		
		DIO_GetPinValue(SPI_PORT,SPI_SS_PIN,&Check_Trans_start);
		if(Check_Trans_start != 0)
		{
			SPI->SPDR = data;
			while((GetBit(SPI->SPSR,SPIF) == 0) && (Trans_N_Started_counter != 0))
				Trans_N_Started_counter++;
			if(Trans_N_Started_counter == 0)
				Received_Data = TRANS_FAILED;
			else
				Received_Data = SPI->SPDR;
		}
		else
		{
			// wait till current transmission is completed
			while((GetBit(SPI->SPSR,SPIF) == 0) && (Trans_N_Started_counter != 0))
				Trans_N_Started_counter++;
			if(Trans_N_Started_counter == 0)
				Received_Data = TRANS_FAILED;
			else
			{
				// Load the required data to be sent
				SPI->SPDR = data;
				while(GetBit(SPI->SPSR,SPIF) == 0);
				Received_Data = SPI->SPDR;
			}
		}
		
	#endif
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
	
	// Enable SPI Peripheral
	SPI->SPCR |= (1<<SPE);

	//make the least significant bit to be transmitted first. i.e shift right
	SPI->SPCR |= (1<<DORD);		
}