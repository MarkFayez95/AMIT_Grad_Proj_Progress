/*
 * Smart_Home.h
 *
 * Created: 30/05/2021 04:07:15 PM
 *  Author: Mark Fayez
 */ 

#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#include "Comm_Bridge.h"
#include "Devices.h"

// The group of tasks that are carried out by each ECU in the system containers.

// Initialization Task group.
// In Control ECU: Initialize the Status_FollowUP application, then the Communication Bridge/manager
// In Actuator ECU: Initialize the Status_FollowUP application as well, then the Device manager application, then finally initializes the communication Bridge/manager.
// Choosing between both roles is done through the Smart_Home_Sys_Config file.
void Smart_Home_Init(void);

// Run System Task Group.
// In Control ECU: Clear Previous user selection, then if system recorded an out of sync flag then perform re-handshake, then request selection from user and check validity of the PUID, then send it to Actuator and receive its response, then cascade it to the bluetooth device.
void Smart_Home_Run(void);

// A controller ECU task that involves the following actions:
// Read the user PUID (PinUserID) Byte and confirm it's an authorized user for the system.
static void Smart_Home_User_Selection(void);

static void Smart_Home_Read_N_Decode(void);

static void Smart_Home_Process_N_Respond(void);

void Smart_Home_Clear_User_Selection(void);

#endif /* SMART_HOME_H_ */