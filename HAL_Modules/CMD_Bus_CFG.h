/*
 * CMD_Bus_CFG.h
 *
 * Created: 27/05/2021 08:39:20 PM
 *  Author: Mark Fayez
 */ 
#ifndef CMD_BUS_CFG_H_
#define CMD_BUS_CFG_H_

#ifndef ECU_ROLE
    #define ECU_ROLE    CONTROL_ECU
#endif

#if ECU_ROLE == CONTROL_ECU
    #define SPI_ROLE SPI_MASTER
    #define CMD_BUS_DEV_ID 0xA0
    #define CMD_BUS_PEER_ID 0xB0
#elif ECU_ROLE == ACTUATOR_ECU
    #define SPI_ROLE SPI_SLAVE
    #define CMD_BUS_DEV_ID 0xB0
    #define CMD_BUS_PEER_ID 0xA0
#endif /* ECU_ROLE */

#include "SPI.h"

#endif /* CMD_BUS_CFG_H_ */
