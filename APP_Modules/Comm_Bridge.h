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
#include "Status_FollowUp.h"

#ifdef PUID_DB_H_
    #include "PUID_DB.h"
#else
    #define VALID_PUID    0xA8 // static pre-defined Pin User ID for security communicating with peer
    #define ECU_PUID      0xAB
    #define VALID_ID      0x0A
    #define INVALID_ID    0x0C
#endif /* PUID_DB_H_ */

#ifndef COMMAND_BYTE_LENGTH
    #define COMMAND_BYTE_LENGTH     1
#endif /* COMMAND_BYTE_LENGTH */

#define BT_PUID_BYTE	0
#define BT_DATA_BYTE	1

#define CMD_DATA_BYTE	0

#if COMMAND_BYTE_LENGTH == 1
	#define REQ_DEV_SHIFT_MASK	4
	#define REQ_OP_MASK			0x0F
#elif COMMAND_BYTE_LENGTH == 2
	#define BT_DATA_BYTE_2		2
	#define CMD_DATA_BYTE_2		1
#endif /* COMMAND_BYTE_LENGTH */

#define CMD_FAILED_TRANS_REPEAT_DELAY_MS    15
#define CMD_SEND_REQ_RECEIVE_ACK_DELAY_MS   50

typedef enum 
{
    SEND_FAILED=NACK_RES,
    REQ_DONE,
    NACK_REASON_REQ,
    INV_DEV_SEL,
    INV_OP_SEL
}Comm_Bridge_Extra_Porting_Codes;

void Comm_Bridge_Init(void);

#if ECU_ROLE == CONTROL_ECU
	void Comm_Bridge_BT_Read(uint8* Command);
	void Comm_Bridge_BT_Send(uint8 Response);
	void Comm_Bridge_BT_SendStream(uint8* data_stream);
#endif	/* ECU_ROLE */

uint8 Comm_Bridge_CMD_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Read_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Res(uint8* Ack_Response);

#endif /* COMM_BRIDGE_H_ */

