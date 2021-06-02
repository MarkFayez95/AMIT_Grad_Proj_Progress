/*
 * Develop_APP_Layer.c
 *
 * Created: 30/05/2021 5:26:40 PM
 * Author : Mark Fayez
 */ 

//#include "Smart_Home.h"
#include "Status_FollowUp.h"

int main(void)
{
	Status_FollowUp_Init();
	
	Status_Disp_LCD(LCD_ROW_TXT_CONTROL_SYSTEM,LCD_ROW_TXT_STARTING);
	
	//Smart_Home_Init();
    while (1) 
    {
		//Smart_Home_Run();
    }
}

