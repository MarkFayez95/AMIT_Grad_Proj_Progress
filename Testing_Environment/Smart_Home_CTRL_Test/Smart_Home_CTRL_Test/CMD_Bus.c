/*
 * CMD_Bus.c
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

    #if SPI_ROLE == SPI_MASTER
        SPI_Master_InitTrans();
    #endif /* SPI_ROLE */

    Peer_ID = SPI_Transiver(CMD_BUS_DEV_ID);
    
    #if SPI_ROLE == SPI_MASTER
        SPI_Master_TermTrans();
    #endif /* SPI_ROLE */

    if(Peer_ID == CMD_BUS_PEER_ID)
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

        Response = SPI_Transiver(Req_Command);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(Response == PEER_DROPPED);

    if(Response != READING)
        return FAILED_SEND;
    else 
        return DELIVERED;
    
}

/*
 * Description: Receive/Read Byte from CMD_Bus Peer
 * Inputs: uint8* (pointer to uint8 variable to write the data byte received in it)
 * Outputs: Pass by reference the received byte &AND& Received data byte code (0x04)
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

        *Req_Command = SPI_Transiver(READING);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
    }
    while(*Req_Command == PEER_DROPPED);

    return RECEIVED;
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
    uint16 Iteration_counter = 0;
    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        *Ack_Req_Response = SPI_Transiver(REQUEST_ACK);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */

        Iteration_counter ++;
    }
    while((*Ack_Req_Response != ACK_RES) && (*Ack_Req_Response != NACK_RES) && (Iteration_counter != 0));
    

    if ((*Ack_Req_Response == ACK_RES) || (*Ack_Req_Response == NACK_RES))
        return RECEIVED;
    else 
        return INVALID_ACK_RESPONSE;
    
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
    uint16 Iteration_counter = 0;

    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        Response = SPI_Transiver(Ack_Response);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
        
        Iteration_counter ++;
    }
    while((Response != REQUEST_ACK) && (Iteration_counter != 0));

    if (Response == REQUEST_ACK)
        return DELIVERED;
    else 
        return INVALID_ACK_REQUEST;
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
    uint16 Iteration_counter = 0;
    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        *Nack_Res_Reason = SPI_Transiver(NACK_REASON_REQ);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */

        Iteration_counter ++;
    }
    while((*Nack_Res_Reason != INV_DEV_SEL) && (*Nack_Res_Reason != INV_OP_SEL) && (Iteration_counter != 0));
    

    if ((*Nack_Res_Reason == INV_DEV_SEL) || (*Nack_Res_Reason == INV_OP_SEL))
        return RECEIVED;
    else 
        return INVALID_NACK_REASON;
    
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
    uint16 Iteration_counter = 0;

    do
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        Response = SPI_Transiver(NACK_Reason);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */
        
        Iteration_counter ++;
    }
    while((Response != NACK_REASON_REQ) && (Iteration_counter != 0));

    if (Response == NACK_REASON_REQ)
        return DELIVERED;
    else 
        return INVALID_NACK_REASON_REQ;
}