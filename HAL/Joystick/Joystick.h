/*
 * Joystick.h
 *
 *  Created on: 25 May 2023
 *      Author: saids
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define Max_Joystick_Value  ((33*4096)/34)			//this is the max value that can be calculated by adc
													// input voltage =3.3 volts ,, reference voltage =3.4,, and adc is 12 bits so 2^12 =4096
													//where adc value = (input voltage/ref voltage)*4096

#define Mid_Joystick_Value (Max_Joystick_Value/2)		// this the middle point or the initial point

#define Forward	   1
#define Right      2
#define Left       3
#define Backward   4
#define Stop	   0


#endif /* JOYSTICK_H_ */
