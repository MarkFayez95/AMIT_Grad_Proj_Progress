/*
 * Comm_Bridge.h
 *
 * Created: 29/05/2021 02:41:32 PM
 *  Author: Mark Fayez
 */ 

#ifndef COMM_BRIDGE_H_
#define COMM_BRIDGE_H_

#define CREATED       (1)
#define NOT_CREATED   (0)

#ifndef PUID_DB
    #define PUID_DB     NOT_CREATED
#endif /* PUID_DB */

#include "Bluetooth_Mod.h"
#include "CMD_Bus.h"
#include "LCD.h"

#if PUID_DB == CREATED
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

typedef enum 
{
    SEND_FAILED=16,
    REQ_DONE,
    NACK_REASON_REQ,
    INV_DEV_SEL,
    INV_OP_SEL
}Comm_Bridge_Extra_Porting_Codes;

void Comm_Bridge_Init(void);

void Comm_Bridge_BT_Read(uint8* Command);
void Comm_Bridge_BT_Send(uint8 Response);
void Comm_Bridge_BT_SendStream(uint8* data_stream)

uint8 Comm_Bridge_CMD_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Read_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Res(uint8* Ack_Response);

#endif /* COMM_BRIDGE_H_ */

