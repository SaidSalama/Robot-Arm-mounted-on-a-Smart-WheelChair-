/*
 * Motors.h
 *
 *  Created on: Nov 2, 2022
 *      Author: Said Salama
 */
#include "STD_TYPES.h"
#ifndef MOTORS_H_
#define MOTORS_H_

#define Left_Motor  0   //PA0 FOR TIM2->CH1
#define Right_Motor 1   //PA1 FOR TIM2->CH2

#define Left_Motor_Port  GPIOA
#define Right_Motor_Port  GPIOA

#define Left_Motor__En_Port  GPIOB
#define Right_Motor_En_Port  GPIOB

#define Left_Motor__En_Pin  0
#define Right_Motor_En_Pin  1


/* Motors speed */
#define Max_Speed        1
#define Half_Speed       2
#define One_Third_Speed  3
#define Quarter_speed    4

#define ACTUAL_SPEED	Half_Speed			//you can change the speed by changing the value of this macro


void Init_Motors();
void Set_Motors_DutyCycle(u8 speed);
void Stop();
void Forward(u8 speed);
void Turn_Left(u8 speed);
void Turn_Right(u8 speed);

#endif /* MOTORS_H_ */
