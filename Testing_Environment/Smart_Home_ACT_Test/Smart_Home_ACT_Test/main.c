/*
 * Smart_Home_ACT_Test.c
 *
 * Created: 31/05/2021 3:09:57 PM
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

