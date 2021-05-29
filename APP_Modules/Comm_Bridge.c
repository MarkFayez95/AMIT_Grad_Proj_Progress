/*
 * Comm_Bridge.c
 *
 * Created: 29/05/2021 02:40:45 PM
 *  Author: Mark Fayez
 */ 

 #include "Comm_Bridge.h"
 
 void Comm_Bridge_Init(void)
 {
    #if ECU_ROLE == CONTROL_ECU
        CMD_Bus_Master_Init();
        if(CMD_Bus_HandShake() == INVALID_PEER)
        {
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Invalid Peer');
            while(CMD_Bus_HandShake() == INVALID_PEER);
        }
        else{}

        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Slave Ready');
        
        Bluetooth_Mod_Init();
        if(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
        {
            LCD_WriteString('BT Peer');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Not Connected');
            while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
        }
        else{}

        LCD_WriteString('BT Peer');
        LCD_GoToLocation(LCD_ROW_2,4*LCD_SHIFT_CURSOR);
        LCD_WriteString('Paired');
    #elif ECU_ROLE == ACTUATOR_ECU
        CMD_Bus_Slave_Init();
        if(CMD_Bus_HandShake() == INVALID_PEER)
        {
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Invalid Peer');
            while(CMD_Bus_HandShake() == INVALID_PEER);
        }
        else{}

        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Master Ready');
    #endif /* ECU_ROLE */
 }

void Comm_Bridge_BT_Read(uint8* Command)
{
    uint8 Check_Valid_PUID = 0;
    if(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
    {
        LCD_WriteString('BT Peer');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Not Connected');
        while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
    }
    else{}

    do 
    {
        LCD_WriteString('BT Peer Paired');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Pending Input');

        Bluetooth_Mod_Seq_Rx(Command);
        #if PUID_DB == CREATED
            Check_Valid_PUID = PUID_DB_Search(Command[0]);
        #else
            if(Command[0] == VALID_PUID)
            {
                Check_Valid_PUID = VALID_ID;
            }
            else
            {
                Check_Valid_PUID = INVALID_ID;
                LCD_Clear();
                LCD_WriteString('Invalid PUID');
            }
        #endif /* PUID_DB */
    } while(Check_Valid_PUID = INVALID_ID);

    // Shift the received frame to delete the PUID from it.
    Command[0] = Command[1];
    Command[1] = Command[2];
    
    LCD_Clear();
    LCD_WriteString('Valid PUID');
    LCD_GoToLocation(LCD_ROW_2,4*LCD_SHIFT_CURSOR);
    LCD_WriteString('Proceeding...');
}
void Comm_Bridge_BT_Respond(uint8* Response)
{

}

void Comm_Bridge_CMD_Req(uint8* Request_Command)
{

}
void Comm_Bridge_CMD_Read_Req(uint8* Request_Command)
{

}
void Comm_Bridge_CMD_Res(uint8* Ack_Response)
{

}