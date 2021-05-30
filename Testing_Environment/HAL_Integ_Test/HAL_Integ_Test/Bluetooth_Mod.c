/*
 * Bluetooth_Mod.c
 *
 * Created: 27/05/2021 08:40:30 PM
 *  Author: Mark Fayez
 */ 

 #include "Bluetooth_Mod.h"

void Bluetooth_Mod_Init(void)
{
    UART_Init();
    DIO_SetPinDir(BT_STAT_PIN_PORT, BT_STAT_PIN_PIN, DIO_PIN_INPUT);
}
uint8 Bluetooth_Mod_Ch_Pair(void)
{
	uint8 Pairing_State = BT_NOT_PAIRED;
	DIO_ReadPinValue(BT_STAT_PIN_PORT, BT_STAT_PIN_PIN, &Pairing_State);
    return Pairing_State;
}
void Bluetooth_Mod_Tx(uint8 Data_Byte)
{
    while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
    UART_Tx(Data_Byte);
}
uint8 Bluetooth_Mod_Rx(void)
{
    while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
    return UART_Rx();
}
void Bluetooth_Mod_Seq_Tx(uint8* Data_Stream)
{
    while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
    UART_TxString(Data_Stream);
}
void Bluetooth_Mod_Seq_Rx(uint8* Data_Stream)
{
    while(Bluetooth_Mod_Ch_Pair() == BT_NOT_PAIRED);
    UART_RxString(Data_Stream);
}