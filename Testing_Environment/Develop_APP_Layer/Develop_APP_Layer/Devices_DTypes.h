/*
 * Devices_DTypes.h
 *
 * Created: 29/05/2021 10:44:15 PM
 *  Author: Mark Fayez
 */ 


#ifndef DEVICES_DTYPES_H_
#define DEVICES_DTYPES_H_



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
	RESERVED_0,
	DEV_N_OP_VALID,
	RESERVED_1,
	DEV_INVALID,
	OP_INVALID
} Dev_Ops_Check_Status;

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


#endif /* DEVICES_DTYPES_H_ */