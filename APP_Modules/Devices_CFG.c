/*
 * Devices_CFG.c
 *
 * Created: 30/05/2021 04:07:35 PM
 *  Author: Mark Fayez
 */ 

#include "Devices_CFG.h"

static volatile DevicesDB Smart_Home_Devices;

void Devices_DB_Config(void)
{
    uint8 device_counter = 0;
    uint8 Operation_counter = 0;
    for(device_counter = 0; device_counter < NUM_OF_DEVICES; device_counter++)
    {
        for(Operation_counter = 0; Operation_counter < MAX_OPS_PER_DEV ; Operation_counter++)
        {
            Smart_Home_Devices.Device[device_counter].Device_Ref = (Device_Codes_Shifted_rightByte[0] << 4);
        }
    }
    
}
