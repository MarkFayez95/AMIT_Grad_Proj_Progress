/*
 * Smart_Home_Sys_Config.h
 * 
 * Created: 02/06/2021 08:58:15 PM
 *  Author: Mark Fayez
 */ 

#ifndef SMART_HOME_SYS_CONFIG_H_
#define SMART_HOME_SYS_CONFIG_H_

#include "System_Config_Options.h"
#include "System_DTypes.h"

/** Main ECU configuration **/
#define ECU_ROLE	ACTUATOR_ECU
#define NUM_OF_RESYNC_HANDSHAKES    8

/** Status Follow Up configurations **/
#define LCD_DISP_DELAY_MS    250

/** Communication Bridge Module configurations **/
#define COMMAND_BYTE_LENGTH     1
#define COMMAND_PACKET_HEADER_TAIL_LENGTH 2
#define MAX_FAILED_COMM_BRI_HANDSHAKES    5
#define MAX_FAILED_COMM_BRI_TRANSMISSIONS   10
#define PRIOR_RE_SYNC_HANDSHAKES_DELAY_MS   50

    // Bluetooth Driver configurations //
    #define BT_PUID_BYTE	0
    #define BT_DATA_BYTE	1
    #if COMMAND_BYTE_LENGTH == 2
        #define BT_DATA_BYTE_2		2
    #endif /* COMMAND_BYTE_LENGTH */


    #define VALID_PUID    0x37 // static pre-defined Pin User ID for security communicating with peer
    #define ECU_PUID      0x40
    #define VALID_ID      0x0A
    #define INVALID_ID    0x0C

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
        #define RESPONSE_DATA_BYTE  1
    #elif COMMAND_BYTE_LENGTH == 2
        #define CMD_DATA_BYTE_2		1
        #define RESPONSE_DATA_BYTE  2
    #endif /* COMMAND_BYTE_LENGTH */

    #define CMD_FAILED_TRANS_REPEAT_DELAY_MS        30
    #define CMD_FAILED_HANDSHAKE_REPEAT_DELAY_MS    10
    #define CMD_SEND_REQ_RECEIVE_ACK_DELAY_MS       1800
    #define CMD_SEND_REQ_SYNC_DELAY_MS              500

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

        #define MASTER_SS_SET_DELAY_MS    30

        #if SPI_ROLE == SPI_MASTER
            #define SPI_PORT     DIO_PORTB
            #define SPI_SS_PIN   DIO_PIN_4
            #define SPI_MOSI_PIN DIO_PIN_5
            #define SPI_MISO_PIN DIO_PIN_6
            #define SPI_CLK_PIN  DIO_PIN_7
        #elif SPI_ROLE == SPI_SLAVE
            #define SPI_PORT     DIO_PORTB
            #define SPI_SS_PIN   DIO_PIN_4
            #define SPI_MOSI_PIN DIO_PIN_5
            #define SPI_MISO_PIN DIO_PIN_6
            #define SPI_CLK_PIN  DIO_PIN_7
        #endif

/** Devices Manager Application Module configurations **/
#define NUM_OF_DEVICES      3
#define MAX_OPS_PER_DEV     3

#define INIT_FUN_INDEX		0

#define DEV_CONST	0x03
#define OPER_CONST	0x01

#endif /* SMART_HOME_SYS_CONFIG_H_ */