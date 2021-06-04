/*
 * CMD_Bus.h
 *
 * Created: 27/05/2021 08:37:05 PM
 *  Author: Mark Fayez
 */ 
#ifndef CMD_BUS_H_
#define CMD_BUS_H_

#include "SPI.h"

#define PEER_DROPPED    0xFF  // if response from peer is FF then it might indicate that Peer ECU is down.

typedef enum 
{
    VALID_PEER = 0x01, // Valid Peer code 0x01
    INVALID_PEER, // Invalid Peer code 0x02
    READING, // Reading code 0x03
    RECEIVED, // Received data byte code 0x04
    DELIVERED, // Delivered successfully code 0x05
    FAILED_SEND, // Failed Send code 0x06
    REQUEST_ACK, // Request Acknowledgement code 0x07
    NACK_RES, // NACK response code 0x08
    ACK_RES, // Ack response code 0x09
    INVALID_ACK_REQUEST, // Invalid Ack request code 0x0A
    INVALID_ACK_RESPONSE, // Invalid Ack response code 0x0B
    PEER_UNAVAILABLE, // Peer unavailable code 0x0C
    NACK_REASON_REQ, // Request Reason for NACK code 0x0D
    INVALID_NACK_REASON_REQ, //Invalid Reason for NACK code 0x0E
    INV_DEV_SEL, // Invalide device selection code 0x0F
    INV_OP_SEL, // Invalid device selection code 0x10
    INVALID_NACK_REASON, // Invalid Reason for NACK code 0x11
    REQ_DONE, // Request Done code 0x12
	OUT_OF_SYNC // Out of Sync state code 0x13
}CMD_Bus_States;

/*
 * Description: Initiate the CMD_Bus communication as Master
 * Inputs: None
 * Outputs: SPI peripheral initiated as Master
 * Returns: None
 * Author: Mark Fayez
**/
void CMD_Bus_Master_Init(void);

/*
 * Description: Initiate the CMD_Bus communication as Slave
 * Inputs: None
 * Outputs: SPI peripheral initiated as Slave
 * Returns: None
 * Author: Mark Fayez
**/
void CMD_Bus_Slave_Init(void);
/*
 * Description: CMD Bus Handshake between Master and Slave of SPI bus
 * Inputs: None
 * Outputs: VALID_PEER Code (0x01) ||OR|| INVALID_PEER Code (0x02) 
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
 */
uint8 CMD_Bus_HandShake(void);

/*
 * Description: send Byte to the CMD_Bus Peer
 * Inputs: uint8 (1 Data Byte)
 * Outputs: DELIVERED successfully code (0x05) ||OR|| FAILED_SEND code (0x06)
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Write(uint8 Req_Command);

/*
 * Description: Receive/Read Byte from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to write the data byte received in it)
 * Outputs: Pass by reference the received byte &AND& RECEIVED data byte code (0x04)
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Read(uint8* Req_Command);

/*
 * Description: Request Acknowledgement from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to store the respond received in it)
 * Outputs: RECEIVED code (0x04) if a valid Ack_Response code was received ||OR|| INVALID_ACK_RESPONSE code (0x0B) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Req_Ack(uint8* Ack_Req_Response);

/*
 * Description: Respond to Acknowledgement request by CMD_Bus Peer
 * Inputs: uint8 (the Acknowledgement response code to be sent)
 * Outputs: DELIVERED Code (0x05) if a valid REQUEST_ACK code received ||OR|| INVALID_ACK_REQUEST code (0x0A) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Res_Ack(uint8 Ack_Response);

/*
 * Description: Request Reason for NACK Response received earlier from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to store the respond received in it)
 * Outputs: RECEIVED code (0x04) if a valid Ack_Response code was received ||OR|| INVALID_NACK_REASON code (0x11) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Req_Reason_NACK(uint8* Nack_Res_Reason);

/*
 * Description: provide NACK reason responding to Reason for NACK request by CMD_Bus Peer
 * Inputs: uint8 (the Acknowledgement response code to be sent)
 * Outputs: DELIVERED Code (0x05) if a valid Reason for NACK response code received ||OR|| INVALID_NACK_REASON_REQ code (0x0e) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Res_Reason_NACK(uint8 NACK_Reason);

#endif /* CMD_BUS_H_ */