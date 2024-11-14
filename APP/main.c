/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "Motors.h"
#include "EXTI_interface.h"
#include "joystick.h"
#include "Ultrasonic.h"
#include "../Robot Arm/Robot_arm.h"


  extern u8 mode;					//this variable is changed in the external interrupt handler to set the mode of operation
  u8 Direction;						//this variable is used to store the direction returned by the joystick or TTL
  u32 Distance;						//the distance returned by the Ultrasonic sensor
void main(void)
{

  RCC_Init();
  Init_Motors();
  Init_TTL();
  Init_Joystick();
  Robot_Arm_Communication_Init();
  All_Ultrasonic_Init();
  Init_External_Interrupts();
  while (1)
  {
	  /*in joystick mode we first read the distance between the wheelchair and any obstacle like in any other mode
	   * if the distance is greater than 50 cm the user updates the direction and speed of the wheelchair
	   * normally without any problem
	   * but if the distance is below 50 cm it means there is an obstacle in front of the wheelchair
	   * and in this case we prevent the user from moving in the forward direction by getting the direction
	   * the user wants from the joystick and only update the speed if the direction is not forward
	   * */
	  /*In other modes a python program is used to determine the direction of motion then sends the direction to the TTL*/
	  switch(mode)
	  {
	  	  case JOYSTICK_Mode:
	  		  	  	  Distance=Ultrasonic_Set_Distance();
	  				  if(Distance>50)
	  				  {
	  					  Motors_Update_Speed_Direction();

	  				  }
	  				  else if (Distance<50)				//this method is used to prevent the user from hitting any obstacle at a distance of 50 cm
	  				  {									//by not allowing the wheelchair to move to the forward direction

	  						  Direction=Joystick_Set_Direction();
							  if(Direction!=Forward)
							  {
								  Motors_Update_Speed_Direction();
							  }
							  else
							  {
								  Motors_Stop();
							  }

	  				  }
	  				  break;

	  	  case EYE_Mode:
	  		  	  	  Distance=Ultrasonic_Set_Distance();
	  		  	  	  if(Distance>50)
	  		  	  	  {
	  		  	  		  	  Direction=Read_TTL();
							  if(Direction==Right)
							  {
								  Motors_Turn_Right(ACTUAL_SPEED);
							  }
							  else if(Direction==Left)
							  {
								  Motors_Turn_Left(ACTUAL_SPEED);
							  }
							  else if(Direction==Forward)
							  {
								  Motors_Forward(ACTUAL_SPEED);
							  }
							  else if(Direction==Stop)
							  {
								  Motors_Stop();
							  }
							  else if (Direction == Robot_Arm_Open)
							  {
								  Robot_Arm_SendCommand(Robot_Arm_Open);
							  }
							  else if (Direction == Robot_Arm_Close)
							  {
								  Robot_Arm_SendCommand(Robot_Arm_Close);
							  }
							  else if (Direction == Robot_Arm_Getmedicine)
							  {
								  Robot_Arm_SendCommand(Robot_Arm_Getmedicine);
							  }

	  		  	  	  }
	  		  	  	  else if (Distance<50)
	  		  	  	  {
	  		  	  		  Direction=Read_TTL();
						  if(Direction==Right)
						  {
							  Motors_Turn_Right(ACTUAL_SPEED);
						  }
						  else if(Direction==Left)
						  {
							  Motors_Turn_Left(ACTUAL_SPEED);
						  }
						  else if(Direction==Forward)
						  {
							  Motors_Stop();
						  }
						  else if(Direction==Stop)
						  {
							  Motors_Stop();
						  }
						  else if (Direction == Robot_Arm_Open)
						  {
							  Robot_Arm_SendCommand(Robot_Arm_Open);
						  }
						  else if (Direction == Robot_Arm_Close)
						  {
							  Robot_Arm_SendCommand(Robot_Arm_Close);
						  }
						  else if (Direction == Robot_Arm_Getmedicine)
						  {
							  Robot_Arm_SendCommand(Robot_Arm_Getmedicine);
						  }
	  		  	  	  }
					break;
	  	  case BCI_Mode:
	  		  Distance=Ultrasonic_Set_Distance();
			  if(Distance>50)
			  {
					  Direction=Read_TTL();
					  if(Direction==Right)
					  {
						  Motors_Turn_Right(ACTUAL_SPEED);
					  }
					  else if(Direction==Left)
					  {
						  Motors_Turn_Left(ACTUAL_SPEED);
					  }
					  else if(Direction==Forward)
					  {
						  Motors_Forward(ACTUAL_SPEED);
					  }
					  else if(Direction==Stop)
					  {
						  Motors_Stop();
					  }
					  else if (Direction == Robot_Arm_Open)
					  {
						  Robot_Arm_SendCommand(Robot_Arm_Open);
					  }
					  else if (Direction == Robot_Arm_Close)
					  {
						  Robot_Arm_SendCommand(Robot_Arm_Close);
					  }
					  else if (Direction == Robot_Arm_Getmedicine)
					  {
						  Robot_Arm_SendCommand(Robot_Arm_Getmedicine);
					  }
			  }
			  else if (Distance<50)
			  {
				  Direction=Read_TTL();
				  if(Direction==Right)
				  {
					  Motors_Turn_Right(ACTUAL_SPEED);
				  }
				  else if(Direction==Left)
				  {
					  Motors_Turn_Left(ACTUAL_SPEED);
				  }
				  else if(Direction==Forward)
				  {
					  Motors_Stop();
				  }
				  else if(Direction==Stop)
				  {
					  Motors_Stop();
				  }
				  else if (Direction == Robot_Arm_Open)
				  {
					  Robot_Arm_SendCommand(Robot_Arm_Open);
				  }
				  else if (Direction == Robot_Arm_Close)
				  {
					  Robot_Arm_SendCommand(Robot_Arm_Close);
				  }
				  else if (Direction == Robot_Arm_Getmedicine)
				  {
					  Robot_Arm_SendCommand(Robot_Arm_Getmedicine);
				  }
			  }
				break;
	  	  	 case VOICE_Mode:
				  Distance=Ultrasonic_Set_Distance();
					  if(Distance>50)
					  {
							  Direction=Read_TTL();
							  if(Direction==Right)
							  {
								  Motors_Turn_Right(ACTUAL_SPEED);
							  }
							  else if(Direction==Left)
							  {
								  Motors_Turn_Left(ACTUAL_SPEED);
							  }
							  else if(Direction==Forward)
							  {
								  Motors_Forward(ACTUAL_SPEED);
							  }
							  else if(Direction==Stop)
							  {
								  Motors_Stop();
							  }
							  else if (Direction == Robot_Arm_Open)
							  {
								  Robot_Arm_SendCommand(Robot_Arm_Open);
							  }
							  else if (Direction == Robot_Arm_Close)
							  {
								  Robot_Arm_SendCommand(Robot_Arm_Close);
							  }
							  else if (Direction == Robot_Arm_Getmedicine)
							  {
								  Robot_Arm_SendCommand(Robot_Arm_Getmedicine);
							  }
					  }
					  else if (Distance<50)
					  {
						  Direction=Read_TTL();
						  if(Direction==Right)
						  {
							  Motors_Turn_Right(ACTUAL_SPEED);
						  }
						  else if(Direction==Left)
						  {
							  Motors_Turn_Left(ACTUAL_SPEED);
						  }
						  else if(Direction==Forward)
						  {
							  Motors_Stop();
						  }
						  else if(Direction==Stop)
						  {
							  Motors_Stop();
						  }
						  else if (Direction == Robot_Arm_Open)
						  {
							  Robot_Arm_SendCommand(Robot_Arm_Open);
						  }
						  else if (Direction == Robot_Arm_Close)
						  {
							  Robot_Arm_SendCommand(Robot_Arm_Close);
						  }
						  else if (Direction == Robot_Arm_Getmedicine)
						  {
							  Robot_Arm_SendCommand(Robot_Arm_Getmedicine);
						  }
					  }
						break;

	  }



  }

}