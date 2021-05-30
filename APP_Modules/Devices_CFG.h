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

typedef enum
{
    LED_0 = 0x0A,
    LED_1,
    LED_2
} Device_Codes_Shifted_rightByte;

void Devices_DB_Config(void);


#endif /* DEVICES_CFG_H_ */

