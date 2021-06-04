/*
 * Devices.c
 *
 * Created: 29/05/2021 10:42:45 PM
 *  Author: Mark Fayez
 */ 

#include "Devices_LCFG.h"

#include "Devices.h"
#include "Status_FollowUp.h"

volatile DevicesDB Smart_Home_Devices;

void Devices_Init(void)
{
	Devices_DB_Config(&Smart_Home_Devices);

	uint8 device_counter = 0;
	for(device_counter = 0; device_counter < NUM_OF_DEVICES; device_counter++)
	{
		Smart_Home_Devices.Device[device_counter].Init();
		Smart_Home_Devices.Device[device_counter].OpFn[OP_1]();
		Smart_Home_Devices.Device[device_counter].Current_Operation = OP_1;
		
		Status_Disp_LCD_IncludeInteger(LCD_ROW_TXT_DEVICE_,(device_counter + 1),LCD_ROW_TXT_READY);
	}
}
uint8 Dev_Op_Check_Valid(uint8 Req_Device, uint8 Req_Operation)
{
	if(((Req_Device-DEV_CONST) >= 0) && ((Req_Device-DEV_CONST)<NUM_OF_DEVICES))
	{
		if (((Req_Operation-OPER_CONST) >= 0) && ((Req_Operation-OPER_CONST) < MAX_OPS_PER_DEV))
		{
			if((Req_Operation-OPER_CONST) == Smart_Home_Devices.Device[(Req_Device-DEV_CONST)].Current_Operation)
			{
				if((Req_Operation-OPER_CONST) == OP_3)
				{
					Status_Disp_LCD(LCD_ROW_TXT_VALID_SELECTION,LCD_ROW_TXT_PROCEEDING);

					return DEV_N_OP_VALID;
				}
				else
				{
					Status_Disp_LCD(LCD_ROW_TXT_OP_SELECTED,LCD_ROW_TXT_ALREADY_RUNNING);
				
					return OP_INVALID;
				}
			}
			else
			{
				Status_Disp_LCD(LCD_ROW_TXT_VALID_SELECTION,LCD_ROW_TXT_PROCEEDING);

				return DEV_N_OP_VALID;
			}

		}
		else
		{
			Status_Disp_LCD(LCD_ROW_TXT_OP_SELECTED,LCD_ROW_TXT_INVALID);

			return OP_INVALID;
		}
	}
	else
	{
		Status_Disp_LCD(LCD_ROW_TXT_DEVICE_SELECTED,LCD_ROW_TXT_INVALID);

		return DEV_INVALID;
	}
}
void Device_Apply_Request(uint8 Req_Device, uint8 Req_Operation)
{
	Smart_Home_Devices.Device[Req_Device-DEV_CONST].OpFn[Req_Operation-OPER_CONST]();
	Smart_Home_Devices.Device[Req_Device-DEV_CONST].Current_Operation = (Req_Operation-OPER_CONST);
	
	Status_Disp_LCD(LCD_ROW_TXT_DEVICE_OP,LCD_ROW_TXT_APPLIED);
}
 
