/*
 * EEPROM.c
 *
 * Created: 08/05/2021 12:28:05 PM
 *  Author: Mark Fayez
 */ 
#include "EEPROM.h"

void EEPROM_Init(void)
{
	I2C_Master_Init();
}

void EEPROM_Write_Byte(uint8 data_byte, uint8 Loc)
{
	I2C_Start_Condition();
	I2C_Send_SlaveAddr_Write_Op(EEPROM_ADDR);
	I2C_Send_DataByte(Loc);
	I2C_Send_DataByte(data_byte);
	I2C_Stop_Condition();
	
}
void EEPROM_Write_Data(uint8* data_stream, uint8 Size, uint8 Loc)
{
	uint8 count = 0;
	I2C_Start_Condition();
	I2C_Send_SlaveAddr_Write_Op(EEPROM_ADDR);
	I2C_Send_DataByte(Loc);
	while(count < Size)
	{
		I2C_Send_DataByte(data_stream[count]);
		count++;
	}
	I2C_Stop_Condition();
}

uint8 EEPROM_Read_Byte(uint8 Loc)
{
	uint8 data;
	I2C_Start_Condition();
	I2C_Send_SlaveAddr_Write_Op(EEPROM_ADDR);
	I2C_Send_DataByte(Loc);
	I2C_RepeatedStart();
	I2C_Send_SlaveAddr_Read_Op(EEPROM_ADDR);
	data = I2C_Read_DataByte();
	I2C_Stop_Condition();
	return data;
}
void EEPROM_Read_Data(uint8* data_stream, uint8 Size, uint8 Loc)
{
	uint8 count = 0;
	I2C_Start_Condition();
	while (count < Size)
	{
		if(count != 0)
			I2C_RepeatedStart();
		I2C_Send_SlaveAddr_Write_Op(EEPROM_ADDR);
		I2C_Send_DataByte(Loc+count);
		I2C_RepeatedStart();
		I2C_Send_SlaveAddr_Read_Op(EEPROM_ADDR);
		data_stream[count] = I2C_Read_DataByte();
		count++;
	}
	I2C_Stop_Condition();
}
