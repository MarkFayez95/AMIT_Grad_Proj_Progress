/*
 * Devices_CFG.c
 *
 * Created: 30/05/2021 04:07:35 PM
 *  Author: Mark Fayez
 */ 

#include "Devices_CFG.h"
#include "LED.h"

volatile DevicesDB Smart_Home_Devices;
volatile Device_Codes Dev_Cod = LED_0;

void (*Op_Fun_Ptr[NUM_OF_DEVICES][MAX_OPS_PER_DEV+1])(void) =
{
	{
		LED0_Init,
		LED0_OFF,
		LED0_ON,
		LED0_Toggle
	},
	{
		LED1_Init,
		LED1_OFF,
		LED1_ON,
		LED1_Toggle
	},
	{
		LED2_Init,
		LED2_OFF,
		LED2_ON,
		LED2_Toggle
	}
	
};

void Devices_DB_Config(void)
{
    uint8 device_counter = 0;
    uint8 Operation_counter = 0;
    for(device_counter = 0; device_counter < NUM_OF_DEVICES; device_counter++)
    {
		Dev_Cod = LED_0;
		Smart_Home_Devices.Device[device_counter].Device_Ref = (Dev_Cod+device_counter) << 4;
		Smart_Home_Devices.Device[device_counter].Init = Op_Fun_Ptr[device_counter][Init_Fun_Index];
        for(Operation_counter = 0; Operation_counter < MAX_OPS_PER_DEV ; Operation_counter++)
        {
            Smart_Home_Devices.Device[device_counter].OpFn[Operation_counter] =  Op_Fun_Ptr[device_counter][Operation_counter+1];
        }
    }
    
}
