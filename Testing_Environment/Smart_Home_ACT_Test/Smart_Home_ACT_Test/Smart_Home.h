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


void Smart_Home_Init(void);
void Smart_Home_Run(void);


static void Smart_Home_User_Selection(void);

static void Smart_Home_Read_N_Decode(void);

static void Smart_Home_Process_N_Respond(void);

#endif /* SMART_HOME_H_ */