/*
 * Robot arm.c
 *
 *  Created on: Jan 14, 2023
 *      Author: saids
 */

#include "interface_SPI.h"

#include "Robot_arm.h"

SPI_Config RobotArm;
void Robot_Arm_Communication_Init()
{


	RobotArm.Mode=Master;
	RobotArm.Phase=Second_Edge;
	RobotArm.BaudRate=fPCLK_2;
	RobotArm.Data_Size=_8bit;
	RobotArm.Frame_Format=LSB_First;
	RobotArm.SPI_NUM=SPI_2;
	RobotArm.Polarity=Inverted;
	RobotArm.Slave_Select=Software_Slave_Selcet;

			SPI_Init(& RobotArm);
}
void Robot_Arm_SendCommand(u8 Command)
{
	SPI_Send(Command, &RobotArm);
}
