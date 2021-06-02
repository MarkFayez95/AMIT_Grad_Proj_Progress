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

typedef enum {
    SPI_MASTER=0xA0,
    SPI_SLAVE
} SPI_Roles;

#define TRANS_FAILED    0
#define MASTER_SS_SET_DELAY_MS    30

#ifndef SPI_ROLE
    #define SPI_ROLE    SPI_MASTER
#endif

#if SPI_ROLE == SPI_MASTER
    #define SPI_PORT     DIO_PORTB
    #define SPI_SS_PIN   DIO_PIN_4
    #define SPI_MOSI_PIN DIO_PIN_5
    #define SPI_MISO_PIN DIO_PIN_6
    #define SPI_CLK_PIN  DIO_PIN_7

#elif SPI_ROLE == SPI_SLAVE

    #define SPI_PORT     DIO_PORTB
    #define SPI_SS_PIN   DIO_PIN_4
    #define SPI_MOSI_PIN DIO_PIN_5
    #define SPI_MISO_PIN DIO_PIN_6
    #define SPI_CLK_PIN  DIO_PIN_7

#endif

void SPI_Master_Init(void);
void SPI_Master_InitTrans(void);
void SPI_Master_TermTrans(void);
uint8 SPI_Transiver(uint8 data);
void SPI_Slave_Init(void);
#endif /* SPI_H_ */