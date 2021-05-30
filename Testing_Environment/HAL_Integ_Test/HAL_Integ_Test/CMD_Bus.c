/*
 * CMD_Bus.c
 *
 * Created: 27/05/2021 08:38:25 PM
 *  Author: Mark Fayez
**/ 

#include "CMD_Bus.h"

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
    else if(Peer_ID == REQ_DROPPED)
        return REQ_DROPPED;
    else
        return INVALID_PEER;
}
void CMD_Bus_Master_Init(void)
{
    SPI_Master_Init();
}
void CMD_Bus_Slave_Init(void)
{
    SPI_Slave_Init();
}
uint8 CMD_Bus_Write(uint8 Req_Command)
{
    uint8 Response=0;
    do {Response = CMD_Bus_HandShake();}
    while(Response == REQ_DROPPED);


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
uint8 CMD_Bus_Read(uint8* Req_Command)
{
    uint8 Response=0;
    do {Response = CMD_Bus_HandShake();}
    while(Response == REQ_DROPPED);


    if(Response == INVALID_PEER)
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
uint8 CMD_Bus_Req_Ack(uint8* Ack_Req_Response)
{
    uint8 Response=0;
    do {Response = CMD_Bus_HandShake();}
    while(Response == REQ_DROPPED);


    if(Response == INVALID_PEER)
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

uint8 CMD_Bus_Res_Ack(uint8 Ack_Response)
{
    uint8 Response=0;
    do {Response = CMD_Bus_HandShake();}
    while(Response == REQ_DROPPED);


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