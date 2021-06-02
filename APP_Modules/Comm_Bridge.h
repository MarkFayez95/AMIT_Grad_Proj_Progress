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

typedef enum 
{
    SEND_FAILED=NACK_RES,
    REQ_DONE,
    NACK_REASON_REQ,
    INV_DEV_SEL,
    INV_OP_SEL,
	OUT_OF_SYNC
}Comm_Bridge_Extra_Porting_Codes;

void Comm_Bridge_Init(void);

void Comm_Bridge_BT_Read(uint8* Command);
void Comm_Bridge_BT_Send(uint8 Response);
void Comm_Bridge_BT_SendStream(uint8* data_stream);
uint8 Comm_Bridge_CMD_Req(uint8* Request_Command);

void Comm_Bridge_CMD_Read_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Res(uint8* Ack_Response);

#endif /* COMM_BRIDGE_H_ */

