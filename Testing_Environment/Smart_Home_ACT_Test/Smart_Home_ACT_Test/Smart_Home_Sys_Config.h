/*
 * Smart_Home_Sys_Config.h
 *
 * Created: 02/06/2021 08:58:15 PM
 *  Author: Mark Fayez
 */ 

#ifndef SMART_HOME_SYS_CONFIG_H_
#define SMART_HOME_SYS_CONFIG_H_

#include "System_Config_Options.h"

/** Main ECU configuration **/
#define ECU_ROLE	ACTUATOR_ECU

/** Communication Bridge Module configurations **/
#define COMMAND_BYTE_LENGTH     1

    // Bluetooth Driver configurations //
    #define BT_PUID_BYTE	0
    #define BT_DATA_BYTE	1
    #if COMMAND_BYTE_LENGTH == 2
        #define BT_DATA_BYTE_2		2
    #endif /* COMMAND_BYTE_LENGTH */

    #ifndef PUID_DB_H_
        #define VALID_PUID    0xA8 // static pre-defined Pin User ID for security communicating with peer
        #define ECU_PUID      0xAB
        #define VALID_ID      0x0A
        #define INVALID_ID    0x0C
    #endif /* PUID_DB_H_ */

    #define BT_END_PACKET_CODE 0x0D

        // UART Driver Configurations //
        #define Baud_Rate_Hundred 384
        #define UART_Presc	16
        #define UART_Clk_Sor 160000

    /****************************************************/
    /*##################################################*/
    /****************************************************/

    // CMD_Bus Driver configurations //
    #define CMD_DATA_BYTE	0

    #if COMMAND_BYTE_LENGTH == 1
        #define REQ_DEV_SHIFT_MASK	4
        #define REQ_OP_MASK			0x0F
    #elif COMMAND_BYTE_LENGTH == 2
        #define CMD_DATA_BYTE_2		1
    #endif /* COMMAND_BYTE_LENGTH */

    #define CMD_FAILED_TRANS_REPEAT_DELAY_MS    30
    #define CMD_SEND_REQ_RECEIVE_ACK_DELAY_MS   2000

        // SPI Driver Configurations //
        #if ECU_ROLE == CONTROL_ECU
            #define SPI_ROLE            SPI_MASTER
            #define CMD_BUS_DEV_ID      0xA0
            #define CMD_BUS_PEER_ID     0xB0
        #elif ECU_ROLE == ACTUATOR_ECU
            #define SPI_ROLE            SPI_SLAVE
            #define CMD_BUS_DEV_ID      0xB0
            #define CMD_BUS_PEER_ID     0xA0
        #endif /* ECU_ROLE */

/** Devices Module configurations **/
#define NUM_OF_DEVICES      3
#define MAX_OPS_PER_DEV     3

#define INIT_FUN_INDEX		0
#define OP_2_INDEX			INIT_FUN_INDEX+1

#define DEV_CONST	0x07
#define OPER_CONST	0x07

#endif /* SMART_HOME_SYS_CONFIG_H_ */