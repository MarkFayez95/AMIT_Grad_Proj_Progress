/*
 * Bluetooth_Mod_CFG.h
 *
 * Created: 27/05/2021 08:40:45 PM
 *  Author: Mark Fayez
 */ 
#ifndef BLUETOOTH_MOD_CFG_H_
#define BLUETOOTH_MOD_CFG_H_

#include "DIO.h"

#define Baud_Rate_Hundred 384
#define UART_Presc	16
#define UART_Clk_Sor 160000

#define BT_STAT_PIN_PORT    DIO_PORTD
#define BT_STAT_PIN_PIN     DIO_PIN_7

#endif /* BLUETOOTH_MOD_CFG_H_ */