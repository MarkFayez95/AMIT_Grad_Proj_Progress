/*
 * CMD_Bus.h
 *
 * Created: 27/05/2021 08:37:05 PM
 *  Author: Mark Fayez
 */ 
#ifndef CMD_BUS_H_
#define CMD_BUS_H_

#define CMD_BUS_ROLE    COMM_BRI_ROLE

#if CMD_BUS_ROLE == CONTROL_ECU
    #define SPI_ROLE            SPI_MASTER
    #define CMD_BUS_DEV_ID      0xA0
    #define CMD_BUS_PEER_ID     0xB0
#elif CMD_BUS_ROLE == ACTUATOR_ECU
    #define SPI_ROLE            SPI_SLAVE
    #define CMD_BUS_DEV_ID      0xB0
    #define CMD_BUS_PEER_ID     0xA0
#endif /* ECU_ROLE */

#include "SPI.h"

typedef enum {
    REQ_DROPPED=0, // if response from peer is 0 then it might indicate that Peer ECU is down.
    VALID_PEER,
    INVALID_PEER,
    READING, // dummy response to be sent on reading
    RECEIVED,
    DELIVERED,
    REQUEST_ACK,
    NACK_RES,
    ACK_RES,
    INVALID_ACK_REQUEST,
    INVALID_ACK_RESPONSE,
    PEER_UNAVAILABLE
}CMD_Bus_States;

void CMD_Bus_Master_Init(void);
void CMD_Bus_Slave_Init(void);
uint8 CMD_Bus_HandShake(void);
uint8 CMD_Bus_Write(uint8 Req_Command);
uint8 CMD_Bus_Read(uint8* Req_Command);
uint8 CMD_Bus_Req_Ack(uint8* Ack_Req_Response);
uint8 CMD_Bus_Res_Ack(uint8 Ack_Response);

#endif /* CMD_BUS_H_ */