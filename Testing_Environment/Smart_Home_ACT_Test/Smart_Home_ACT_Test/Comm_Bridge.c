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
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Invalid Peer');
            _delay_ms(20);

            while(CMD_Bus_HandShake() == INVALID_PEER);
        }
        else{}

        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Slave Ready');
        _delay_ms(20);
        
        Bluetooth_Mod_Init();
        if(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
        {
            LCD_Clear();
            LCD_WriteString('BT Peer');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Not Connected');
            _delay_ms(20);

            while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
        }
        else{}

        LCD_Clear();
        LCD_WriteString('BT Peer');
        LCD_GoToLocation(LCD_ROW_2,4*LCD_SHIFT_CURSOR);
        LCD_WriteString('Paired');
        _delay_ms(20);

    #elif ECU_ROLE == ACTUATOR_ECU
        CMD_Bus_Slave_Init();
        if(CMD_Bus_HandShake() == INVALID_PEER)
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Invalid Peer');
            _delay_ms(20);

            while(CMD_Bus_HandShake() == INVALID_PEER);
        }
        else{}

        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Master Ready');
        _delay_ms(20);
    #endif /* ECU_ROLE */
 }

void Comm_Bridge_BT_Read(uint8* Command)
{
    uint8 Check_Valid_PUID = 0;
    if(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
    {
        LCD_Clear();
        LCD_WriteString('BT Peer');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Not Connected');
        _delay_ms(20);

        while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
    }
    else{}

    do 
    {
        LCD_Clear();
        LCD_WriteString('BT Peer Paired');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Pending Input');
        _delay_ms(20);

        Bluetooth_Mod_Seq_Rx(&Command);
        #ifdef PUID_DB_H_
            Check_Valid_PUID = PUID_DB_Search(Command[BT_PUID_BYTE]);
        #else
            if(Command[BT_PUID_BYTE] == VALID_PUID)
            {
                Check_Valid_PUID = VALID_ID;
            }
            else
            {
                Check_Valid_PUID = INVALID_ID;
                LCD_Clear();
                LCD_WriteString('Invalid PUID');
                _delay_ms(20);
            }
        #endif /* PUID_DB */
    } while(Check_Valid_PUID = INVALID_ID);

    // Shift the received frame to delete the PUID from it.
    Command[BT_PUID_BYTE] = Command[BT_DATA_BYTE];
#if COMMAND_BYTE_LENGTH == 2
	Command[BT_DATA_BYTE] = Command[BT_DATA_BYTE_2];
#endif /* COMMAND_BYTE_LENGTH */
    
    LCD_Clear();
    LCD_WriteString('Valid PUID');
    LCD_GoToLocation(LCD_ROW_2,4*LCD_SHIFT_CURSOR);
    LCD_WriteString('Proceeding...');
    _delay_ms(20);
}
void Comm_Bridge_BT_Send(uint8 Response)
{
    Bluetooth_Mod_Tx(Response);
    if(Response == REQ_DONE)
    {
        Bluetooth_Mod_Seq_Tx('Request Done!');
        
        LCD_Clear();
        LCD_WriteString('Send to BT Peer');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Request Done!');
        _delay_ms(10);
    }
    else if(Response == INV_DEV_SEL)
    {
        Bluetooth_Mod_Seq_Tx('Invalid Device Requested!');
        
        LCD_Clear();
        LCD_WriteString('Send to BT Peer');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Invalid Device!');
        _delay_ms(10);
    }
    else
    {
        Bluetooth_Mod_Seq_Tx('Invalid Operation Requested!');
        
        LCD_Clear();
        LCD_WriteString('Send to BT Peer');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Invalid Option!');
        _delay_ms(10);
    }
}
void Comm_Bridge_BT_SendStream(uint8* data_stream)
{
    Bluetooth_Mod_Tx(ECU_PUID);
    Bluetooth_Mod_Seq_Tx(data_stream);
}

uint8 Comm_Bridge_CMD_Req(uint8* Request_Command)
{
    uint8 ECUs_Comm_State = REQ_DROPPED;
    uint8 Ack_Validity = INVALID_ACK_RESPONSE;
    uint8 Ack_Response = INVALID_ACK_RESPONSE;
    ECUs_Comm_State = CMD_Bus_Write(Request_Command[0]);
    while(ECUs_Comm_State == PEER_UNAVAILABLE)
    {
        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Peer Unavailable');

        ECUs_Comm_State = CMD_Bus_Write(Request_Command[0]);
        _delay_ms(10);
    }
#if COMMAND_BYTE_LENGTH == 2
    if(ECUs_Comm_State == READING)
    {
        ECUs_Comm_State = CMD_Bus_Write(Request_Command[1]);
        while(ECUs_Comm_State == PEER_UNAVAILABLE)
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Peer Unavailable');

            ECUs_Comm_State = CMD_Bus_Write(Request_Command[1]);
            _delay_ms(10);
        }
        if(ECUs_Comm_State != READING)
        {
            LCD_Clear();
            LCD_WriteString('CMD Bus Peers');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Not in Sync');
            _delay_ms(10);
            return SEND_FAILED;
        }
    }
    else 
    {
        LCD_Clear();
        LCD_WriteString('CMD Bus Peers');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Not in Sync');
        _delay_ms(10);
        return SEND_FAILED;
    }
#elif COMMAND_BYTE_LENGTH == 1
    if(ECUs_Comm_State != READING)
    {
        LCD_Clear();
        LCD_WriteString('CMD Bus Peers');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Not in Sync');
        _delay_ms(10);
        return SEND_FAILED;
    }            
#endif

    Ack_Validity = CMD_Bus_Req_Ack(&Ack_Response);
    while((Ack_Validity == PEER_UNAVAILABLE) || (Ack_Validity == INVALID_ACK_RESPONSE))
    {
        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        if(Ack_Validity == PEER_UNAVAILABLE)
        {
            LCD_WriteString('Peer Unavailable');
        }
        else if (Ack_Validity == INVALID_ACK_RESPONSE)
        {
            LCD_WriteString('Invalid Response');
        }
        
        _delay_ms(10);
        Ack_Validity = CMD_Bus_Req_Ack(&Ack_Response);
    }
    if(Ack_Response == ACK_RES)
    {
        LCD_Clear();
        LCD_WriteString('Request Done!');
        return REQ_DONE;
    }
    else if(Ack_Response == NACK_RES)
    {
        LCD_Clear();
        LCD_WriteString('Invalid Request!');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Requesting Reason');
        Ack_Response = CMD_Bus_Write(NACK_REASON_REQ);
        while(Ack_Response == PEER_UNAVAILABLE)
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Peer Unavailable');

            Ack_Response = CMD_Bus_Write(NACK_REASON_REQ);
            _delay_ms(10);
        }
        return Ack_Response;
    }
}
void Comm_Bridge_CMD_Read_Req(uint8* Request_Command)
{
    uint8 ECUs_Comm_State = REQ_DROPPED;
    ECUs_Comm_State = CMD_Bus_Read(Request_Command);
    while(ECUs_Comm_State == PEER_UNAVAILABLE)
    {
        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Peer Unavailable');

        ECUs_Comm_State = CMD_Bus_Read(Request_Command);
        _delay_ms(10);
    }
#if COMMAND_BYTE_LENGTH == 2
    if(ECUs_Comm_State == RECEIVED)
    {
        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Device Selected');
        _delay_ms(10);
        ECUs_Comm_State = CMD_Bus_Read(Request_Command+1);
        while(ECUs_Comm_State == PEER_UNAVAILABLE)
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Peer Unavailable');

            ECUs_Comm_State = CMD_Bus_Read(Request_Command+1);
            _delay_ms(10);
        }
        if(ECUs_Comm_State == RECEIVED)
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,3*LCD_SHIFT_CURSOR);
            LCD_WriteString('Op Selected');
            _delay_ms(10);
        }
    }
#elif COMMAND_BYTE_LENGTH == 1
    if(ECUs_Comm_State == RECEIVED)
    {
        LCD_Clear();
        LCD_WriteString('Control Bus');
        LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
        LCD_WriteString('Dev/Op Selected');
        _delay_ms(10);
    }
#endif
}
void Comm_Bridge_CMD_Res(uint8* Ack_Response)
{
    uint8 ECUs_Comm_State = REQ_DROPPED;
    uint8 Ack_Request = INVALID_ACK_REQUEST;
    if(*Ack_Response == REQ_DONE)
    {
        Ack_Request = CMD_Bus_Res_Ack(*Ack_Response);
        while((Ack_Request == PEER_UNAVAILABLE) || (Ack_Request == INVALID_ACK_REQUEST))
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            if(Ack_Request == PEER_UNAVAILABLE)
            {
                LCD_WriteString('Peer Unavailable');
            }
            else if (Ack_Request == INVALID_ACK_REQUEST)
            {
                LCD_WriteString('Invalid Request');
            }
            _delay_ms(10);
            Ack_Request = CMD_Bus_Res_Ack(*Ack_Response);
        }
    }
    else
    {
        Ack_Request = CMD_Bus_Res_Ack(NACK_RES);
        while((Ack_Request == PEER_UNAVAILABLE) || (Ack_Request == INVALID_ACK_REQUEST))
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            if(Ack_Request == PEER_UNAVAILABLE)
            {
                LCD_WriteString('Peer Unavailable');
            }
            else if (Ack_Request == INVALID_ACK_REQUEST)
            {
                LCD_WriteString('Invalid Request');
            }
            _delay_ms(10);
            Ack_Request = CMD_Bus_Res_Ack(NACK_RES);
        }
        Ack_Request = CMD_Bus_Write(*Ack_Response);
        while(Ack_Request == PEER_UNAVAILABLE) 
        {
            LCD_Clear();
            LCD_WriteString('Control Bus');
            LCD_GoToLocation(LCD_ROW_2,0*LCD_SHIFT_CURSOR);
            LCD_WriteString('Peer Unavailable');
            _delay_ms(10);
            Ack_Request = CMD_Bus_Write(*Ack_Response);
        }
    }
}