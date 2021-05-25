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

#define Baud_Rate_Hundred 96
#define UART_Presc	16
#define UART_Clk_Sor 160000


void UART_Init(void);
void UART_Tx(uint8 data);
uint8 UART_Rx(void);
void UART_TxString(uint8* str);

#endif /* UART_H_ */