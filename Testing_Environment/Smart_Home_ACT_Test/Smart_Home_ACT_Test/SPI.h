/*
 * SPI.h
 *
 * Created: 24/04/2021 11:54:55 AM
 *  Author: Mark Fayez
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "MCU.h"
#include "STD_DTypes.h"
#include "Bit_math.h"

#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#include <util/delay.h>

#include "DIO.h"

void SPI_Master_Init(void);
void SPI_Master_InitTrans(void);
void SPI_Master_TermTrans(void);
uint8 SPI_Transiver(uint8 data);
void SPI_Slave_Init(void);
#endif /* SPI_H_ */