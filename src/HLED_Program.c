/*
 * HLED_Program.

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
#include "../include/LIB/ARM_Delay.h"
/*******************************MCAL*************************************/
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
/*******************************HAL*************************************/
#include "../include/HAL/HLED/HLED_Private.h"
#include "../include/HAL/HLED/HLED_Interface.h"

/**************************Functions Definitions***********************/

/*
 * Used to Initialize Traffic Light Led Pins
 * Parameter inputs: None
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_Init(void)
{
	// Initialize LED Pins Output Mode
	for(u8 LedPinNum = CAR_A_RED ; LedPinNum <= PED_B_GREEN ; LedPinNum++)
	{
		MGPIO_voidSetPinMode(LED_PORT,LedPinNum,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(LED_PORT,LedPinNum,GPIO_PUSH_PULL,GPIO_LOW_SPEED);
		MGPIO_voidSetPinValue(LED_PORT,LedPinNum,GPIO_PIN_LOW);
	}
}

/*
 * Used to turn ON a specific Car Traffic Light and turn off the rest of the lights
 * Parameter inputs:
 * 					copy_u8TrafficLight: Traffic light name
 * 					copy_u8Led: Light Color
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_CarTrafficLightON(u8 copy_u8TrafficLight, u8 copy_u8LED)
{
	// Check Car Traffic Light Name
	if(copy_u8TrafficLight == CAR_TL_A)
	{
		// Select Led Color which is ON
		switch(copy_u8LED)
		{
		case RED_L:
			// Set Red led of Traffic car A High and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_YELLOW,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_GREEN,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_RED,GPIO_PIN_HIGH);
			break;
		case YELLOW_L:
			// Set Yellow led of Traffic car A High and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_GREEN,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_RED,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_YELLOW,GPIO_PIN_HIGH);
			break;
		case GREEN_L:
			// Set Green led of Traffic car A High and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_RED,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_YELLOW,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_GREEN,GPIO_PIN_HIGH);
			break;
		default:
			break;
		}

	}
	// Check Car Traffic Light Name
	else if(copy_u8TrafficLight == CAR_TL_B)
	{
		// Select Led Color which is ON
		switch(copy_u8LED)
		{
		case RED_L:
			// Set Red led of Traffic car B High and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_YELLOW,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_GREEN,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_RED,GPIO_PIN_HIGH);
			break;
		case YELLOW_L:
			// Set Yellow led of Traffic car B High and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_GREEN,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_RED,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_YELLOW,GPIO_PIN_HIGH);
			break;
		case GREEN_L:
			// Set Green led of Traffic car B High and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_RED,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_YELLOW,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_GREEN,GPIO_PIN_HIGH);
			break;
		default:
			break;
		}
	}
	else
	{
		//do nothing
	}
}
/*
 * Used to turn OFF a specific Car Traffic Light and turn off the rest of the lights
 * Parameter inputs:
 * 					copy_u8TrafficLight: Traffic light name
 * 					copy_u8Led: Light Color
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_CarTrafficLightOFF(u8 copy_u8TrafficLight, u8 copy_u8LED)
{
	// Check Car Traffic Light Name
	if(copy_u8TrafficLight == CAR_TL_A)
	{
		// Select Led Color which is OFF
		switch(copy_u8LED)
		{
		case RED_L:
			// Turn OFF Red led of Traffic car A
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_RED,GPIO_PIN_LOW);
			break;
		case YELLOW_L:
			// Turn OFF Yellow led of Traffic car A
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_YELLOW,GPIO_PIN_LOW);
			break;
		case GREEN_L:
			// Turn OFF Green led of Traffic car A
			MGPIO_voidSetPinValue(LED_PORT,CAR_A_GREEN,GPIO_PIN_LOW);
			break;
		default:
			break;
		}

	}
	// Check Car Traffic Light Name
	else if(copy_u8TrafficLight == CAR_TL_B)
	{
		// Select Led Color which is OFF
		switch(copy_u8LED)
		{
		case RED_L:
			// Turn OFF Red led of Traffic car B
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_RED,GPIO_PIN_LOW);
			break;
		case YELLOW_L:
			// Turn OFF Yellow led of Traffic car B
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_YELLOW,GPIO_PIN_LOW);
			break;
		case GREEN_L:
			// Turn OFF Green led of Traffic car B
			MGPIO_voidSetPinValue(LED_PORT,CAR_B_GREEN,GPIO_PIN_LOW);
			break;
		default:
			break;
		}
	}
	else
	{
		//do nothing
	}
}
/*
 * Used to turn ON a specific Ped Traffic Light and turn off the rest of the lights
 * Parameter inputs:
 * 					copy_u8TrafficLight: Traffic light name
 * 					copy_u8Led: Light Color
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_PedTrafficLightON(u8 copy_u8TrafficLight, u8 copy_u8LED)
{
	// Check the Ped Traffic Light Name
	if(copy_u8TrafficLight == PED_TL_A)
	{
		// Check Led Color which is ON
		if(copy_u8LED == RED_L)
		{
			// Set Red led of Traffic Ped A ON and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,PED_A_GREEN,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,PED_A_RED,GPIO_PIN_HIGH);
		}
		else if(copy_u8LED == GREEN_L)
		{
			// Set Green led of Traffic Ped A ON and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,PED_A_RED,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,PED_A_GREEN,GPIO_PIN_HIGH);
		}
		else if(copy_u8LED == Blinking_GREEN_L)
		{
			MGPIO_voidSetPinValue(LED_PORT,PED_A_RED,GPIO_PIN_LOW);
			MGPIO_voidTogglePin(LED_PORT,PED_A_GREEN);
//			Delay_MS(200);
//			MGPIO_voidTogglePin(LED_PORT,PED_A_GREEN);
//			Delay_MS(200);
		}
		else
		{
			//do nothing
		}

	}
	// Check the Ped Traffic Light Name
	else if(copy_u8TrafficLight == PED_TL_B)
	{
		// Check Led Color which is ON
		if(copy_u8LED == RED_L)
		{
			// Set Red led of Traffic Ped B ON and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,PED_B_GREEN,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,PED_B_RED,GPIO_PIN_HIGH);
		}
		else if(copy_u8LED == GREEN_L)
		{
			// Set Green led of Traffic Ped B ON and turn off the rest
			MGPIO_voidSetPinValue(LED_PORT,PED_B_RED,GPIO_PIN_LOW);
			MGPIO_voidSetPinValue(LED_PORT,PED_B_GREEN,GPIO_PIN_HIGH);
		}
		else if(copy_u8LED == Blinking_GREEN_L)
		{
			MGPIO_voidSetPinValue(LED_PORT,PED_B_RED,GPIO_PIN_LOW);
			MGPIO_voidTogglePin(LED_PORT,PED_B_GREEN);
//			Delay_MS(200);
//			MGPIO_voidTogglePin(LED_PORT,PED_B_GREEN);
//			Delay_MS(200);
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		//do nothing
	}
}
/*
 * Used to turn OFF a specific Ped Traffic Light and turn off the rest of the lights
 * Parameter inputs:
 * 					copy_u8TrafficLight: Traffic light name
 * 					copy_u8Led: Light Color
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_PedTrafficLightOFF(u8 copy_u8TrafficLight, u8 copy_u8LED)
{
	// Check the Ped Traffic Light Name
	if(copy_u8TrafficLight == PED_TL_A)
	{
		// Check Led Color which is off
		if(copy_u8LED == RED_L)
		{
			// Turn Off Red Led
			MGPIO_voidSetPinValue(LED_PORT,PED_A_RED,GPIO_PIN_LOW);
		}
		else if(copy_u8LED == GREEN_L)
		{
			// Turn Off Green Led
			MGPIO_voidSetPinValue(LED_PORT,PED_A_GREEN,GPIO_PIN_LOW);
		}
		else
		{
			//do nothing
		}

	}
	// Check the Ped Traffic Light Name
	else if(copy_u8TrafficLight == PED_TL_B)
	{
		// Check Led Color which is off
		if(copy_u8LED == RED_L)
		{
			// Turn Off Red Led
			MGPIO_voidSetPinValue(LED_PORT,PED_B_RED,GPIO_PIN_LOW);
		}
		else if(copy_u8LED == GREEN_L)
		{
			// Turn Off Green Led
			MGPIO_voidSetPinValue(LED_PORT,PED_B_GREEN,GPIO_PIN_LOW);
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		//do nothing
	}
}



