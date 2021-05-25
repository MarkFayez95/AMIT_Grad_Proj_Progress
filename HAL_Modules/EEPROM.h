/*
 * EEPROM.h
 *
 * Created: 08/05/2021 12:28:15 PM
 *  Author: Mark Fayez
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C.h"

#define EEPROM_SLAVE_ADDR	0x50
#define EEPROM_EN_PIN_STAT	0
#define EEPROM_EN_BIT_LOC	3
#define EEPROM_BLOCK_SEL	0

#define EEPROM_ADDR		0b01010000 //(EEPROM_SLAVE_ADDR | (EEPROM_EN_PIN_STAT << EEPROM_EN_BIT_LOC) | EEPROM_BLOCK_SEL)

void EEPROM_Init(void);

void EEPROM_Write_Byte(uint8 data_byte, uint8 Loc);
void EEPROM_Write_Data(uint8* data_stream, uint8 Size, uint8 Loc);

uint8 EEPROM_Read_Byte(uint8 Loc);
void EEPROM_Read_Data(uint8* data_stream, uint8 Size, uint8 Loc);

#endif /* EEPROM_H_ */