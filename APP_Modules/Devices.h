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
    uint8 Current_Operation;
    void (*OpFn[MAX_OPS_PER_DEV]) (void);
} DeviceEntry;

typedef struct 
{
    DeviceEntry Device[NUM_OF_DEVICES];
} DevicesDB;

typedef enum
{
	DEV_1,
	DEV_2,
	DEV_3,
	DEV_4,
	DEV_5,
	DEV_6,
	DEV_7,
	DEV_8,
} DEV_Codes;

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
} OP_Codes;

typedef enum
{
	DEV_N_OP_VALID=1,
	DEV_INVALID,
	OP_INVALID
} Dev_Ops_Check_Status;

void Devices_Init(void);
uint8 Dev_Op_Check_Valid(uint8* Command_Request);
void Device_Apply_Request(uint8 Req_Device, uint8 Req_Operation);

#endif /* DEVICES_H_ */