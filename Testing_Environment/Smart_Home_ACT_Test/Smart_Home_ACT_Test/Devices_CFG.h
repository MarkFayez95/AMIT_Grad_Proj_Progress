/*
 * Devices_CFG.h
 *
 * Created: 30/05/2021 04:08:43 PM
 *  Author: Mark Fayez
 */ 


#ifndef DEVICES_CFG_H_
#define DEVICES_CFG_H_

#define NUM_OF_DEVICES      3
#define MAX_OPS_PER_DEV     3

#define INIT_FUN_INDEX		0
#define OP_2_INDEX			INIT_FUN_INDEX+1

#define DEV_CONST	0x07
#define OPER_CONST	0x07

typedef enum
{
	LED_0,
	LED_1,
	LED_2
} Device_Codes;

typedef enum
{
	LED_OFF_OP=OP_2_INDEX,
	LED_ON_OP,
	LED_TOGGLE_OP
} Operation_Codes;

#endif /* DEVICES_CFG_H_ */