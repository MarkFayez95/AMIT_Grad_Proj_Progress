/*
 * Devices_LCFG.C
 *
 * Created: 02/06/2021 10:06:20 PM
 *  Author: Mark Fayez
 */ 

#include "Devices_LCFG.h"

#include "LED.h"

// array of function pointers for all the devices operations functions
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

// function to configure the Device manager's database of devices 
void Devices_DB_Config(DevicesDB* Smart_Home_DevDB)
{
	Device_Codes Dev_Cod = LED_0;
	
	uint8 device_counter = 0;
	uint8 Operation_counter = 0;
	
	for(device_counter = 0; device_counter < NUM_OF_DEVICES; device_counter++)
	{
		// Set the device name/reference code which can be used to further adjust the codes that are sent through the wireless connection for security reasons
		Smart_Home_DevDB->Device[device_counter].Device_Ref = (Dev_Cod + device_counter + DEV_CONST) << 4;
		
		// Set the Devices Initialization function pointer to each corresponding device in the array.
		Smart_Home_DevDB->Device[device_counter].Init = Op_Fun_Ptr[device_counter][INIT_FUN_INDEX];
		
		// Loop to set the Devices operations function pointer to its corresponding index in the array of Device operations for each device in the devices database.
		for(Operation_counter = 0; Operation_counter < MAX_OPS_PER_DEV ; Operation_counter++)
		{
			Smart_Home_DevDB->Device[device_counter].OpFn[Operation_counter] =  Op_Fun_Ptr[device_counter][Operation_counter + 1]; // 1 is added to the counter to skip the init function in the Op_Fun_Ptr array of pointers to functions
		}
		
		// Increment the Dev_Code variable to next device in the database.
		Dev_Cod++;
	}
}