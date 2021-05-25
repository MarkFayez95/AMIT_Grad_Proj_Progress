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

#define F_CPU 16000000
#include <util/delay.h>

#include "DIO.h"

#define SPI_MASTER  0xA0
#define SPI_SLAVE   0xB0

#define SPI_ROLE SPI_MASTER

#if SPI_ROLE == SPI_MASTER
    #define SPI_PORT     DIO_PORTB
    #define SPI_SS_PIN   DIO_PIN_4
    #define SPI_MOSI_PIN DIO_PIN_5
    #define SPI_MISO_PIN DIO_PIN_6
    #define SPI_CLK_PIN  DIO_PIN_7

    void SPI_Master_Init(void);
    void SPI_Master_InitTrans(void);
    void SPI_Master_TermTrans(void);
    uint8 SPI_Master_Transiver(uint8 data);
#elif SPI_ROLE == SPI_SLAVE
    #define SPI_PORT     DIO_PORTB
    #define SPI_SS_PIN   DIO_PIN_4
    #define SPI_MOSI_PIN DIO_PIN_5
    #define SPI_MISO_PIN DIO_PIN_6
    #define SPI_CLK_PIN  DIO_PIN_7

    void SPI_Slave_Init(void);
    uint8 SPI_Slave_Transiver(uint8 data);
#endif

#endif /* SPI_H_ */