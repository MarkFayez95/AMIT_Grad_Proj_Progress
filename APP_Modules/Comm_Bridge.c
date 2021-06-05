/*
 * Comm_Bridge.c
 *
 * Created: 29/05/2021 02:40:45 PM
 *  Author: Mark Fayez
 */ 

#include "Smart_Home_Sys_Config.h"
#include "Comm_Bridge.h"
#include "Status_FollowUp.h" 

/*
 * Description: Initialize the Communication Bridge of the ECU depending on its role defined in the Sys_Config file
 * Inputs: None
 * Outputs: None
 * Returns: None
 * Author: Mark Fayez
**/
 void Comm_Bridge_Init(void)
 {
    uint8 ECUs_Comm_State = FAILED_SEND;

    #if ECU_ROLE == CONTROL_ECU
		// Comm_Bridge_Init :: Status LCD Display 'BT Peer' 'Not Connected'
		Status_Disp_LCD(LCD_ROW_TXT_BT_PEER,LCD_ROW_TXT_NOT_CONNECTED);
        
        // Initialize the Bluetooth Module driver
        Bluetooth_Mod_Init();
		while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);

		// Comm_Bridge_Init :: Status LCD Display 'BT Peer' 'Paired'
		Status_Disp_LCD(LCD_ROW_TXT_BT_PEER,LCD_ROW_TXT_PAIRED);
		
        // Initialize the CMD_Bus driver as Master
        CMD_Bus_Master_Init();

        // Perform hanshake and hault on its status
        ECUs_Comm_State = CMD_Bus_HandShake();
        if( ECUs_Comm_State == INVALID_PEER)
        {
            // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Invalid Peer'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_PEER);

            ECUs_Comm_State = CMD_Bus_HandShake();
        }
        while(ECUs_Comm_State == INVALID_PEER); // loop till a valid CMD_Bus Slave Peer is detected.

        // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Slave Ready'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_SLAVE_READY);
    #elif ECU_ROLE == ACTUATOR_ECU
        // Initialize the CMD_Bus driver as Slave
        CMD_Bus_Slave_Init();

        // Perform hanshake and hault on its status
        ECUs_Comm_State = CMD_Bus_HandShake();
        if(ECUs_Comm_State == INVALID_PEER)
        {
            // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Invalid Peer'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_PEER);

            ECUs_Comm_State = CMD_Bus_HandShake();
        }
        while(ECUs_Comm_State == INVALID_PEER); // loop till a valid CMD_Bus Master Peer is detected.

        // Comm_Bridge_Init :: Status LCD Display 'Control Bus' 'Master Ready'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_MASTER_READY);
    #endif /* ECU_ROLE */
 }


/*
* Description: Reading command from Bluetooth user using Bluetooth_Mod Driver
* Inputs: uint8* (Pointer to array of bytes to store the received command packet in it)
* Outputs: The command data packet as array of bytes (uint8[])
* Returns: None
* Author: Mark Fayez
*/
void Comm_Bridge_BT_Read(uint8* Command)
{
#if ECU_ROLE == CONTROL_ECU    
    uint8 Check_Valid_PUID = INVALID_ID;
    
    if(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED)
    {
        // Status LCD Display 'BT Peer' 'Not Connected'
        Status_Disp_LCD(LCD_ROW_TXT_BT_PEER,LCD_ROW_TXT_NOT_CONNECTED);
    }
    while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);

    do 
    {
        // Comm_Bridge_BT_Read :: Status LCD Display "BT Peer Paired" "pending input"
        Status_Disp_LCD(LCD_ROW_TXT_BT_PEER_PAIRED,LCD_ROW_TXT_PENDING_INPUT);

        // Read the command data stream/packet - from Bluetooth module - in the Command array of bytes
        Bluetooth_Mod_Seq_Rx(Command);

        // check the packet for the Pin User Identifier if it matches the one in the config file defined be the Macro VALID_PUID
        if(Command[BT_PUID_BYTE] == VALID_PUID)
        {
            Check_Valid_PUID = VALID_ID; // set check validity flag to Valid ID to break the loop
        }
        else
        {
            Check_Valid_PUID = INVALID_ID; // set check validity flag to Valid ID to keep in loop reading new data from Bluetooth
            // Comm_Bridge_BT_Read :: Status LCD Display "Invalid PUID"
            Status_Disp_LCD(LCD_ROW_TXT_INVALID_PUID,LCD_ROW_TXT_NONE);
        }
        
    } 
    while(Check_Valid_PUID == INVALID_ID);

    // Shift the received frame to delete the PUID from it.
    Command[BT_PUID_BYTE] = Command[BT_DATA_BYTE];
    #if COMMAND_BYTE_LENGTH == 2
    Command[BT_DATA_BYTE] = Command[BT_DATA_BYTE_2];
    #endif /* COMMAND_BYTE_LENGTH */

    // Comm_Bridge_BT_Read :: Status LCD Display "Valid PUID" "Proceeding..."
    Status_Disp_LCD(LCD_ROW_TXT_VALID_PUID,LCD_ROW_TXT_PROCEEDING);
#endif /* ECU_ROLE */
}

/*
* Description: send response code to User's request through Bluetooth
* Inputs: uint8 (The response code required to be sent)
* Outputs: None
* Returns: None
* Author: Mark Fayez
*/
void Comm_Bridge_BT_Send(uint8 Response)
{
#if ECU_ROLE == CONTROL_ECU
    Bluetooth_Mod_Tx(Response);
    if(Response == REQ_DONE)
    {
        // Comm_Bridge_BT_Send :: Status LCD Display 'Send to BT Peer' 'Request Done!'
        Status_Disp_LCD(LCD_ROW_TXT_SENT_TO_BT_PEER,LCD_ROW_TXT_REQUEST_DONE);
    }
    else if(Response == INV_DEV_SEL)
    {
        // Comm_Bridge_BT_Send :: Status LCD Display 'Send to BT Peer' 'Invalid Device!'
        Status_Disp_LCD(LCD_ROW_TXT_SENT_TO_BT_PEER, LCD_ROW_TXT_INVALID_DEVICE);
    }
    else
    {
        // Comm_Bridge_BT_Send :: Status LCD Display 'Send to BT Peer' 'Invalid Option!'
        Status_Disp_LCD(LCD_ROW_TXT_SENT_TO_BT_PEER, LCD_ROW_TXT_INVALID_OPTION);
    }
#endif /* ECU_ROLE */
}

/*
* Description: send a stream of bytes to user through Bluetooth Module (in case you want to send a specific message out of the designed codes that are decoded by the user's Application)
* Inputs: uint8* (pointer to uint8 variable to point to an array of characters/bytes)
* Outputs: None
* Returns: None
* Author: Mark Fayez
*/    
void Comm_Bridge_BT_SendStream(uint8* data_stream)
{
#if ECU_ROLE == CONTROL_ECU
    Bluetooth_Mod_Tx(ECU_PUID);
    Bluetooth_Mod_Seq_Tx(data_stream);
#endif /* ECU_ROLE */
}


/*
* Description: Pass command/Request from CTRL to Actuator ECU and respond Acknowledgement on performing the required action.
* Inputs: uint8* (Pointer to uint8 array that have the command bytes 1 or 2 bytes depending on Sys_Config file settings)
* Outputs: The response from the peer regarding the validity of the request and the action taken if it was valid, it's added in the array.
*           Exact codes of the response are decided by the devices manager module in the actuator system.
*           It return either IN_SYNC if send was processed correctly ||OR|| OUT_OF_SYNC if the request trials reached MAX_FAILED_COMM_BRI_TRANSMISSIONS
* Returns: uint8 (code indicating the status of the requested process)
* Author: Mark Fayez
**/
uint8 Comm_Bridge_CMD_Req(uint8* Request_Command)
{
#if ECU_ROLE == CONTROL_ECU

    uint8 ECUs_Comm_State = PEER_UNAVAILABLE;
    uint8 Failed_Iteration_counter = 0;
    
    uint8 Ack_Validity = INVALID_ACK_RESPONSE;
    uint8 Ack_Response = ACK_RES;
    
    ECUs_Comm_State = CMD_Bus_HandShake();
    for(Failed_Iteration_counter = 0; (ECUs_Comm_State == INVALID_PEER) && (Failed_Iteration_counter < MAX_FAILED_COMM_BRI_HANDSHAKES); Failed_Iteration_counter++)
    {
        // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

        ECUs_Comm_State = CMD_Bus_HandShake();
    }
    // check if maximum number of failed handshakes is reached
    if((Failed_Iteration_counter == MAX_FAILED_COMM_BRI_HANDSHAKES) && (ECUs_Comm_State == INVALID_PEER))
    {
        // Comm_Bridge_CMD_Req :: Status LCD Display 'CMD Bus Peers' 'Not in Sync'
        Status_Disp_LCD(LCD_ROW_TXT_CMD_BUS_PEERS,LCD_ROW_TXT_NOT_IN_SYNC);
        ECUs_Comm_State = SEND_FAILED;

        return OUT_OF_SYNC;
    }

    // if Handshake was successfull and a valid peer is detected, then prceed with sending the command byte.
    if(ECUs_Comm_State == VALID_PEER)
    {
        // send the command byte to the CMD Peer
        ECUs_Comm_State = CMD_Bus_Write(Request_Command[CMD_DATA_BYTE]);
        if(ECUs_Comm_State == FAILED_SEND)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Send CMD Failed'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_SEND_CMD_FAILED);

            return OUT_OF_SYNC;
        }
        
        #if COMMAND_BYTE_LENGTH == 2
            else if(ECUs_Comm_State == DELIVERED)
            {
                // if first byte is sent successfully then send the second byte of the command
                ECUs_Comm_State = CMD_Bus_Write(Request_Command[CMD_DATA_BYTE_2]);

                if(ECUs_Comm_State == FAILED_SEND)
                {
                    // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Send B2 Failed'
                    Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_SEND_B2_FAILED);

                    return OUT_OF_SYNC;
                }
            }
        #endif /* COMMAND_BYTE_LENGTH */
    }
    
    _delay_ms(CMD_SEND_REQ_RECEIVE_ACK_DELAY_MS);

    //* Request Sent, Now confirm with with actuator status of performing the request.*//

    // Request confirmation from CMD_Bus Peer that the request was valid
    Ack_Validity = CMD_Bus_Req_Ack(&Ack_Response);

    // Check if valid ACK response is received.
    if(Ack_Validity == INVALID_ACK_RESPONSE)
    {
        // Comm_Bridge_CMD_Req :: Status LCD Display "Control Bus" "Invalid Response"
        Status_Disp_LCD( LCD_ROW_TXT_CONTROL_BUS , LCD_ROW_TXT_INVALID_RESPONSE);

        return OUT_OF_SYNC;
    }
    // if a valid ACK Response was received, then we shall check on it and return the response to the caller
    else if(Ack_Response == ACK_RES)
    {
        // Comm_Bridge_CMD_Req :: Status LCD Display 'Request Done!' ''
        Status_Disp_LCD(LCD_ROW_TXT_REQUEST_DONE,LCD_ROW_TXT_NONE);

        Request_Command[RESPONSE_DATA_BYTE] = REQ_DONE;

        return IN_SYNC; // since communication protocol is completed return success IN_SYNC code ensuring both peers are still in sync.
    }
    else if(Ack_Response == NACK_RES)
    {
        // Comm_Bridge_CMD_Req :: Status LCD Display 'Invalid Request!' 'Requesting Reason'
        Status_Disp_LCD(LCD_ROW_TXT_INVALID_REQUEST,LCD_ROW_TXT_REQUESTING_REASON);

        // request from CMD_Bus Peer reason for NACK response received and check on validity of response.
        Ack_Validity = CMD_Bus_Req_Reason_NACK(&Ack_Response);

        // loop if received reason code is invalid till MAX_FAILED_COMM_BRI_TRANSMISSIONS is reached or a valid reason code is received.
        if(Ack_Validity == INVALID_NACK_REASON)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display "Control Bus" "Invalid Response"
            Status_Disp_LCD( LCD_ROW_TXT_CONTROL_BUS , LCD_ROW_TXT_INVALID_RESPONSE);

            return OUT_OF_SYNC;
        }
        else 
        {
            // if a valid reason is received then return the received code (reason for NACK) to caller function in the same array the command was received in.
            Request_Command[RESPONSE_DATA_BYTE] =  Ack_Response;

            return IN_SYNC; // since communication protocol is completed return success IN_SYNC code ensuring both peers are still in sync.
        }
    }
    else
		return OUT_OF_SYNC;

#endif	/* ECU_ROLE */
}


/*
 * Description: read the Command data byte from the peer on CMD_Bus
 * Inputs: uint8* (pointer to arry to save the received command Byte/s)
 * Outputs: RECEIVED code (0x04) if command data byte/s is/are received after a successfull handshake with the peer ||OR|| OUT_OF_SYNC code (4) if handshake couldn't be completed, hence no data received.
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 Comm_Bridge_CMD_Read_Req(uint8* Request_Command)
{
#if ECU_ROLE == ACTUATOR_ECU
    uint8 ECUs_Comm_State = OUT_OF_SYNC;
    uint8 Failed_Iteration_counter = 0;

    ECUs_Comm_State = CMD_Bus_HandShake();
    
    for(Failed_Iteration_counter = 0; (ECUs_Comm_State != VALID_PEER) && (Failed_Iteration_counter < MAX_FAILED_COMM_BRI_HANDSHAKES); Failed_Iteration_counter++)
    {
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);

        ECUs_Comm_State = CMD_Bus_HandShake();
    }
    if((Failed_Iteration_counter == MAX_FAILED_COMM_BRI_HANDSHAKES) && (ECUs_Comm_State == INVALID_PEER))
    {
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'CMD Bus Peers' 'Not in Sync'
        Status_Disp_LCD(LCD_ROW_TXT_CMD_BUS_PEERS,LCD_ROW_TXT_NOT_IN_SYNC);

        return OUT_OF_SYNC;
    }
    // Repeat handshake if failed with max iterations pre-set in configurations file then break out of loop anyway.
    
    if(ECUs_Comm_State == VALID_PEER)
    {
        #if COMMAND_BYTE_LENGTH == 2
        CMD_Bus_Read(Request_Command);
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Device Selected'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_DEVICE_SELECTED);

        CMD_Bus_Read(Request_Command+1);
    
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Op Selected'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_OP_SELECTED);

        #elif COMMAND_BYTE_LENGTH == 1
        CMD_Bus_Read(Request_Command);
        // Comm_Bridge_CMD_Read_Req :: Status LCD Display 'Control Bus' 'Dev/Op Selected'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_DEV_OP_SELECTED);
        #endif /* COMMAND_BYTE_LENGTH */

        return RECEIVED;
    }
    else
    {
        return OUT_OF_SYNC;
    }
#endif /* ECU_ROLE */
}

/*
 * Description: to respond to the CMD Peer regarding the command that was send to the device, the response is according to request validity
 * Inputs: uint8* (Pointer to the validity value resolved by the upper layer application - the Devices manager)
 * Outputs: replace the Ack response value by OUT_OF_SYNC if MAX_FAILED_COMM_BRI_TRANSMISSIONS is reached without being able to send the data.
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 Comm_Bridge_CMD_Res(uint8 Ack_Response)
{
#if ECU_ROLE == ACTUATOR_ECU
    uint8 Ack_Request = INVALID_ACK_REQUEST;

    if(Ack_Response == REQ_DONE)
    {
        Ack_Request = CMD_Bus_Res_Ack(ACK_RES);
        if(Ack_Request == INVALID_ACK_REQUEST)
        {
            // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Invalid Request'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_REQUEST);

            return OUT_OF_SYNC;
        }
        else
        {
            // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Response Sent'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_RESPONSE_SENT);

            return IN_SYNC; // since communication protocol is completed by sending the ACK response, return success IN_SYNC code ensuring both peers are still in sync.
        }  
    }
    else
    {

        Ack_Request = CMD_Bus_Res_Ack(NACK_RES);
        if(Ack_Request == INVALID_ACK_REQUEST)
        {
            // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Invalid Request'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_REQUEST);

            return OUT_OF_SYNC;
        }
        else if(Ack_Request == DELIVERED)
        {

            Ack_Request = CMD_Bus_Res_Reason_NACK(Ack_Response);
            if(Ack_Request == INVALID_NACK_REASON_REQ)
            {
                // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Invalid Request'
                Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_INVALID_REQUEST);

                return OUT_OF_SYNC;
            }
        }
        // Comm_Bridge_CMD_Res :: Status LCD Display 'Control Bus' 'Response Sent'
        Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_RESPONSE_SENT);

        return IN_SYNC; // since communication protocol is completed by sending reason for NACK response, return success IN_SYNC code ensuring both peers are still in sync.
    }
#endif /* ECU_ROLE */
}


/*
 * Description: Re-sync the Peers on the CMD bus using a certain amount of hanshakes and then a delay
 * Inputs: None (predefined macro for number of hanshakes required for re-syncing)
 * Outputs: None
 * Returns: None
 * Author: Mark Fayez
**/
void Comm_Bridge_CMD_Bus_Re_Sync(void)
{
    uint8 Iteration_counter = 0;

    uint8 ECUs_Comm_State = OUT_OF_SYNC;
    
    ECUs_Comm_State = CMD_Bus_HandShake();
    
    for(Iteration_counter = 0; (ECUs_Comm_State == VALID_PEER) && (Iteration_counter < NUM_OF_RESYNC_HANDSHAKES); Iteration_counter++)
    {
        if(ECUs_Comm_State == INVALID_PEER)
        {
            // Comm_Bridge_CMD_Req :: Status LCD Display 'Control Bus' 'Peer Unavailable'
            Status_Disp_LCD(LCD_ROW_TXT_CONTROL_BUS,LCD_ROW_TXT_PEER_UNAVAILABLE);
            Iteration_counter = 0;
        }
        ECUs_Comm_State = CMD_Bus_HandShake();
    }

    _delay_ms(PRIOR_RE_SYNC_HANDSHAKES_DELAY_MS);
}