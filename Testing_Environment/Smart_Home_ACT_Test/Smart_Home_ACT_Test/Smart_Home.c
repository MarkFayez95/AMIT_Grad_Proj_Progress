/*
 * Smart_Home.c
 *
 * Created: 30/05/2021 04:08:35 PM
 *  Author: Mark Fayez
 */

#include "Smart_Home_Sys_Config.h"

#include "Smart_Home.h"
#include "Status_FollowUp.h"

// User selection array is of command byte length adding to it one Pin User Identifier byte for authentication with the BT user and one more byte for the response of the Actuator ECU to be recorded in it.
uint8 User_Selection[COMMAND_BYTE_LENGTH+2];

uint8 Smart_Home_Sys_Sync_Flag = IN_SYNC;

#if ECU_ROLE == ACTUATOR_ECU
	uint8 Selected_Device = DEV_1;
	uint8 Selected_Operation = OP_1;
#endif /* ECU_ROLE */


void Smart_Home_Init(void)
{
	Status_FollowUp_Init();
	
	#if ECU_ROLE == CONTROL_ECU
		
		Status_Disp_LCD(LCD_ROW_TXT_CONTROL_SYSTEM,LCD_ROW_TXT_STARTING);
		
		Comm_Bridge_Init();

		Status_Disp_LCD(LCD_ROW_TXT_CONTROL_SYSTEM,LCD_ROW_TXT_READY);
		
	#elif ECU_ROLE == ACTUATOR_ECU
		
		
		Status_Disp_LCD(LCD_ROW_TXT_ACTUATOR_SYSTEM,LCD_ROW_TXT_STARTING);
		
		Devices_Init();
		
		Comm_Bridge_Init();
		
		Status_Disp_LCD(LCD_ROW_TXT_ACTUATOR_SYSTEM,LCD_ROW_TXT_READY);
		
	#endif /* ECU_ROLE */
}
void Smart_Home_Run(void)
{
	if(Smart_Home_Sys_Sync_Flag == OUT_OF_SYNC)
	{
		// Force sync on CMD_Bus by NUM_OF_RESYNC_HANDSHAKES consecutive successfull handshakes.
		Comm_Bridge_CMD_Bus_Re_Sync();
	}	
	#if ECU_ROLE == CONTROL_ECU
		Smart_Home_User_Selection();
		if(Smart_Home_Sys_Sync_Flag == IN_SYNC)
		{
			Smart_Home_Process_N_Respond();
		}
	#elif ECU_ROLE == ACTUATOR_ECU
		Smart_Home_Read_N_Decode();
		if(Smart_Home_Sys_Sync_Flag == IN_SYNC)
		{
			Smart_Home_Process_N_Respond();
		}
	#endif /* ECU_ROLE */
}


static void Smart_Home_User_Selection(void)
{
	#if ECU_ROLE == CONTROL_ECU
		Comm_Bridge_BT_Read(User_Selection);

		Status_Disp_LCD(LCD_ROW_TXT_DEV_OP_SELECTED,LCD_ROW_TXT_NONE);
	#endif /* ECU_ROLE */
}
static void Smart_Home_Read_N_Decode(void)
{
	#if ECU_ROLE == ACTUATOR_ECU
		Status_Disp_LCD(LCD_ROW_TXT_ACTUATOR_SYSTEM,LCD_ROW_TXT_PENDING_INPUT);
		if(Comm_Bridge_CMD_Read_Req(User_Selection) == OUT_OF_SYNC)
		{
			Status_Disp_LCD(LCD_ROW_TXT_CTRL_ACT_SYSTEM,LCD_ROW_TXT_NOT_IN_SYNC);
			Smart_Home_Sys_Sync_Flag = OUT_OF_SYNC;
		}
		else
		{
			#if COMMAND_BYTE_LENGTH == 1
				Selected_Device = User_Selection[CMD_DATA_BYTE] >> REQ_DEV_SHIFT_MASK; // shift the command byte 4 times to the right to get the 4 MSbs which represent the Device Identifier.
				Selected_Operation = (User_Selection[CMD_DATA_BYTE] & REQ_OP_MASK); // Mask the 4 LSbs from the command byte to get the Operation identifier.
			#elif COMMAND_BYTE_LENGTH == 2
				Selected_Device = User_Selection[CMD_DATA_BYTE]; // the first byte represent the device identifier.
				Selected_Operation = User_Selection[CMD_DATA_BYTE_2]; // the second byte represent the operation identifier.
			#endif /* COMMAND_BYTE_LENGTH */
		}
	#endif /* ECU_ROLE */
}
#if ECU_ROLE == CONTROL_ECU
static void Smart_Home_Process_N_Respond(void)
{
	uint8 Selection_Validity = SEND_FAILED;

	Comm_Bridge_CMD_Req(User_Selection);

	Selection_Validity = User_Selection[RESPONSE_DATA_BYTE];
	
	if(Selection_Validity == REQ_DONE)
	{
		Status_Disp_LCD(LCD_ROW_TXT_OP_STATUS,LCD_ROW_TXT_DONE);
		Comm_Bridge_BT_Send(Selection_Validity);
	}
	else if(Selection_Validity == INV_DEV_SEL)
	{
		Status_Disp_LCD(LCD_ROW_TXT_SELECTION_ERROR,LCD_ROW_TXT_INVALID_DEVICE);
		Comm_Bridge_BT_Send(Selection_Validity);
	}
	else if(Selection_Validity == INV_OP_SEL)
	{
		Status_Disp_LCD(LCD_ROW_TXT_SELECTION_ERROR,LCD_ROW_TXT_INVALID_OPTION);
		Comm_Bridge_BT_Send(Selection_Validity);
	}
	else
	{
		Status_Disp_LCD(LCD_ROW_TXT_CTRL_ACT_SYSTEM,LCD_ROW_TXT_NOT_IN_SYNC);
		Smart_Home_Sys_Sync_Flag = OUT_OF_SYNC;
	}
}
#elif ECU_ROLE == ACTUATOR_ECU
static void Smart_Home_Process_N_Respond(void)
{
	uint8 Selection_Validity = SEND_FAILED;
	Selection_Validity = Dev_Op_Check_Valid(Selected_Device, Selected_Operation);
	if(Selection_Validity == DEV_N_OP_VALID)
	{
		Device_Apply_Request(Selected_Device,Selected_Operation);
		
		Status_Disp_LCD(LCD_ROW_TXT_REQUEST,LCD_ROW_TXT_DONE);
	}
	Comm_Bridge_CMD_Res(&Selection_Validity);
	if(Selection_Validity == OUT_OF_SYNC)
	{
		Smart_Home_Sys_Sync_Flag = OUT_OF_SYNC;
	}
}
#endif /* ECU_ROLE */ 

