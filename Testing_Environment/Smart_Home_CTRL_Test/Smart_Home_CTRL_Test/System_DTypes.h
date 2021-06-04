/*
 * System_DTypes.h
 *
 * Created: 04/06/2021 04:23:30 PM
 *  Author: Mark Fayez
 */ 

#ifndef SYSTEM_D_TYPES_H_
#define SYSTEM_D_TYPES_H_


//** Bluetooth Module required data types **//
typedef enum {
    BT_NOT_PAIRED,
    BT_PAIRED
} BT_Pair_State;

//** CMD_Bus Driver required data types **//
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
	OUT_OF_SYNC, // Out of Sync state code 0x13
    IN_SYNC // In Sync state code 0x14
}CMD_Bus_States;


//** Devices Manager application required data types **//
typedef enum
{
	DEV_1,
	DEV_2,
	DEV_3,
	DEV_4,
	DEV_5,
	DEV_6,
	DEV_7,
	DEV_8,
} DEV_Codes;

typedef enum
{
	OP_1,
	OP_2,
	OP_3,
	OP_4,
	OP_5,
	OP_6,
	OP_7,
	OP_8,
} OP_Codes;

typedef enum
{
	RESERVED,
	DEV_N_OP_VALID,
	DEV_INVALID,
	OP_INVALID
} Dev_Ops_Check_Status;


#endif /* SYSTEM_D_TYPES_H_ */