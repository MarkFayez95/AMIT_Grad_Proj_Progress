/*
 * Status_FollowUp.c
 * APP Layer application responsible for displaying the current status of the system on each ECU.
 * 
 * Created: 01/06/2021 02:03:50 AM
 *  Author: Mark Fayez
 */ 

#include "Smart_Home_Sys_Config.h"
#include "Status_FollowUp.h"

LCD_Row_Text LCD_Row_Text_Options[LCD_ROW_TXT_NONE+1] =
{
    "Control ECU",
    "Actuator ECU",
    "Control Bus",
    "BT Peer",
    "BT Peer Paired",
    "Invalid PUID",
    "Valid PUID",
    "Request Done!",
    "Send to BT Peer",
    "CMD Bus Peers",
    "Invalid Request!",
    "Starting...>>>...",
    "Invalid Peer",
    "Slave Ready",
    "Not Connected",
    "Paired",
    "Master Ready",
    "pending input",
    "Proceeding...",
    "Invalid Device!",
    "Invalid Option!",
    "Peer Unavailable",
    "Not in Sync",
    "Invalid Response",
    "Requesting Reason",
    "Device Selected",
    "Op Selected",
    "Dev/Op Selected",
    "Response Sent",
    "Device : ",
    "READY!",
    "Already Running",
    "Valid Selection",
    "INVALID",
    "Device Op",
    "APPLIED!",
    "Control System",
    "Actuator System",
    "Selected",
    "Op Status:..",
    "Done!",
    "Selection ERROR!",
    "Request:...",
	"CTRL ACT System",
    "Send B1 Failed",
    "Send B2 Failed",
    "Send Cmd Failed",
    '\0'
};

// Initialize the LCD
void Status_FollowUp_Init(void)
{
    LCD_Init();
}

// Display a 2 row status on LCD
// Inputs are 2 codes for the corresponding row text in the application database.
void Status_Disp_LCD(uint8 R1_Text_Index, uint8 R2_Text_Index)
{
    LCD_Clear();
    LCD_WriteString(LCD_Row_Text_Options[R1_Text_Index]);
    LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
    LCD_WriteString(LCD_Row_Text_Options[R2_Text_Index]);
    _delay_ms(LCD_DISP_DELAY_MS);
}

// Display a 2 row status on LCD that includes integer value in the first row.
// Inputs are 2 codes for the corresponding row string of text defined in the application database.
// as well as the integer value required to be displayed.
void Status_Disp_LCD_IncludeInteger(uint8 R1_Text_Index,uint8 Integer_Number, uint8 R2_Text_Index)
{
    LCD_Clear();
	LCD_WriteString(LCD_Row_Text_Options[R1_Text_Index]);
	LCD_WriteInteger(Integer_Number);
	LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
	LCD_WriteString(LCD_Row_Text_Options[R2_Text_Index]);
	_delay_ms(LCD_DISP_DELAY_MS);
}
