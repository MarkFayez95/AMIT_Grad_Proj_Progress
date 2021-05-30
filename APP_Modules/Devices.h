/*
 * Devices.h
 *
 * Created: 29/05/2021 10:43:15 PM
 *  Author: Mark Fayez
 */ 
#ifndef DEVICES_H_
#define DEVICES_H_

#include "LCD.h"
#include "Devices_CFG.h"

typedef struct 
{
    uint8 Device_Ref;
    void *Init(void);
    uint8 Operation;
    void (*OpFn[MAX_OPS_PER_DEV]) (void);
} DeviceEntry;

typedef struct 
{
    DeviceEntry Device[NUM_OF_DEVICES];
} DevicesDB;

typedef enum 
{
    OP_1,
    OP_2,
    OP_3,
    OP_4,
    OP_5,
    OP_6,
    OP_7,
    OP_8,
    OP_9,
    OP_10,
    OP_11,
    OP_12,
    OP_13,
    OP_14,
    OP_14,
    OP_15,
    OP_16
} OP_Index;

void Devices_Init(void);





#endif /* DEVICES_H_ */