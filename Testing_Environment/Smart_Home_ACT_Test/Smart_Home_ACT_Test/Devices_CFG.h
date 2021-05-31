/*
 * Devices_CFG.h
 *
 * Created: 30/05/2021 04:06:50 PM
 *  Author: Mark Fayez
 */ 

#ifndef DEVICES_CFG_H_
#define DEVICES_CFG_H_

#define LEDS_VOID_INPUT_FUNCTIONS	1

#include "LED.h"

#define NUM_OF_DEVICES      3
#define MAX_OPS_PER_DEV     3

#define Init_Fun_Index		0

#define DEV_CONST	0x07
#define OPER_CONST	0x07

typedef enum
{
	LED_0=DEV_CONST,
	LED_1,
	LED_2
} Device_Codes;

typedef enum
{
	LED_OFF_OP=OPER_CONST,
	LED_ON_OP,
	LED_TOGGLE_OP
} Operation_Codes;

typedef struct
{
	uint8 Device_Ref;
	void(*Init)(void);
	uint8 Current_Operation;
	void(*OpFn[MAX_OPS_PER_DEV])(void);
} DeviceEntry;

typedef struct
{
	DeviceEntry Device[NUM_OF_DEVICES];
} DevicesDB;

void Devices_DB_Config(void);


#endif /* DEVICES_CFG_H_ */

