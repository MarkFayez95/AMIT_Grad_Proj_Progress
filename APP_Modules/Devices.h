/*
 * Devices.h
 *
 * Created: 29/05/2021 10:43:15 PM
 *  Author: Mark Fayez
 */ 
#ifndef DEVICES_H_
#define DEVICES_H_

#define LEDS_VOID_INPUT_FUNCTIONS	1

#include "LED.h"
#include "LCD.h"

#ifndef NUM_OF_DEVICES
    #define NUM_OF_DEVICES      2
#endif /* NUM_OF_DEVICES */

#ifndef MAX_OPS_PER_DEV
    #define MAX_OPS_PER_DEV     2
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
#endif /* MAX_OPS_PER_DEV */

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

static void Devices_DB_Config(DevicesDB* Devices_DB);
void Devices_Init(DevicesDB* Devices_DB);




#endif /* DEVICES_H_ */