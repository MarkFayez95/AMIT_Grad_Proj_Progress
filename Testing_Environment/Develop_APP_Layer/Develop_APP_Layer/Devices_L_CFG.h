/*
 * Devices_L_CFG.h
 *
 * Created: 30/05/2021 04:06:50 PM
 *  Author: Mark Fayez
 */ 

#ifndef DEVICES_L_CFG_H_
#define DEVICES_L_CFG_H_

#define LEDS_VOID_INPUT_FUNCTIONS	1

#include "LED.h"

#include "Devices_CFG.h"
#include "Devices_DTypes.h"

typedef enum
{
	LED_0,
	LED_1,
	LED_2
} Device_Codes;

typedef enum
{
	LED_OFF_OP,
	LED_ON_OP,
	LED_TOGGLE_OP
} Operation_Codes;

void Devices_DB_Config(DevicesDB* Smart_Home_DevDB);

#endif /* DEVICES_L_CFG_H_ */

