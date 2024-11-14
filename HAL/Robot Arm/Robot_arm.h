/*
 * Robot arm.h
 *
 *  Created on: Jan 14, 2023
 *      Author: saids
 */

#ifndef ROBOT_ARM_H_
#define ROBOT_ARM_H_

/*Robot Arm Commands*/
#define Robot_Arm_Open     		   10
#define Robot_Arm_Close   		   20
#define Robot_Arm_Getmedicine      30

void Robot_Arm_Communication_Init();
void Robot_Arm_SendCommand(u8 Command);






#endif /* ROBOT_ARM_H_ */
