/*
 * Devices_LCFG.C
 *
 * Created: 02/06/2021 10:06:20 PM
 *  Author: Mark Fayez
 */ 

#include "Devices_LCFG.h"

#include "LED.h"

FunctionPointer Op_Fun_Ptr[NUM_OF_DEVICES][MAX_OPS_PER_DEV+1] =
{
    LED0_Init,
    LED0_OFF,
    LED0_ON,
    LED0_Toggle,
    
    LED1_Init,
    LED1_OFF,
    LED1_ON,
    LED1_Toggle,
    
    LED2_Init,
    LED2_OFF,
    LED2_ON,
    LED2_Toggle
};

void Devices_DB_Config(DevicesDB* Smart_Home_DevDB)
{
	Device_Codes Dev_Cod = LED_0;
	
	uint8 device_counter = 0;
	uint8 Operation_counter = 0;
	
	for(device_counter = 0; device_counter < NUM_OF_DEVICES; device_counter++)
	{
		Dev_Cod = LED_0;
		Smart_Home_DevDB->Device[device_counter].Device_Ref = (Dev_Cod+device_counter+DEV_CONST) << 4;
		Smart_Home_DevDB->Device[device_counter].Init = Op_Fun_Ptr[device_counter][INIT_FUN_INDEX];
		for(Operation_counter = 0; Operation_counter < MAX_OPS_PER_DEV ; Operation_counter++)
		{
			Smart_Home_DevDB->Device[device_counter].OpFn[Operation_counter] =  Op_Fun_Ptr[device_counter][Operation_counter+1];
		}
	}
}