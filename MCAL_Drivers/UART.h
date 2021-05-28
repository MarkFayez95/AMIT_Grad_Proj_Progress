/*
 * UART.h
 *
 * Created: 05/05/2021 5:08:40 PM
 *  Author: Mark Fayez
 */ 


#ifndef UART_H_
#define UART_H_

#include "MCU.h"
#include "Bit_math.h"
#include "DIO.h"

#define UART_PORT   DIO_PORTD
#define UART_TX_PIN DIO_PIN_0
#define UART_RX_PIN DIO_PIN_1

#ifndef Baud_Rate_Hundred
    #define Baud_Rate_Hundred 96
    #define UART_Presc	16
    #define UART_Clk_Sor 160000
#endif /* Baud_Rate_Hundred */

#define UART_Flag_Down	0

void UART_Init(void);
void UART_Tx(uint8 data);
uint8 UART_Rx(void);
void UART_RxString(uint8* str);
void UART_TxString(uint8* str);

#endif /* UART_H_ */