/*
 * Smart_Home.c
 *
 * Created: 30/05/2021 04:08:35 PM
 *  Author: Mark Fayez
 */

#include "Smart_Home.h"

uint8 User_Selection[COMMAND_BYTE_LENGTH+1];


#if ECU_ROLE == ACTUATOR_ECU
	extern volatile DevicesDB Smart_Home_Devices;
	uint8 Selected_Device = DEV_1;
	uint8 Selected_Operation = OP_1;
#endif /* ECU_ROLE */


void Smart_Home_Init(void)
{
	LCD_Init();
	
	#if ECU_ROLE == CONTROL_ECU
		
		LCD_Clear();
		LCD_WriteString('Control System');
		LCD_GoToLocation(LCD_ROW_2,5*LCD_SHIFT_CURSOR);
		LCD_WriteString('Starting...');
		_delay_ms(20);
		
		Comm_Bridge_Init();
		
		_delay_ms(20);
		LCD_Clear();
		LCD_WriteString('Control System');
		LCD_GoToLocation(LCD_ROW_2,5*LCD_SHIFT_CURSOR);
		LCD_WriteString('Ready.');
		_delay_ms(20);
		
	#elif ECU_ROLE == ACTUATOR_ECU
		
		LCD_Clear();
		LCD_GoToLocation(LCD_ROW_1,3*LCD_SHIFT_CURSOR);
		LCD_WriteString('Actuator System');
		LCD_GoToLocation(LCD_ROW_2,5*LCD_SHIFT_CURSOR);
		LCD_WriteString('Starting...');
		_delay_ms(10);
		
		Devices_DB_Config(&Smart_Home_Devices);
		
		Devices_Init();
		
		Comm_Bridge_Init();
		
		_delay_ms(20);
		LCD_Clear();
		LCD_WriteString('Actuator System');
		LCD_GoToLocation(LCD_ROW_2,5*LCD_SHIFT_CURSOR);
		LCD_WriteString('Ready.');
		_delay_ms(20);
		
	#endif /* ECU_ROLE */
}
void Smart_Home_Run(void)
{
	#if ECU_ROLE == CONTROL_ECU
		Smart_Home_User_Selection();
		Smart_Home_Process_N_Respond();
	#elif ECU_ROLE == ACTUATOR_ECU
		Smart_Home_Read_N_Decode();
		Smart_Home_Process_N_Respond();
	#endif /* ECU_ROLE */
}

#if ECU_ROLE == CONTROL_ECU
static void Smart_Home_User_Selection(void)
{
	Comm_Bridge_BT_Read(User_Selection);
	
	_delay_ms(20);
	LCD_Clear();
	LCD_WriteString('Dev and Op');
	LCD_GoToLocation(LCD_ROW_2,4*LCD_SHIFT_CURSOR);
	LCD_WriteString('Selected');
	_delay_ms(20);
}
static void Smart_Home_Process_N_Respond(void)
{
	uint8 Selection_Validity = SEND_FAILED;
	
	Selection_Validity = Comm_Bridge_CMD_Req(User_Selection);
	
	if(Selection_Validity == REQ_DONE)
	{
		LCD_Clear();
		LCD_WriteString('Op Status:..');
		LCD_GoToLocation(LCD_ROW_2,5*LCD_SHIFT_CURSOR);
		LCD_WriteString('Done!');
		_delay_ms(100);
	}
	else if(Selection_Validity == INV_DEV_SEL)
	{
		LCD_Clear();
		LCD_WriteString('Selection ERROR!');
		LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
		LCD_WriteString('Invalid Device!');
		_delay_ms(100);
	}
	else
	{
		LCD_Clear();
		LCD_WriteString('Selection ERROR!');
		LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
		LCD_WriteString('Invalid Option!');
		_delay_ms(100);
	}
	
	Comm_Bridge_BT_Send(Selection_Validity);
}
#elif ECU_ROLE == ACTUATOR_ECU
static void Smart_Home_Read_N_Decode(void)
{
	Comm_Bridge_CMD_Read_Req(User_Selection);
	#if COMMAND_BYTE_LENGTH == 1
		Selected_Device = User_Selection[CMD_DATA_BYTE] >> REQ_DEV_SHIFT_MASK;
		Selected_Operation = (User_Selection[CMD_DATA_BYTE] & REQ_OP_MASK);
	#elif COMMAND_BYTE_LENGTH == 2
		Selected_Device = User_Selection[CMD_DATA_BYTE_1];
		Selected_Operation = User_Selection[CMD_DATA_BYTE_2];
	#endif /* COMMAND_BYTE_LENGTH */
}
static void Smart_Home_Process_N_Respond(void)
{
	uint8 Selection_Validity = SEND_FAILED;
	Selection_Validity = Dev_Op_Check_Valid(Selected_Device, Selected_Operation);
	if(Selection_Validity == DEV_N_OP_VALID)
	{
		Device_Apply_Request(Selected_Device,Selected_Operation);
		
		LCD_Clear();
		LCD_WriteString('Request:...');
		LCD_GoToLocation(LCD_ROW_2,5*LCD_SHIFT_CURSOR);
		LCD_WriteString('Done!');
		_delay_ms(100);
	}
	Selection_Validity += NACK_RES;
	Comm_Bridge_CMD_Res(&Selection_Validity);
}
#endif /* ECU_ROLE */ 
