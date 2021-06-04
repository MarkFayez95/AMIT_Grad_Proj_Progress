/*
 * Devices.h
 *
 * Created: 29/05/2021 10:43:15 PM
 *  Author: Mark Fayez
 */ 
#ifndef DEVICES_H_
#define DEVICES_H_

void Devices_Init(void);
uint8 Dev_Op_Check_Valid(uint8 Req_Device, uint8 Req_Operation);
void Device_Apply_Request(uint8 Req_Device, uint8 Req_Operation);

#endif /* DEVICES_H_ */