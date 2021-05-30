/*
 * Smart_Home.h
 *
 * Created: 30/05/2021 04:07:15 PM
 *  Author: Mark Fayez
 */ 

#ifndef SMART_HOME_H_
#define SMART_HOME_H_

#define CONTROL_ECU		0xAA
#define ACTUATOR_ECU	0xBB

#define ECU_ROLE	CONTROL_ECU

#include "Comm_Bridge.h"
#if ECU_ROLE == ACTUATOR_ECU
#include "Devices.h"
#endif /* ECU_ROLE */






#endif /* SMART_HOME_H_ */