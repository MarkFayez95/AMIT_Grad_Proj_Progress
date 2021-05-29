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
    #define VALID_PUID      0xA8 // static pre-defined Pin User ID for security communicating with peer
    #define VALID_ID      0x0A
    #define INVALID_ID    0x0C
#endif /* PUID_DB_H_ */

void Comm_Bridge_Init(void);

void Comm_Bridge_BT_Read(uint8* Command);
void Comm_Bridge_BT_Respond(uint8* Response);

void Comm_Bridge_CMD_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Read_Req(uint8* Request_Command);
void Comm_Bridge_CMD_Res(uint8* Ack_Response);

#endif /* COMM_BRIDGE_H_ */

