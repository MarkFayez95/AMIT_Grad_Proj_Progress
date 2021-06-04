/*
 * Devices_DTypes.h
 *
 * Created: 02/06/2021 10:04:15 PM
 *  Author: Mark Fayez
 */ 
#ifndef DEVICES_DTYPES_H_
#define DEVICES_DTYPES_H_

#include "Smart_Home_Sys_Config.h"
#include "STD_DTypes.h"

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

typedef void (*FunctionPointer)(void);

#endif /* DEVICES_DTYPES_H_ */