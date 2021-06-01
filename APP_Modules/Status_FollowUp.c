/*
 * Status_FollowUp.c
 *
 * Created: 01/06/2021 02:03:50 AM
 *  Author: Mark Fayez
 */ 

#include "Status_FollowUp.h"

const LCD_Row_Text LCD_Row_Text_Options[] =
{
    'Control ECU',
    'Actuator ECU',
    'Control Bus',
    'BT Peer',
    'BT Peer Paired',
    'Invalid PUID',
    'Valid PUID',
    'Request Done!',
    'Send to BT Peer',
    'CMD Bus Peers',
    'Invalid Request!',
    'Starting...>>>...',
    'Invalid Peer',
    'Slave Ready',
    'Not Connected',
    'Paired',
    'Master Ready',
    'pending input',
    'Proceeding...',
    'Request Done!',
    'Invalid Device!',
    'Invalid Option!',
    'Peer Unavailable',
    'Not in Sync',
    'Invalid Response',
    'Requesting Reason',
    'Device Selected',
    'Op Selected',
    'Dev/Op Selected',
    'Response Sent',
    'Device - ',
    'READY!',
    'Already Running',
    'Valid Selection',
    'INVALID',
    'Device Op',
    'APPLIED!',
    'Control System',
    'Actuator System',
    'Starting...',
    'Ready.',
    'Selected',
    'Op Status:..',
    'Done!',
    'Selection ERROR!',
    'Request:...',
    ''
};

const uint8 BT_Text_Options[][] =
{
    'Request Done!',
    'Invalid Device Requested!',
    'Invalid Operation Requested!'
};

void Status_FollowUp_Init(void)
{
    LCD_Init();
}
void Status_Disp_LCD(uint8 R1_Text_Index, uint8 R2_Text_Index)
{
    LCD_Clear();
    LCD_WriteString(LCD_Row_Text_Options[R1_Text_Index]);
    LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
    LCD_WriteString(LCD_Row_Text_Options[R2_Text_Index]);
    _delay_ms(LCD_DISP_DELAY_MS);
}
void Status_Disp_LCD_IncludeInteger(uint8 R1_Text_Index,uint8 Integer_Number, uint8 R1_Text_Index)
{
    LCD_Clear();
	LCD_WriteString(LCD_Row_Text_Options[R1_Text_Index]);
	LCD_WriteInteger(Integer_Number);
	LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
	LCD_WriteString(LCD_Row_Text_Options[R2_Text_Index]);
	_delay_ms(LCD_DISP_DELAY_MS);
}
void Status_Send_BT(uint8 Text_Index)
{
    Bluetooth_Mod_Seq_Tx(BT_Text_Options[Text_Index]);
}
