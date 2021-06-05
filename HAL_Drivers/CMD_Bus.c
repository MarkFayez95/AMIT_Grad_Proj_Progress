/*
 * CMD_Bus.c
 * HAL Layer Driver that utilized the SPI MCAL Driver to create a communication Bus with slave ECU over SPI Standard communication protocol.
 * It is also trying to apply a basic protocol of it's own that run at a higher software level than the physical level of SPI.
 * Role in architecture: this driver is to perform under the Comm_Bridge which acts as the communication manager of the system. 
 * 
 * Created: 27/05/2021 08:38:25 PM
 *  Author: Mark Fayez
**/ 

#include "Smart_Home_Sys_Config.h"
#include "CMD_Bus.h"

/*
 * Description: CMD Bus Handshake between Master and Slave of SPI bus
 * Inputs: None
 * Outputs: Valid_Peer Code (0x01) -OR- Invalid_Peer Code (0x02) 
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
 */
uint8 CMD_Bus_HandShake(void)
{
    uint8 Peer_ID;

    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        // send the current device ID (ID sepcific for Command Bus driver/Module) and receives the peer ID.
        Peer_ID = SPI_Transiver(CMD_BUS_DEV_ID);
        
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(Peer_ID == PEER_DROPPED); // repeat the handshake above if peer ID received is actually a 0xFF (No Peer)

    if(Peer_ID == CMD_BUS_PEER_ID) // check validity of the ID received if it's not a dropped code.
        return VALID_PEER;
    else
        return INVALID_PEER;
}

/*
 * Description: Initiate the CMD_Bus communication as Master
 * Inputs: None
 * Outputs: SPI peripheral initiated as Master
 * Returns: None
 * Author: Mark Fayez
**/
void CMD_Bus_Master_Init(void)
{
    SPI_Master_Init();
}

/*
 * Description: Initiate the CMD_Bus communication as Slave
 * Inputs: None
 * Outputs: SPI peripheral initiated as Slave
 * Returns: None
 * Author: Mark Fayez
**/
void CMD_Bus_Slave_Init(void)
{
    SPI_Slave_Init();
}

/*
 * Description: send Byte to the CMD_Bus Peer
 * Inputs: uint8 (1 Data Byte)
 * Outputs: Delivered successfully code (0x05) ||OR|| FAILED_SEND code (0x06)
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Write(uint8 Req_Command)
{
    uint8 Response=0;

    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        // send data byte to Peer and receive the cross talk code and save it.
        Response = SPI_Transiver(Req_Command);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(Response == PEER_DROPPED); //loop while data bytes are dropped on a missing peer.

    if(Response != READING) // check if the cross talk code is a valid READING code
        return FAILED_SEND;
    else 
        return DELIVERED;
    
}

/*
 * Description: Receive/Read Byte from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to write the data byte received in it)
 * Outputs: Pass by reference the received byte &AND& Received data byte code (0x04)
** Note: This Function shall hault the system till a data exchange is performed.
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Read(uint8* Req_Command)
{
    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        // receive a data byte from peer sending the default cross talk code for receiving (READING), and save received data byte in the passed by reference variable
        *Req_Command = SPI_Transiver(READING);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(*Req_Command == PEER_DROPPED); // loop if data is invalid (0xFF == SPI's way of saying peer is not found)

    return RECEIVED; // return with code RECEIVED when done.
}

/*
 * Description: Request Acknowledgement from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to store the respond received in it)
 * Outputs: Received code (0x04) if a valid Ack_Response code was received ||OR|| Invalid Ack_Response code (0x0B) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Req_Ack(uint8* Ack_Req_Response)
{
    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */
        // save received byte in the passed by reference variable , sending code (REQUEST_ACK) to the Peer
        *Ack_Req_Response = SPI_Transiver(REQUEST_ACK);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(*Ack_Req_Response == PEER_DROPPED); // loop while peer is disconnected

    if ((*Ack_Req_Response == ACK_RES) || (*Ack_Req_Response == NACK_RES)) // check if the code received is a received acknowledgement option.
        return RECEIVED;
    else 
        return INVALID_ACK_RESPONSE; // return Invalid code if response received is not a valid acknowledgement code
    
}

/*
 * Description: Respond to Acknowledgement request by CMD_Bus Peer
 * Inputs: uint8 (the Acknowledgement response code to be sent)
 * Outputs: Delivered Code (0x05) if a valid Ack_Request code received ||OR|| Invalid Ack_Request code (0x0A) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Res_Ack(uint8 Ack_Response)
{
    uint8 Response = 0;
    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        // send the passed value to the peer and save the cross talk response.
        Response = SPI_Transiver(Ack_Response);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(Response == PEER_DROPPED); // loop while cross talk indicate peer is dropped.
    
    if (Response == REQUEST_ACK)
        return DELIVERED; 
    else 
        return INVALID_ACK_REQUEST; // return invalid code if the cross talk was not the expected request for Acknowledgement
}

/*
 * Description: Request Reason for NACK Response received earlier from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to store the respond received in it)
 * Outputs: Received code (0x04) if a valid Ack_Response code was received ||OR|| Invalid NACK Reason code (0x11) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Req_Reason_NACK(uint8* Nack_Res_Reason)
{
    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        // save received cross talk in the passed by reference variable sending code NACK_REASON_REQ
        *Nack_Res_Reason = SPI_Transiver(NACK_REASON_REQ);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(*Nack_Res_Reason == PEER_DROPPED); // loop while transmission is dropped.

    if ((*Nack_Res_Reason == INV_DEV_SEL) || (*Nack_Res_Reason == INV_OP_SEL))
        return RECEIVED;
    else 
        return INVALID_NACK_REASON; // if not a valid reason code is received return INVALID_NACK_REASON code.
    
}

/*
 * Description: provide NACK reason responding to Reason for NACK request by CMD_Bus Peer
 * Inputs: uint8 (the Acknowledgement response code to be sent)
 * Outputs: Delivered Code (0x05) if a valid Ack_Request code received ||OR|| Invalid Reason for NACK code (0x0e) if not
 * Returns: uint8 (code indicating the status of the requested process)
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Res_Reason_NACK(uint8 NACK_Reason)
{
    uint8 Response = 0;

    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */
        
        // send the reason code (following a NACK response) to the Peer, and save the received cross talk for checking synchronization
        Response = SPI_Transiver(NACK_Reason);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(Response == PEER_DROPPED); // loop while the received cross talk indicates peer has dropped off the CMD_Bus

    if (Response == NACK_REASON_REQ)
        return DELIVERED;
    else 
        return INVALID_NACK_REASON_REQ; // if received cross talk code is not NACK_REASON_REQ
}