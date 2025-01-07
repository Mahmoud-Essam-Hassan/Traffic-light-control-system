/*
 * HPB_Program.
 *
 *  Created on: Jan 3, 2025
 *      Author: Mahmoud Essam
 */

/************************************************************************/
/*							FILES INCLUSIONS							*/
/************************************************************************/
/*******************************LIB**************************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
/*******************************MCAL*************************************/
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
/*******************************HAL*************************************/
#include "../include/HAL/HPB/HPB_Interface.h"
/**************************Functions Definitions***********************/


/*
 * Used to Initialize Pedestrian Traffic Light Push Buttons Pins
 * Parameter inputs: None
 * 	Parameter Out: None
 * 	Return: void
 */
void HPb_Init(void)
{
	MGPIO_voidSetPinMode(PB_PORT,PED_A_PB,GPIO_INPUT);
	MGPIO_voidSetPinInputMode(PB_PORT,PED_A_PB,GPIO_PULLDOWN);

	MGPIO_voidSetPinMode(PB_PORT,PED_B_PB,GPIO_INPUT);
	MGPIO_voidSetPinInputMode(PB_PORT,PED_B_PB,GPIO_PULLDOWN);
}

