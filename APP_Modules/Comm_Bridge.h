/*
 * Comm_Bridge.h
 *
 * Created: 29/05/2021 02:41:32 PM
 *  Author: Mark Fayez
 */ 

#ifndef COMM_BRIDGE_H_
#define COMM_BRIDGE_H_

#include "Bluetooth_Mod.h"
#include "CMD_Bus.h"

#ifdef PUID_DB_H_
    #include "PUID_DB.h"
#endif /* PUID_DB_H_ */

typedef enum 
{
    SEND_FAILED,
    REQ_DONE,
    INV_DEV_SEL,
    INV_OP_SEL,
	OUT_OF_SYNC,
    IN_SYNC
} Comm_Bridge_CMD_Bus_Response_Options;

/*
 * Description: Initialize the Communication Bridge of the ECU depending on its role defined in the Sys_Config file
 * Inputs: None
 * Outputs: None
 * Returns: None
 * Author: Mark Fayez
**/
void Comm_Bridge_Init(void);

/*
* Description: Reading command from Bluetooth user using Bluetooth_Mod Driver
* Inputs: uint8* (Pointer to array of bytes to store the received command packet in it)
* Outputs: The command data packet as array of bytes (uint8[])
* Returns: None
* Author: Mark Fayez
*/
void Comm_Bridge_BT_Read(uint8* Command);

/*
* Description: send response code to User's request through Bluetooth
* Inputs: uint8 (The response code required to be sent)
* Outputs: None
* Returns: None
* Author: Mark Fayez
*/
void Comm_Bridge_BT_Send(uint8 Response);

/*
* Description: send a stream of bytes to user through Bluetooth Module (in case you want to send a specific message out of the designed codes that are decoded by the user's Application)
* Inputs: uint8* (pointer to uint8 variable to point to an array of characters/bytes)
* Outputs: None
* Returns: None
* Author: Mark Fayez
*/  
void Comm_Bridge_BT_SendStream(uint8* data_stream);

/*
* Description: Pass command/Request from CTRL to Actuator ECU and respond Acknowledgement on performing the required action.
* Inputs: uint8* (Pointer to uint8 array that have the command bytes 1 or 2 bytes depending on Sys_Config file settings)
* Outputs: The response from the peer regarding the validity of the request and the action taken if it was valid, it's added in the array.
*           Exact codes of the response are decided by the devices manager module in the actuator system.
* Returns: None
* Author: Mark Fayez
**/
void Comm_Bridge_CMD_Req(uint8* Request_Command);

/*
 * Description: read the Command data byte from the peer on CMD_Bus
 * Inputs: uint8* (pointer to arry to save the received command Byte/s)
 * Outputs: RECEIVED code (0x04) if command data byte/s is/are received after a successfull handshake with the peer ||OR|| OUT_OF_SYNC code (4) if handshake couldn't be completed, hence no data received.
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 Comm_Bridge_CMD_Read_Req(uint8* Request_Command);

/*
 * Description: to respond to the CMD Peer regarding the command that was send to the device, the response is according to request validity
 * Inputs: uint8* (Pointer to the validity value resolved by the upper layer application - the Devices manager)
 * Outputs: replace the Ack response value by OUT_OF_SYNC if end of function reached without being able to send the data.
 * Returns: None
 * Author: Mark Fayez
**/
void Comm_Bridge_CMD_Res(uint8* Ack_Response);

/*
 * Description: Re-sync the Peers on the CMD bus using a certain amount of hanshakes and then a delay
 * Inputs:  None (predefined macro for number of hanshakes required for re-syncing)
 * Outputs: None
 * Returns: None
 * Author: Mark Fayez
**/
void Comm_Bridge_CMD_Bus_Re_Sync(void);

#endif /* COMM_BRIDGE_H_ */

