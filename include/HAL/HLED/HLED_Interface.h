/*
 * HLED_Program.

 *
 *  Created on: Jan 3, 2025
 *      Author: Mahmoud Essam
 */
#ifndef HLED_INTERFACE_H
#define HLED_INERFACE_H

// Traffic Light name Macros
#define CAR_TL_A				1
#define CAR_TL_B				2
#define PED_TL_A				3
#define PED_TL_B				4
// Traffic Lights Colors Macros
#define RED_L					1
#define YELLOW_L				2
#define GREEN_L					3
#define Blinking_GREEN_L		4

/**********************FUNCTIONS PROTOTYPES*************************/

/*
 * Used to Initialize Traffic Light Led Pins
 * Parameter inputs: None
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_Init(void);

/*
 * Used to turn ON a specific Car Traffic Light and turn off the rest of the lights
 * Parameter inputs:
 * 					copy_u8TrafficLight: Traffic light name
 * 					copy_u8Led: Light Color
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_CarTrafficLightON(u8 copy_u8TrafficLight, u8 copy_u8LED);
/*
* Used to turn OFF a specific Car Traffic Light and turn off the rest of the lights
* Parameter inputs:
* 					copy_u8TrafficLight: Traffic light name
* 					copy_u8Led: Light Color
* 	Parameter Out: None
* 	Return: void
*/
void HLED_CarTrafficLightOFF(u8 copy_u8TrafficLight, u8 copy_u8LED);
/*
 * Used to turn ON a specific Ped Traffic Light and turn off the rest of the lights
 * Parameter inputs:
 * 					copy_u8TrafficLight: Traffic light name
 * 					copy_u8Led: Light Color
 * 	Parameter Out: None
 * 	Return: void
 */
void HLED_PedTrafficLightON(u8 copy_u8TrafficLight, u8 copy_u8LED);
/*
* Used to turn OFF a specific Ped Traffic Light and turn off the rest of the lights
* Parameter inputs:
* 					copy_u8TrafficLight: Traffic light name
* 					copy_u8Led: Light Color
* 	Parameter Out: None
* 	Return: void
*/
void HLED_PedTrafficLightOFF(u8 copy_u8TrafficLight, u8 copy_u8LED);

#endif
