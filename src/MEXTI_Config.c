/*
 * MEXTI_Config.
 *
 *  Created on: 24-04-2024
 *  Author: Mahmoud Essam
 *
 */




/*****************LIB*************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"


/****************MCAL************************/
#include "../include/MCAL/MEXTI/MEXTI_Config.h"
#include "../include/MCAL/MEXTI/MEXTI_Interface.h"
#include "../include/MCAL/MEXTI/MEXTI_Private.h"


MEXTI_Configurations  MEXTI_Config[MEXTI_NUMBER] =
{
		{
				MEXTI_LINE2	,
				MEXTI_PORTB ,
				MEXTI_RISING_EDGE ,
				MEXTI_ENABLED
		}
		,
		{
				MEXTI_LINE0	,
				MEXTI_PORTB ,
				MEXTI_RISING_EDGE ,
				MEXTI_ENABLED
		}


//
//		,
//		{
//				MEXTI_LINE10	,
//				MEXTI_PORTA ,
//				MEXTI_FALLING_EDGE ,
//				MEXTI_ENABLED
//		}
//		,
//		{
//				MEXTI_LINE5	,
//				MEXTI_PORTB ,
//				MEXTI_FALLING_EDGE ,
//				MEXTI_ENABLED
//		}
//		,
//		{
//				MEXTI_LINE10	,
//				MEXTI_PORTB ,
//				MEXTI_FALLING_EDGE ,
//				MEXTI_ENABLED
//		}
};



