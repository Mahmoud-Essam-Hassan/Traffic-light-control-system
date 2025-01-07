/*
 * HLED_Program.

 *
 *  Created on: Jan 3, 2025
 *      Author: Mahmoud Essam
 */

#ifndef HPB_INTERFACE_H_
#define HPB_INTERFACE_H_

#define PB_PORT				GPIO_PORTB
#define PED_A_PB			GPIO_PIN0
#define PED_B_PB			GPIO_PIN2

/*
 * Used to Initialize Pedestrian Traffic Light Push Buttons Pins
 * Parameter inputs: None
 * 	Parameter Out: None
 * 	Return: void
 */
void HPb_Init(void);



#endif /* HPB_INTERFACE_H_ */
