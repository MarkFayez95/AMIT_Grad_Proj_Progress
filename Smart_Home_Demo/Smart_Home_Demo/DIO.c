/*
 * DIO.c
 *
 * Created: 20/03/2021 11:00:23 AM
 *  Author: Mark Fayez
 */ 
#include "DIO.h"

void DIO_SetPortDir(PORT_REG* Port, uint8 Dir)
{
	Port->DDR = Dir;
}
void DIO_SetPinDir(PORT_REG* Port, uint8 Pin, uint8 Dir)
{
	Port->DDR &= ~(1<<Pin);
	Port->DDR |= ((Dir<<Pin) & (1<<Pin));
}

void DIO_SetPortValue(PORT_REG* Port, uint8 Value)
{
	Port->PORT = Value;
}
void DIO_SetPinValue(PORT_REG* Port, uint8 Pin, uint8 Value)
{
	Port->PORT &= ~(1<<Pin);
	Port->PORT |= ((Value<<Pin) & (1<<Pin));
}

void DIO_ReadPortValue(PORT_REG* Port, uint8* Value)
{
	*Value = Port->PIN;
}
void DIO_ReadPinValue(PORT_REG* Port, uint8 Pin, uint8* Value)
{
	*Value = GetBit(Port->PIN,Pin);
}

void DIO_TogglePort(PORT_REG* Port)
{
	Port->PORT ^= DIO_PORT_HIGH;
	
}
void DIO_TogglePin(PORT_REG* Port, uint8 Pin)
{
	ToggleBit(Port->PORT,Pin);
}

void DIO_SetPortPullup(PORT_REG* Port)
{
	Port->PORT = DIO_PORT_HIGH;
}
void DIO_SetPinPullup(PORT_REG* Port, uint8 Pin)
{
	SetBit(Port->PORT,Pin);
}