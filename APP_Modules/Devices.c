/*
 * Devices.c
 *
 * Created: 29/05/2021 10:42:45 PM
 *  Author: Mark Fayez
 */ 

#include "Devices.h"

extern static volatile DevicesDB Smart_Home_Devices;

void Devices_Init(void)
{
	Devices_DB_Config();
	
	uint8 device_counter = 0;
	uint8 Operation_counter = 0;
	for(device_counter = 0; device_counter < NUM_OF_DEVICES; device_counter++)
	{
		Smart_Home_Devices.Device[device_counter].*Init();
		Smart_Home_Devices.Device[device_counter].*OpFn[OP_1]();
		Smart_Home_Devices.Device[device_counter].Current_Operation = OP_1;
	}
}
uint8 Dev_Op_Check_Valid(uint8 Req_Device, uint8 Req_Operation)
{
	if(((Req_Device-DEV_CONST) >= 0) && ((Req_Device-DEV_CONST)<NUM_OF_DEVICES))
	{
		if (((Req_Operation-OPER_CONST) >= 0) && ((Req_Operation-OPER_CONST) < MAX_OPS_PER_DEV))
		{
			if((Req_Operation-OPER_CONST) == Smart_Home_Devices.Device[(Req_Device-DEV_CONST)]->Current_Operation)
			{
				return OP_INVALID;
			}
			else
			{
				return DEV_N_OP_VALID
			}
		}
		else
		{
			return OP_INVALID;
		}
	}
	else
	{
		DEV_INVALID;
	}
}
void Device_Apply_Request(uint8 Req_Device, uint8 Req_Operation)
{
	Smart_Home_Devices.Device[(Req_Device-DEV_CONST)].*OpFn[(Req_Operation-OPER_CONST)]();
}
 
