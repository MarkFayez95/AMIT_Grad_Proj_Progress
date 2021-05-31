/*
 * I2C.h
 *
 * Created: 08/05/2021 10:40:51 AM
 *  Author: Mark Fayez
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "Bit_math.h"
#include "STD_DTypes.h"
#include "MCU.h"

#define START_ACK                0x08 // start has been sent
#define REP_START_ACK            0x10 // repeated start
#define SLAVE_ADD_AND_WR_ACK     0x18 // Master transmit ( slave address + Write request ) ACK
#define SLAVE_ADD_AND_RD_ACK     0x40 // Master transmit ( slave address + Read request ) ACK
#define WR_BYTE_ACK              0x28 // Master transmit data ACK
#define RD_BYTE_WITH_ACK		 0x58 // Master received data with not ACK
#define SLAVE_ADD_RCVD_RD_REQ    0xA8 // means that slave address is received with write req
#define SLAVE_ADD_RCVD_WR_REQ    0x60 // means that slave address is received with read req
#define SLAVE_DATA_RECEIVED      0x80 // means that read byte req is received
#define SLAVE_BYTE_TRANSMITTED   0xC0 // means that write byte req is received

#define I2C_READ			0x01
#define I2C_OP_STATUS_MASK	0xF8
#define I2C_SLAVE_ADDR		0x01
#define I2C_CLK_ATTRIBUTE	0x07

void I2C_Master_Init(void);
void I2C_Slave_Init(void);

void I2C_Start_Condition(void);
void I2C_RepeatedStart(void);
void I2C_Send_SlaveAddr_Write_Op(uint8 Slave_addr);
void I2C_Send_SlaveAddr_Read_Op(uint8 Slave_addr);

void I2C_Send_DataByte(uint8 Data_Byte);
uint8 I2C_Read_DataByte(void);

void I2C_Stop_Condition(void);


#endif /* I2C_H_ */