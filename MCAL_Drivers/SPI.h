/*
 * SPI.h
 *
 * Created: 24/04/2021 11:54:55 AM
 *  Author: Mark Fayez
 */ 


#ifndef SPI_H_
#define SPI_H_

#define F_CPU 16000000
#include <util/delay.h>

#include "DIO.h"

void SPI_Master_Init(void);
void SPI_Slave_Init(void);

void SPI_Master_InitTrans(void);
void SPI_Master_TermTrans(void);

uint8 SPI_Master_Transiver(uint8 data);
uint8 SPI_Slave_Transiver(uint8 data);

#endif /* SPI_H_ */