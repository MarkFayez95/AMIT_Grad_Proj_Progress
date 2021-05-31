/*
 * Smart_Home_CTRL_Test.c
 *
 * Created: 31/05/2021 2:51:19 PM
 * Author : Mark Fayez
 */ 

#include "Smart_Home.h"


int main(void)
{
    Smart_Home_Init();
    while (1) 
    {
		Smart_Home_Run();
    }
}

