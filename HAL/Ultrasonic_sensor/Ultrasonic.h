/*
 * Ultrasonic..h
 *
 *  Created on: Oct 18, 2022
 *      Author: Said Salama
 */

#include "BIT_MATH.h"
#include "Std_Types.h"

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
/* 1st Ultrasonic sensor*/
#define Echo_Port_1  GPIOA
#define Trig_Port_1   GPIOB
#define Trig_Pin_1   9					//PB9 TRIG PIN
#define Echo_Pin_1   8					//PA8 TIM1->CH1 ECHON PIN

/* 2nd Ultrasonic sensor*/
#define Echo_Port_2  GPIOA
#define Trig_Port_2   GPIOB
#define Trig_Pin_2   8
#define Echo_Pin_2   9

u32 Read_Ultrasonic_1();
void All_Ultrasonic_Trigger();

#endif /* ULTRASONIC_H_ */
