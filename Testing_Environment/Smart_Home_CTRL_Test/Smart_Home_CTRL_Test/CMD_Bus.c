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
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
 */
uint8 CMD_Bus_HandShake(void)
{
    uint8 Peer_ID;

    #if SPI_ROLE == SPI_MASTER
        SPI_Master_InitTrans();
    #endif /* SPI_ROLE */

    do{Peer_ID = SPI_Transiver(CMD_BUS_DEV_ID);}
    while(Peer_ID == REQ_DROPPED);
    
     #if SPI_ROLE == SPI_MASTER
        SPI_Master_TermTrans();
    #endif /* SPI_ROLE */

    if(Peer_ID == CMD_BUS_PEER_ID)
        return VALID_PEER;
    else
        return INVALID_PEER;
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
void CMD_Bus_Master_Init(void)
{
    SPI_Master_Init();
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
void CMD_Bus_Slave_Init(void)
{
    SPI_Slave_Init();
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Write(uint8 Req_Command)
{
    uint8 Response=0;
    Response = CMD_Bus_HandShake();

    if(Response == INVALID_PEER)
        return PEER_UNAVAILABLE;
    else 
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        do{Response = SPI_Transiver(Req_Command);}
        while(Response == REQ_DROPPED);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */

        return Response;
    }
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Read(uint8* Req_Command)
{
    if(CMD_Bus_HandShake() == INVALID_PEER)
        return PEER_UNAVAILABLE;
    else 
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        *Req_Command = SPI_Transiver(READING);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */

        return RECEIVED;
    }
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Req_Ack(uint8* Ack_Req_Response)
{
    if(CMD_Bus_HandShake() == INVALID_PEER)
        return PEER_UNAVAILABLE;
    else 
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        *Ack_Req_Response = SPI_Transiver(REQUEST_ACK);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */

        if ((*Ack_Req_Response == ACK_RES) || (*Ack_Req_Response == NACK_RES))
            return RECEIVED;
        else 
            return INVALID_ACK_RESPONSE;
    }
}

/*
 * Description: ...
 * Inputs: ...
 * Outputs: ...
 * Returns: ...
 * Author: Mark Fayez
**/
uint8 CMD_Bus_Res_Ack(uint8 Ack_Response)
{
    uint8 Response=0;
    Response = CMD_Bus_HandShake();

    if(Response == INVALID_PEER)
        return PEER_UNAVAILABLE;
    else 
    {
        #if SPI_ROLE == SPI_MASTER
            SPI_Master_InitTrans();
        #endif /* SPI_ROLE */

        do{Response = SPI_Transiver(Ack_Response);}
        while(Response == REQ_DROPPED);

        #if SPI_ROLE == SPI_MASTER
            SPI_Master_TermTrans();
        #endif /* SPI_ROLE */

        if (Response == REQUEST_ACK)
            return DELIVERED;
        else 
            return INVALID_ACK_REQUEST;
    }
}