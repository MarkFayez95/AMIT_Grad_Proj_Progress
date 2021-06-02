/*
 * Smart_Home.h
 *
 * Created: 30/05/2021 04:07:15 PM
 *  Author: Mark Fayez
 */ 

#ifndef SMART_HOME_H_
#define SMART_HOME_H_

typedef enum {
	CONTROL_ECU=0xAA,
	ACTUATOR_ECU
} Roles;

#define ECU_ROLE	ACTUATOR_ECU

#include "Comm_Bridge.h"
#if ECU_ROLE == ACTUATOR_ECU
	#include "Devices.h"
#endif /* ECU_ROLE */

void Smart_Home_Init(void);
void Smart_Home_Run(void);

#if ECU_ROLE == CONTROL_ECU
static void Smart_Home_User_Selection(void);
static void Smart_Home_Process_N_Respond(void);
#elif ECU_ROLE == ACTUATOR_ECU
static void Smart_Home_Read_N_Decode(void);
static void Smart_Home_Process_N_Respond(void);
#endif /* ECU_ROLE */



#endif /* SMART_HOME_H_ */