/*
 * Status_FollowUp.h
 *
 * Created: 01/06/2021 02:03:32 AM
 *  Author: Mark Fayez
 */ 

#include "LCD.h"
#include "Bluetooth_Mod.h"

#define LCD_DISP_DELAY_MS    350
#define LCD_DISP_ROW_WIDTH   16

typedef uint8 LCD_Row_Text[LCD_DISP_ROW_WIDTH];

typedef enum {
    LCD_ROW_TXT_CONTROL_ECU,
    LCD_ROW_TXT_ACTUATOR_ECU,
    LCD_ROW_TXT_CONTROL_BUS,
    LCD_ROW_TXT_BT_PEER,
    LCD_ROW_TXT_BT_PEER_PAIRED,
    LCD_ROW_TXT_INVALID_PUID,
    LCD_ROW_TXT_VALID_PUID,
    LCD_ROW_TXT_REQUEST_DONE,
    LCD_ROW_TXT_SENT_TO_BT_PEER,
    LCD_ROW_TXT_CMD_BUS_PEERS,
    LCD_ROW_TXT_INVALID_REQUEST,
    LCD_ROW_TXT_STARTING,
    LCD_ROW_TXT_INVALID_PEER,
    LCD_ROW_TXT_SLAVE_READY,
    LCD_ROW_TXT_NOT_CONNECTED,
    LCD_ROW_TXT_PAIRED,
    LCD_ROW_TXT_MASTER_READY,
    LCD_ROW_TXT_PENDING_INPUT,
    LCD_ROW_TXT_PROCEEDING,
    LCD_ROW_TXT_INVALID_DEVICE,
    LCD_ROW_TXT_INVALID_OPTION,
    LCD_ROW_TXT_PEER_UNAVAILABLE,
    LCD_ROW_TXT_NOT_IN_SYNC,
    LCD_ROW_TXT_INVALID_RESPONSE,
    LCD_ROW_TXT_REQUESTING_REASON,
    LCD_ROW_TXT_DEVICE_SELECTED,
    LCD_ROW_TXT_OP_SELECTED,
    LCD_ROW_TXT_DEV_OP_SELECTED,
    LCD_ROW_TXT_RESPONSE_SENT,
    LCD_ROW_TXT_DEVICE_,
    LCD_ROW_TXT_READY,
    LCD_ROW_TXT_ALREADY_RUNNING,
    LCD_ROW_TXT_VALID_SELECTION,
    LCD_ROW_TXT_INVALID,
    LCD_ROW_TXT_DEVICE_OP,
    LCD_ROW_TXT_APPLIED,
    LCD_ROW_TXT_CONTROL_SYSTEM,
    LCD_ROW_TXT_ACTUATOR_SYSTEM,
    LCD_ROW_TXT_SELECTED,
    LCD_ROW_TXT_OP_STATUS,
    LCD_ROW_TXT_DONE,
    LCD_ROW_TXT_SELECTION_ERROR,
    LCD_ROW_TXT_REQUEST,
	LCD_ROW_TXT_CTRL_ACT_SYSTEM,
    LCD_ROW_TXT_NONE
} LCD_Row_Text_Index;

typedef enum {
    TXT_BT_REQUEST_DONE,
    TXT_BT_INVALID_DEVICE_REQUESTED,
    TXT_BT_INVALID_OPERATION_REQUESTED
} BT_Text_Index;

void Status_FollowUp_Init(void);
void Status_Disp_LCD(uint8 R1_Text_Index, uint8 R2_Text_Index);
void Status_Disp_LCD_IncludeInteger(uint8 R1_Text_Index,uint8 Integer_Number, uint8 R2_Text_Index);
void Status_Send_BT(uint8 Text_Index);