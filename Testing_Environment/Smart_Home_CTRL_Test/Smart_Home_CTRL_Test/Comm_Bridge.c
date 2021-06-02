/*
 * Comm_Bridge.c
 *
 * Created: 29/05/2021 02:40:45 PM
 *  Author: Mark Fayez
 */ 

 #include "Comm_Bridge.h"
 #include "Status_FollowUp.h"
 
/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
 void Comm_Bridge_Init(void)
 {
    #if COMM_BRI_ROLE == CONTROL_ECU
		Bluetooth_Mod_Init();
		while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
		{
			// Comm_Bridge_Init :: Status LCD Display 'BT Peer' 'Not Connected'
			Status_Disp_LCD(LCD_ROW_TXT_BT_PEER,LCD_ROW_TXT_NOT_CONNECTED);
		}

		// Comm_Bridge_Init :: Status LCD Display 'BT Peer' 'Paired'
		Status_Disp_LCD(LCD_ROW_TXT_BT_PEER,LCD_ROW_TXT_PAIRED);
		
		
        CMD_Bus_Master_Init();
        while(CMD_Bus_HandShake() == INVALID_PEER)
        {
            // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Invalid Peer'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_PEER);
        }

        // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Slave Ready'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_SLAVE_READY);
        
    #elif COMM_BRI_ROLE == ACTUATOR_ECU
        CMD_Bus_Slave_Init();
        while(CMD_Bus_HandShake() == INVALID_PEER)
        {
            // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Invalid Peer'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_PEER);
        }

        // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Master Ready'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_MASTER_READY);
    #endif /* COMM_BRI_ROLE */
 }

#if COMM_BRI_ROLE == CONTROL_ECU
   /*
    * Description: ...
    * Inputs: ...
    * Outputs: ...
    * Returns: ...
    * Author: Mark Fayez
    */
	void Comm_Bridge_BT_Read(uint8* Command)
	{
		uint8 Check_Valid_PUID = 0;
		while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
		{
			// Status LCD Display 'BT Peer' 'Not Connected'
            Status_Disp_LCD(LCD_ROW_TXT_BT_PEER,LCD_ROW_TXT_NOT_CONNECTED);
		}

		do 
		{
			// Comm_Bridge_BT_Read :: Status LCD Display "BT Peer Paired" "pending input"
            Status_Disp_LCD(LCD_ROW_TXT_BT_PEER_PAIRED,LCD_ROW_TXT_PENDING_INPUT);

			Bluetooth_Mod_Seq_Rx(Command);
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
					// Comm_Bridge_BT_Read :: Status LCD Display "Invalid PUID"
                    Status_Disp_LCD(LCD_ROW_TXT_INVALID_PUID,LCD_ROW_TXT_NONE);
				}
			#endif /* PUID_DB */
		} 
		while(Check_Valid_PUID = INVALID_ID);

		// Shift the received frame to delete the PUID from it.
		Command[BT_PUID_BYTE] = Command[BT_DATA_BYTE];
	    #if COMMAND_BYTE_LENGTH == 2
		Command[BT_DATA_BYTE] = Command[BT_DATA_BYTE_2];
	    #endif /* COMMAND_BYTE_LENGTH */
    
		// Comm_Bridge_BT_Read :: Status LCD Display "Valid PUID" "Proceeding..."
        Status_Disp_LCD(LCD_ROW_TXT_VALID_PUID,LCD_ROW_TXT_PROCEEDING);
	}
	
   /*
    * Description: ...
    * Inputs: ...
    * Outputs: ...
    * Returns: ...
    * Author: Mark Fayez
    */
    void Comm_Bridge_BT_Send(uint8 Response)
	{
		Bluetooth_Mod_Tx(Response);
		if(Response == REQ_DONE)
		{
			// Comm_Bridge_BT_Send :: Send Sequence over Bluetooth 'Request Done!'
            Status_Send_BT(TXT_BT_REQUEST_DONE);
        
			// Comm_Bridge_BT_Send :: Status LCD Display 'Send to BT Peer' 'Request Done!'
            Status_Disp_LCD(LCD_ROW_TXT_SENT_TO_BT_PEER,LCD_ROW_TXT_REQUEST_DONE);
		}
		else if(Response == INV_DEV_SEL)
		{
			// Comm_Bridge_BT_Send :: Send Sequence over Bluetooth 'Invalid Device Requested!'
            Status_Send_BT(TXT_BT_INVALID_DEVICE_REQUESTED);

			// Comm_Bridge_BT_Send :: Status LCD Display 'Send to BT Peer' 'Invalid Device!'
            Status_Disp_LCD(LCD_ROW_TXT_SENT_TO_BT_PEER, LCD_ROW_TXT_INVALID_DEVICE);
		}
		else
		{
			// Comm_Bridge_BT_Send :: Send Sequence over Bluetooth 'Invalid Operation Requested!'
            Status_Send_BT(TXT_BT_INVALID_OPERATION_REQUESTED);

			// Comm_Bridge_BT_Send :: Status LCD Display 'Send to BT Peer' 'Invalid Option!'
            Status_Disp_LCD(LCD_ROW_TXT_SENT_TO_BT_PEER, LCD_ROW_TXT_INVALID_OPTION);
		}
	}
	
   /*
    * Description: ...
    * Inputs: ...
    * Outputs: ...
    * Returns: ...
    * Author: Mark Fayez
    */    
    void Comm_Bridge_BT_SendStream(uint8* data_stream)
	{
		Bluetooth_Mod_Tx(ECU_PUID);
		Bluetooth_Mod_Seq_Tx(data_stream);
	}


    /*
    * Description: ...
    * Inputs: ...
    * Outputs: ...
    * Returns: ...
    * Author: Mark Fayez
    **/
    uint8 Comm_Bridge_CMD_Req(uint8* Request_Command)
    {
        uint8 ECUs_Comm_State = REQ_DROPPED;
        uint8 Ack_Validity = INVALID_ACK_RESPONSE;
        uint8 Ack_Response = INVALID_ACK_RESPONSE;
        ECUs_Comm_State = CMD_Bus_Write(Request_Command[CMD_DATA_BYTE]);
        while(ECUs_Comm_State == PEER_UNAVAILABLE)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

            ECUs_Comm_State = CMD_Bus_Write(Request_Command[CMD_DATA_BYTE]);
            _delay_ms(CMD_FAILED_TRANS_REPEAT_DELAY_MS);
        }
        #if COMMAND_BYTE_LENGTH == 2
        if(ECUs_Comm_State == READING)
        {
            ECUs_Comm_State = CMD_Bus_Write(Request_Command[CMD_DATA_BYTE_2]);
            while(ECUs_Comm_State == PEER_UNAVAILABLE)
            {
                // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

                ECUs_Comm_State = CMD_Bus_Write(Request_Command[CMD_DATA_BYTE_2]);
                _delay_ms(CMD_FAILED_TRANS_REPEAT_DELAY_MS);
            }
            if(ECUs_Comm_State != READING)
            {
                // Comm_Bridge_CMD_Req :: Status LCD Display 'CMD Bus Peers' 'Not in Sync'
                Status_Disp_LCD(LCD_ROW_TXT_CMD_BUS_PEERS,LCD_ROW_TXT_NOT_IN_SYNC);

                return SEND_FAILED;
            }
        }
        else 
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'CMD Bus Peers' 'Not in Sync'
            Status_Disp_LCD(LCD_ROW_TXT_CMD_BUS_PEERS,LCD_ROW_TXT_NOT_IN_SYNC);

            return SEND_FAILED;
        }
        #elif COMMAND_BYTE_LENGTH == 1
        if(ECUs_Comm_State != READING)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'CMD Bus Peers' 'Not in Sync'
            return SEND_FAILED;
        }            
        #endif /* COMMAND_BYTE_LENGTH */

        _delay_ms(CMD_SEND_REQ_RECEIVE_ACK_DELAY_MS);

        //* Request Sent, Now confirm with with actuator status of performing the request.*//

        Ack_Validity = CMD_Bus_Req_Ack(&Ack_Response);
        while((Ack_Validity == PEER_UNAVAILABLE) || (Ack_Validity == INVALID_ACK_RESPONSE))
        {
            if(Ack_Validity == PEER_UNAVAILABLE)
            {
                // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);
            }
            else if (Ack_Validity == INVALID_ACK_RESPONSE)
            {
                // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Invalid Response'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_RESPONSE);
            }
            
            Ack_Validity = CMD_Bus_Req_Ack(&Ack_Response);
        }
        if(Ack_Response == ACK_RES)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'Request Done!' ''
            Status_Disp_LCD(LCD_ROW_TXT_REQUEST_DONE,LCD_ROW_TXT_NONE);

            return REQ_DONE;
        }
        else if(Ack_Response == NACK_RES)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'Invalid Request!' 'Requesting Reason'
            Status_Disp_LCD(LCD_ROW_TXT_INVALID_REQUEST,LCD_ROW_TXT_REQUESTING_REASON);

            Ack_Response = CMD_Bus_Write(NACK_REASON_REQ);
            while(Ack_Response == PEER_UNAVAILABLE)
            {
                // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

                Ack_Response = CMD_Bus_Write(NACK_REASON_REQ);
                _delay_ms(10);
            }
            
            // Return the received code (reason for NACK) - as it is - to caller function
            return Ack_Response;
        }
        else
            return OUT_OF_SYNC;
    }
#endif	/* COMM_BRI_ROLE */

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
void Comm_Bridge_CMD_Read_Req(uint8* Request_Command)
{
    uint8 ECUs_Comm_State = REQ_DROPPED;
    ECUs_Comm_State = CMD_Bus_Read(Request_Command);
    while(ECUs_Comm_State == PEER_UNAVAILABLE)
    {
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

        ECUs_Comm_State = CMD_Bus_Read(Request_Command);
        _delay_ms(CMD_FAILED_TRANS_REPEAT_DELAY_MS);
    }
    #if COMMAND_BYTE_LENGTH == 2
    
    // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Device Selected'
    Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_DEVICE_SELECTED);

    ECUs_Comm_State = CMD_Bus_Read(Request_Command+1);
    while(ECUs_Comm_State == PEER_UNAVAILABLE)
    {
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

        ECUs_Comm_State = CMD_Bus_Read(Request_Command+1);
        _delay_ms(CMD_FAILED_TRANS_REPEAT_DELAY_MS);
    }

    // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Op Selected'
    Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_OP_SELECTED);

    #elif COMMAND_BYTE_LENGTH == 1

    // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Dev/Op Selected'
    Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_DEV_OP_SELECTED);
    
    #endif /* COMMAND_BYTE_LENGTH */
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
void Comm_Bridge_CMD_Res(uint8* Ack_Response)
{
    uint8 Ack_Request = INVALID_ACK_REQUEST;
    if(*Ack_Response == REQ_DONE)
    {
        do
        {
            Ack_Request = CMD_Bus_Res_Ack(*Ack_Response);
            if(Ack_Request == PEER_UNAVAILABLE)
            {
                // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Peer Unavailable'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);
            }
            else if (Ack_Request == INVALID_ACK_REQUEST)
            {
                // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Invalid Request'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_REQUEST);
            }
            
        }
        while((Ack_Request == PEER_UNAVAILABLE) || (Ack_Request == INVALID_ACK_REQUEST));
    }
    else
    {
        
        do
        {
            Ack_Request = CMD_Bus_Res_Ack(NACK_RES);
            if(Ack_Request == PEER_UNAVAILABLE)
            {
                // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Peer Unavailable'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);
            }
            else if (Ack_Request == INVALID_ACK_REQUEST)
            {
                // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Invalid Request'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_REQUEST);
            }
            
        }
        while((Ack_Request == PEER_UNAVAILABLE) || (Ack_Request == INVALID_ACK_REQUEST));
        
        Ack_Request = CMD_Bus_Write(*Ack_Response);

        do
        {
            Ack_Request = CMD_Bus_Write(*Ack_Response);

            // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Peer Unavailable'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);
        }
        while(Ack_Request == PEER_UNAVAILABLE);
    }
    // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Response Sent'
    Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_RESPONSE_SENT);
}