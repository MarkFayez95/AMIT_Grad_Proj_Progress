/*
 * Devices.h
 *
 * Created: 29/05/2021 10:43:15 PM
 *  Author: Mark Fayez
 */ 
#ifndef DEVICES_H_
#define DEVICES_H_

#include "LED.h"
#include "LCD.h"

#define NUM_OF_DEVICES      2

typedef struct 
{
    uint8 Device_Ref;
    uint8 Operation;
}DeviceEntry;



#endif /* DEVICES_H_ */