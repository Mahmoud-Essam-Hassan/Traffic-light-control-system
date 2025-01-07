/*
 * MAIN_Program.
 *
 *  Created on: Jan 3, 2025
 *      Author: Mahmoud Essam
 */


/***********************************Traffic Task*******************************/


/************************************************************************/
/*							FILES INCLUSIONS							*/
/************************************************************************/
/***********************LIB*************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/ARM_Delay.h"

/************************MCAL***********************/
#include "../include/MCAL/MRCC/MRCC_Interface.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MEXTI/MEXTI_Interface.h"
#include "../include/MCAL/MNVIC/MNVIC_Interface.h"
#include "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"
/*************************HAL************************/
#include "../include/HAL/HLED/HLED_Interface.h"
#include "../include/HAL/HPB/HPB_Interface.h"
/************************************************************************/
/*							ENTRY POINT <main>							*/
/************************************************************************/

/* Initialize counters for Manage Time between States:
 * Counter: used for count each
 * */
static u8 Counter = 0;
static u8 PB_A_Counter = 0;
static u8 PB_B_Counter = 0;


// Initialize States Flag
u8 u8_State_1 = TRUE;
u8 u8_State_2_0 = FALSE;
u8 u8_State_2_1 = FALSE;
u8 u8_State_3 = FALSE;
u8 u8_State_4_0 = FALSE;
u8 u8_State_4_1 = FALSE;

// Traffic Light Handler for control timing between states
void TL_Handler(void);

// Pedestrian A Handler
void PED_Handler_A();
// Pedestrian B Handler
void PED_Handler_B();

// Initialize States
/*State1:
 * Car Traffic Light A LED: Red
 * Car Traffic Light B LED: Green
 * Pedestrian Traffic Light A LED: Green
 * Pedestrian Traffic Light B LED: Red
 * */
void State1 () {
	HLED_CarTrafficLightON(CAR_TL_A,RED_L);
	HLED_CarTrafficLightON(CAR_TL_B,GREEN_L);
	HLED_PedTrafficLightON(PED_TL_A,GREEN_L);
	HLED_PedTrafficLightON(PED_TL_B,RED_L);
}
/*State2_0:
 * Car Traffic Light A LED: Red
 * Car Traffic Light B LED: Yellow
 * Pedestrian Traffic Light A LED: Blinking Green LED
 * Pedestrian Traffic Light B LED: Red
 * */
void State2_0 () {//30
	HLED_CarTrafficLightON(CAR_TL_A,RED_L);
	HLED_CarTrafficLightON(CAR_TL_B,YELLOW_L);
	HLED_PedTrafficLightON(PED_TL_A,Blinking_GREEN_L);
	HLED_PedTrafficLightON(PED_TL_B,RED_L);
	Delay_MS(200);
}
/*State2_1:
 * Car Traffic Light A LED: Red
 * Car Traffic Light B LED: Yellow
 * Pedestrian Traffic Light A LED: Red
 * Pedestrian Traffic Light B LED: Red
 * */
void State2_1 () {
	HLED_CarTrafficLightON(CAR_TL_A,RED_L);
	HLED_CarTrafficLightON(CAR_TL_B,YELLOW_L);
	HLED_PedTrafficLightON(PED_TL_A,RED_L);
	HLED_PedTrafficLightON(PED_TL_B,RED_L);
}
/*State3:
 * Car Traffic Light A LED: Green
 * Car Traffic Light B LED: Red
 * Pedestrian Traffic Light A LED: Red
 * Pedestrian Traffic Light B LED: Green
 * */
void State3 () {
	HLED_CarTrafficLightON(CAR_TL_A,GREEN_L);
	HLED_CarTrafficLightON(CAR_TL_B,RED_L);
	HLED_PedTrafficLightON(PED_TL_A,RED_L);
	HLED_PedTrafficLightON(PED_TL_B,GREEN_L);
}
/*State4_0:
 * Car Traffic Light A LED: Yellow
 * Car Traffic Light B LED: Red
 * Pedestrian Traffic Light A LED: Red
 * Pedestrian Traffic Light B LED: Blinking Green LED
 * */
void State4_0 () {
	HLED_CarTrafficLightON(CAR_TL_A,YELLOW_L);
	HLED_CarTrafficLightON(CAR_TL_B,RED_L);
	HLED_PedTrafficLightON(PED_TL_A,RED_L);
	HLED_PedTrafficLightON(PED_TL_B,Blinking_GREEN_L);
	Delay_MS(200);
}
/*State4_1:
 * Car Traffic Light A LED: Yellow
 * Car Traffic Light B LED: Red
 * Pedestrian Traffic Light A LED: Red
 * Pedestrian Traffic Light B LED: Red
 * */
void State4_1 () {
	HLED_CarTrafficLightON(CAR_TL_A,YELLOW_L);
	HLED_CarTrafficLightON(CAR_TL_B,RED_L);
	HLED_PedTrafficLightON(PED_TL_A,RED_L);
	HLED_PedTrafficLightON(PED_TL_B,RED_L);
}

void main(void)
{
	//Initialize RCC to Enable HSI Clock
	MRCC_voidInit();
	// Enable Port A&B Clock
	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	// Enable System Configration
	MRCC_voidEnablePeripheral(RCC_APB2 , RCC_APB2_SYSCFG);

	// Initialize PUSH BUTTON A(PortB, Pin0), B(PortB, Pin2)
	HPb_Init();
	// Initialize LED A(PortA, Pin0-9)
	HLED_Init();

	// Initialize SYSTICK, Set Pre-scaler 8
	MSYSTICK_voidInit();
	// Initialize External Interrupt
	MEXTI_voidInit();

	// Set CallBack Function for Handler A
	MEXTI_voidSetCallBack(MEXTI_LINE0,PED_Handler_A);
	// Set CallBack Function for Handler B
	MEXTI_voidSetCallBack(MEXTI_LINE2,PED_Handler_B);

	// Enable Interrupt
	MNVIC_voidEnablePeripheralInterrupt(EXTI0_IRQ);
	MNVIC_voidEnablePeripheralInterrupt(EXTI2_IRQ);

	// Start SYSTICK Periodic Interval Count 1sec then invoke interrupt (TL_Handler)
	MSYSTICK_voidSetPeriodicInterval_ms(1000,TL_Handler);

	while(1)
	{
		// Check States of The Traffic Light
		if (u8_State_1 == TRUE)
		{
			// Call State1 Function
			State1();
		}
		else if(u8_State_2_0 == TRUE)
		{
			// Call State2_0 Function
			State2_0();
		}
		else if(u8_State_2_1 == TRUE)
		{
			// Call State2_1 Function
			State2_1();
		}
		else if(u8_State_3 == TRUE)
		{
			// Call State3 Function
			State3();
		}
		else if(u8_State_4_0 == TRUE)
		{
			// Call State4_0 Function
			State4_0();
		}
		else if(u8_State_4_1 == TRUE)
		{
			// Call State4_1 Function
			State4_1();
		}
		else{
			//do nothing
		}
	}


}

// Count Counter Flags to Manage Time of States and activate State flags
void TL_Handler(void)
{

	// Check For The Systick Timer = 30 Seconds
	if (Counter == 30)
	{
		// Make State2_0 Flag True and Other States Flag False
		u8_State_1 = FALSE;
		u8_State_2_0 = TRUE;
		u8_State_2_1 = FALSE;
		u8_State_3 = FALSE;
		u8_State_4_0 = FALSE;
		u8_State_4_1 = FALSE;
	}
	// Check For The Systick Timer = 35 Seconds
	else if(Counter ==35)
	{
		// Make State2_1 Flag True and Other States Flag False
		u8_State_1 = FALSE;
		u8_State_2_0 = FALSE;
		u8_State_2_1 = TRUE;
		u8_State_3 = FALSE;
		u8_State_4_0 = FALSE;
		u8_State_4_1 = FALSE;
	}
	// Check For The SYSTICK Timer = 40 Seconds
	else if (Counter == 40)
	{
		// Make State3 Flag True and Other States Flag False
		u8_State_1 = FALSE;
		u8_State_2_0 = FALSE;
		u8_State_2_1 = FALSE;
		u8_State_3 = TRUE;
		u8_State_4_0 = FALSE;
		u8_State_4_1 = FALSE;
	}
	// Check For The SYSTICK Timer = 70 Seconds
	else if (Counter == 70)
	{
		// Make State4_0 Flag True and Other States Flag False
		u8_State_1 = FALSE;
		u8_State_2_0 = FALSE;
		u8_State_2_1 = FALSE;
		u8_State_3 = FALSE;
		u8_State_4_0 = TRUE;
		u8_State_4_1 = FALSE;
	}
	// Check For The SYSTICK Timer = 75 Seconds
	else if (Counter == 75)
	{
		// Make State4_1 Flag True and Other States Flag False
		u8_State_1 = FALSE;
		u8_State_2_0 = FALSE;
		u8_State_2_1 = FALSE;
		u8_State_3 = FALSE;
		u8_State_4_0 = FALSE;
		u8_State_4_1 = TRUE;
	}

	// Check For The SYSTICK Timer = 80 Seconds
	else if (Counter == 80)
	{
		// Make State1 Flag True and Other States Flag False
		u8_State_1 = TRUE;
		u8_State_2_0 = FALSE;
		u8_State_2_1 = FALSE;
		u8_State_3 = FALSE;
		u8_State_4_0 = FALSE;
		u8_State_4_1 = FALSE;

		Counter = 0;
	}

	Counter++;
	PB_A_Counter++;
	PB_B_Counter++;
}

// Pedestrian A Handler that invoked when Push Button A Pressed to Handling the sequence of operation
void PED_Handler_A(void)
{
	/*
	 * Checking Last Pressed Time of PUSH BUTTON A  > 30 seconds
	 * Current state is state3 (to make sure that the Pedestrian Traffic A is Red)
	 */
	if(PB_A_Counter > 30 && u8_State_3 == TRUE)
	{
		/*Set State4_0 Flag It's Sequence:
		 * Car Traffic Light A LED: Yellow
		 * Car Traffic Light B LED: Red
		 * Pedestrian Traffic Light A LED: Red
		 * Pedestrian Traffic Light B LED: Blinking Green LED
		 * */

		u8_State_3 = FALSE;
		u8_State_4_0 = TRUE;
		// Set counter to 70 to move to state4_0
		Counter = 70;
		// Reset PUSH BUTTON A Counter
		PB_B_Counter=0;
	}
}

// Pedestrian B Handler that invoked when Push Button B Pressed to Handling the sequence of operation
void PED_Handler_B(void)
{
	/*
	 * Checking Last Pressed Time of PUSH BUTTON B  > 30 seconds
	 * Current state is state1 (to make sure that the Pedestrian Traffic B is Red)
	 */
	if(PB_B_Counter > 30 && u8_State_1 == TRUE)
	{
		/*Set State2_0 Flag It's Sequence:
		 * Car Traffic Light A LED: Red
		 * Car Traffic Light B LED: Yellow
		 * Pedestrian Traffic Light A LED: Blinking Green LED
		 * Pedestrian Traffic Light B LED: Red
		 * */

		u8_State_1 = FALSE;
		u8_State_2_0 = TRUE;
		// Set counter to 30 to move to state2_0
		Counter = 30;
		// Reset PUSH BUTTON B Counter
		PB_B_Counter=0;
	}
}

