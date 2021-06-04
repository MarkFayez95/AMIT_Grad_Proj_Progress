/*
 * Bluetooth_Mod.h
 *
 * Created: 27/05/2021 08:40:15 PM
 *  Author: Mark Fayez
 */ 
#ifndef BLUETOOTH_MOD_H_
#define BLUETOOTH_MOD_H_

#include "UART.h"
#include "DIO.h"

#define BT_STAT_PIN_PORT    DIO_PORTD
#define BT_STAT_PIN_PIN     DIO_PIN_7

void Bluetooth_Mod_Init(void);
uint8 Bluetooth_Mod_Ch_Pair(void);
void Bluetooth_Mod_Tx(uint8 Data_Byte);
uint8 Bluetooth_Mod_Rx(void);
void Bluetooth_Mod_Seq_Tx(uint8* Data_Stream);
void Bluetooth_Mod_Seq_Rx(uint8* Data_Stream);


#endif /* BLUETOOTH_MOD_H_ */