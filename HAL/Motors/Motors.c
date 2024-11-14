/*
 * Motors.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Said Salama
 */
#include "Motors.h"
#include "Std_Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Timer1_interface.h"
#include "RCC_interface.h"
#include "joystick.h"


extern  u32 Joystick_Values[2];
Timer_Config Motors_Config;
 u32 y;
 u32 x;
static u32 Forward_Speed_Left_Motor;
static u32 Forward_Speed_Right_Motor;
static u32 Backward_Speed_Right_Motor;
static u32 Backward_Speed_Left_Motor;
static u16 AutoReloadValueTIM2=40;					//because timer2 is for motors , time base = 1us because frequency internal 8Mhz PRESCALER = 7
void Init_Motors()
{
	    RCC_PerClock_State(APB2, IOPA_PERIPHERAL, PClock_enable);
		RCC_PerClock_State(APB2, IOPB_PERIPHERAL, PClock_enable);
		DIO_PinMode(GPIOA, 0, OUTPUT_SPEED_10MHZ_AFPP);         //TIM2->CH1 FOR LEFT MOTOR (forward)
		DIO_PinMode(GPIOA, 1, OUTPUT_SPEED_10MHZ_AFPP);			//TIM2->CH2 FOR RIGHT MOTOR(forward)
		DIO_PinMode(GPIOA, 2, OUTPUT_SPEED_10MHZ_AFPP);         //TIM2->CH3 FOR LEFT MOTOR (reverse)
		DIO_PinMode(GPIOA, 3, OUTPUT_SPEED_10MHZ_AFPP);			//TIM2->CH4 FOR RIGHT MOTOR(reverse)

	Motors_Config.TIM_Num=TIMER2;
	Motors_Config.Auto_Reload_Preload=TIMER_ENABLE;
	Motors_Config.Counter_Direction=Upcounter;
	Motors_Config.Center_Aligned_mode=Edge_Aligned_mode;
	Motors_Config.Ch1=CH_Used;
	Motors_Config.Ch2=CH_Used;
	Motors_Config.Ch3=CH_Used;
	Motors_Config.Ch4=CH_Used;
	Motors_Config.Ch1_Capture_Compare_Interrupt=TIMER_DISABLE;
	Motors_Config.Ch1_Dir=Output;
	Motors_Config.Ch1_OutputCompare_Preload=TIMER_ENABLE;
	Motors_Config.Ch1_Output_Compare_mode=PWMmode1;
	Motors_Config.Ch1_Polarity=Ch_Active_High;
	Motors_Config.Ch2_Capture_Compare_Interrupt=TIMER_DISABLE;
	Motors_Config.Ch2_Dir=Output;
	Motors_Config.Ch2_OutputCompare_Preload=TIMER_ENABLE;
	Motors_Config.Ch2_Output_Compare_mode=PWMmode1;
	Motors_Config.Ch2_Polarity=Ch_Active_High;
	Motors_Config.Ch3_Capture_Compare_Interrupt=TIMER_DISABLE;
	Motors_Config.Ch3_Dir=Output;
	Motors_Config.Ch3_OutputCompare_Preload=TIMER_ENABLE;
	Motors_Config.Ch3_Output_Compare_mode=PWMmode1;
	Motors_Config.Ch3_Polarity=Ch_Active_High;
	Motors_Config.Ch4_Capture_Compare_Interrupt=TIMER_DISABLE;
	Motors_Config.Ch4_Dir=Output;
	Motors_Config.Ch4_OutputCompare_Preload=TIMER_ENABLE;
	Motors_Config.Ch4_Output_Compare_mode=PWMmode1;
	Motors_Config.Ch4_Polarity=Ch_Active_High;

	Timers_Set_AutoReload(&Motors_Config,AutoReloadValueTIM2);
	Timers_Init(&Motors_Config);

}
/*We control the motors direction just by changing the value of compare register
 * because enable pin are attached to 5 volts */
/*Note that in these   functions the speed of the motors are fixed and determined using the parameter speed*/
void Motors_Forward(u8 speed)
{

	Timers_Set_CaptureCompare(&Motors_Config,3,0);			//CH3 = 0
	Timers_Set_CaptureCompare(&Motors_Config,4,0);			//CH4 = 0
	Timers_Set_CaptureCompare(&Motors_Config,1,AutoReloadValueTIM2/speed);		//apply duty cycle to ch1 ch2
	Timers_Set_CaptureCompare(&Motors_Config,2,AutoReloadValueTIM2/speed);


}
void Motors_Backward(u8 speed) 			//to reverse motors we have to make duty cycle of forward channel =0
{										//and make duty cycle of reverse channel =speed
	Timers_Set_CaptureCompare(&Motors_Config,1,0);
	Timers_Set_CaptureCompare(&Motors_Config,2,0);
	Timers_Set_CaptureCompare(&Motors_Config,3,AutoReloadValueTIM2/speed);
	Timers_Set_CaptureCompare(&Motors_Config,4,AutoReloadValueTIM2/speed);

}

void Motors_Stop()
{

	Timers_Set_CaptureCompare(&Motors_Config,1,0);
	Timers_Set_CaptureCompare(&Motors_Config,2,0);
	Timers_Set_CaptureCompare(&Motors_Config,3,0);
	Timers_Set_CaptureCompare(&Motors_Config,4,0);

}

/*****************************MOTION DIRECTIONS*******************************/

void Motors_Turn_Right(u8 speed)/*to turn right we need to stop the right motors and apply duty cycle to the left motor */
{

	Timers_Set_CaptureCompare(&Motors_Config,2,0);
	Timers_Set_CaptureCompare(&Motors_Config,3,0);
	Timers_Set_CaptureCompare(&Motors_Config,4,0);
	Timers_Set_CaptureCompare(&Motors_Config,1,AutoReloadValueTIM2/speed);

}
void Motors_Turn_Left(u8 speed)		/*to turn left we need to stop the left motors and apply duty cycle to the right motor */
{
	Timers_Set_CaptureCompare(&Motors_Config,1,0);
	Timers_Set_CaptureCompare(&Motors_Config,3,0);
	Timers_Set_CaptureCompare(&Motors_Config,4,0);
	Timers_Set_CaptureCompare(&Motors_Config,2,AutoReloadValueTIM2/speed);


}

/*this functions updates the speed of motors according to the values of the joystick so speed is not fixed*/
/*Note that the equations used to calculate the speed of the motors are based on experiment only and are not fixed with others joystick and motors*/
void  Motors_Update_Speed_Direction()
{
	x=Joystick_Values[1];			//these variables are updated by DMA  see JOYSTIC DRIVER
	y=Joystick_Values[0];
	/*************************************************************************************/
	if(x>(Mid_Joystick_Value) && y>(Mid_Joystick_Value))				//first quarter in forward part
	{
		if(y>x && (y>Mid_Joystick_Value+50))							//50 is the stop region
		{
			Forward_Speed_Right_Motor=(2*(y-Mid_Joystick_Value)*AutoReloadValueTIM2)/Max_Joystick_Value;
			Forward_Speed_Left_Motor=Forward_Speed_Right_Motor-(((x-Mid_Joystick_Value)*AutoReloadValueTIM2)/Max_Joystick_Value);
		}
		else if (x>y && (x>Mid_Joystick_Value+50))
		{
			Forward_Speed_Right_Motor=(2*(x-Mid_Joystick_Value)*AutoReloadValueTIM2)/Max_Joystick_Value;
			Forward_Speed_Left_Motor=((y-Mid_Joystick_Value)*AutoReloadValueTIM2)/Max_Joystick_Value;
		}

		Timers_Set_CaptureCompare(&Motors_Config,3,0);
		Timers_Set_CaptureCompare(&Motors_Config,4,0);
		Timers_Set_CaptureCompare(&Motors_Config,1,Forward_Speed_Left_Motor);
		Timers_Set_CaptureCompare(&Motors_Config,2,Forward_Speed_Right_Motor);

	}
	/***********************************************************************************/
	else if (x<Mid_Joystick_Value && y>Mid_Joystick_Value )			//second quarter in forward part
	{
		if (y>(Max_Joystick_Value-x) && y>(Mid_Joystick_Value+50))
		{
			Forward_Speed_Left_Motor=(2*(y-Mid_Joystick_Value)*AutoReloadValueTIM2)/Max_Joystick_Value;
			Forward_Speed_Right_Motor=Forward_Speed_Left_Motor-((Mid_Joystick_Value-x)*AutoReloadValueTIM2)/Max_Joystick_Value;
		}
		else if(y<(Max_Joystick_Value-x) && x<(Mid_Joystick_Value-50))
		{
			Forward_Speed_Left_Motor=(2*(Mid_Joystick_Value-x)*AutoReloadValueTIM2)/Max_Joystick_Value;
			Forward_Speed_Right_Motor=((y-Mid_Joystick_Value)*AutoReloadValueTIM2)/Max_Joystick_Value;
		}

		Timers_Set_CaptureCompare(&Motors_Config,3,0);
		Timers_Set_CaptureCompare(&Motors_Config,4,0);
		Timers_Set_CaptureCompare(&Motors_Config,1,Forward_Speed_Left_Motor);
		Timers_Set_CaptureCompare(&Motors_Config,2,Forward_Speed_Right_Motor);

	}
	/******************************************************************************/
	/*the back part*/

	else if (y<(Mid_Joystick_Value-50))
	{
	     Backward_Speed_Left_Motor=(2*(Mid_Joystick_Value-y)*AutoReloadValueTIM2)/Max_Joystick_Value;
		 Backward_Speed_Right_Motor=Backward_Speed_Left_Motor;

	 Timers_Set_CaptureCompare(&Motors_Config,1,0);
	 Timers_Set_CaptureCompare(&Motors_Config,2,0);
	 Timers_Set_CaptureCompare(&Motors_Config,3,Backward_Speed_Left_Motor);
	 Timers_Set_CaptureCompare(&Motors_Config,4,Backward_Speed_Right_Motor);
	}
	/***************************************************************************/
	else
	{
		Motors_Stop();
	}
}


