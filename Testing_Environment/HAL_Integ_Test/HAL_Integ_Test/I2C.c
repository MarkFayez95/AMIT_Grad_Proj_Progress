/*
 * I2C.c
 *
 * Created: 08/05/2021 10:41:19 AM
 *  Author: Mark Fayez
 */ 
#include "I2C.h"

void I2C_Master_Init(void)
{
	// Set Clock source for the I2C //
	TWBR = I2C_CLK_ATTRIBUTE;
	TWSR &= ~((1<<TWPS0) | (1<<TWPS1));
	
	// Enable I2C //
	TWCR = (1<<TWEN);
}
void I2C_Slave_Init(void)
{
	// set the Slave address
	TWAR = (I2C_SLAVE_ADDR<<TWA0);
	
	// Enable I2C //
	TWCR = (1<<TWEN);
}

void I2C_Start_Condition(void)
{
	// Generate a start condition and clear flag and Re-enable I2C //
	TWCR = (1<<TWEN) | (1<<TWSTA) | (1<<TWINT);
	
	// Blocking on Flag
	while (GetBit(TWCR,TWINT) == 0);
	
	// blocking on operation status 
	while ( (TWSR & I2C_OP_STATUS_MASK) != START_ACK);
}
void I2C_RepeatedStart(void)
{
	// Generate a start condition and clear flag and Re-enable I2C //
	TWCR = (1<<TWEN) | (1<<TWSTA) | (1<<TWINT);
	
	// Blocking on Flag
	while (GetBit(TWCR,TWINT) == 0);
	
	// blocking on operation status
	while ( (TWSR & I2C_OP_STATUS_MASK) != REP_START_ACK);
}

void I2C_Send_SlaveAddr_Write_Op(uint8 Slave_addr)
{
	// slave address with write operation //
	TWDR = (Slave_addr << 1);
	
	// clear flag and Re-enable I2C //
	TWCR = (1<<TWEN) | (1<<TWINT);
	
	// Blocking on Flag
	while (GetBit(TWCR,TWINT) == 0);
	
	// blocking on operation status
	while ( (TWSR & I2C_OP_STATUS_MASK) != SLAVE_ADD_AND_WR_ACK);
	
}
void I2C_Send_SlaveAddr_Read_Op(uint8 Slave_addr)
{
	// slave address with write operation //
	TWDR = (Slave_addr << 1) | I2C_READ;
	
	// clear flag and Re-enable I2C //
	TWCR = (1<<TWEN) | (1<<TWINT);
	
	// Blocking on Flag
	while (GetBit(TWCR,TWINT) == 0);
	
	// blocking on operation status
	while ( (TWSR & I2C_OP_STATUS_MASK) != SLAVE_ADD_AND_RD_ACK);
}

void I2C_Send_DataByte(uint8 Data_Byte)
{
	// send data byte //
	TWDR = Data_Byte;
	
	// clear flag and Re-enable I2C //
	TWCR = (1<<TWEN) | (1<<TWINT);
	
	// Blocking on Flag
	while (GetBit(TWCR,TWINT) == 0);
	
	// blocking on operation status
	while ((TWSR & I2C_OP_STATUS_MASK) != WR_BYTE_ACK);
}
uint8 I2C_Read_DataByte(void)
{
	// clear flag and Re-enable I2C //
	TWCR = (1<<TWEN) | (1<<TWINT);
	
	// Blocking on Flag
	while (GetBit(TWCR,TWINT) == 0);
	
	// blocking on operation status
	while ((TWSR & I2C_OP_STATUS_MASK) != RD_BYTE_WITH_ACK);
	
	// return with received data 
	return TWDR;
}

void I2C_Stop_Condition(void)
{
	// Generate a stop condition and clear flag and Re-enable I2C //
	TWCR = (1<<TWSTO) | (1<<TWEN) | (1<<TWINT);
}