/*
 * Devices_LCFG.h
 *
 * Created: 02/06/2021 10:06:36 PM
 *  Author: Mark Fayez
 */ 
#ifndef DEVICES_LCFG_H_
#define DEVICES_LCFG_H_

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

#endif /* DEVICES_LCFG_H_ */