/*
 * Ultrasonic.c
 *
 *  Created on: Oct 18, 2022
 *      Author: Said Salama
 */

/* in the wheelchair 4 ultra*/
#include "Ultrasonic.h"
#include "Std_Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Timer1_interface.h"
#include "Timer1_private.h"
#include "STK_interface.h"
#include "NVIC_interface.h"

static u32 Distance=0;
static u32 time =0 ;
static u32 x=0;
static u32 y=0;
static Timer_Config Ultrasonic_Sensor;
extern TIMER_t *Timer_Num [2];
static u32 TimeOut=100000;

void All_Ultrasonic_Init()
{

	DIO_PinMode(Echo_Port_1, Echo_Pin_1, INPUT_PULL_UP_DOWN);    		   		//Timer1 ch1 PA8
	DIO_PinMode(Trig_Port_1, Trig_Pin_1, OUTPUT_SPEED_50MHZ_PP);					//trigg PB9
	DIO_PinWrite(Trig_Port_1, Trig_Pin_1, GPIO_LOW);

	DIO_PinMode(Echo_Port_2, Echo_Pin_2, INPUT_PULL_UP_DOWN);    		   		//Timer1 ch2 PA9
	DIO_PinMode(Trig_Port_2, Trig_Pin_2, OUTPUT_SPEED_50MHZ_PP);					//trigg PB8
	DIO_PinWrite(Trig_Port_2, Trig_Pin_2, GPIO_LOW);


	Ultrasonic_Sensor.TIM_Num=TIMER1;
	Ultrasonic_Sensor.Auto_Reload_Preload=TIMER_ENABLE;
	Ultrasonic_Sensor.Counter_Direction=Upcounter;
	Ultrasonic_Sensor.Center_Aligned_mode=Edge_Aligned_mode;
	Ultrasonic_Sensor.Ch1=CH_Used;
	Ultrasonic_Sensor.Ch2=CH_Not_Used;
	Ultrasonic_Sensor.Ch3=CH_Not_Used;
	Ultrasonic_Sensor.Ch4=CH_Not_Used;
	Ultrasonic_Sensor.Ch1_Capture_Compare_Interrupt=TIMER_DISABLE;
	Ultrasonic_Sensor.Ch1_Dir=Input_Ic1_On_Tl1;
	Ultrasonic_Sensor.Ch1_Input_Edge=Rising_Edge;
	Ultrasonic_Sensor.Ch1_Input_Filter=fSAMPLING__fCK_INT__N8;
	Ultrasonic_Sensor.Ch1_Input_PSC=No_PSC;


	Timers_Init(&Ultrasonic_Sensor);
}

void All_Ultrasonic_Trigger()
{
	DIO_PinWrite(Trig_Port_1, Trig_Pin_1, GPIO_HIGH);
	MSTK_voidSetBusyWait(8);
	DIO_PinWrite(Trig_Port_1, Trig_Pin_1, GPIO_LOW);

}


u32 Ultrasonic_Set_Distance()
{
	  DIO_PinWrite(Trig_Port_1, Trig_Pin_1, GPIO_HIGH);				//triggering the trig pin
	  MSTK_voidSetBusyWait(10);
	  DIO_PinWrite(Trig_Port_1, Trig_Pin_1, GPIO_LOW);

	  while (((Timer_Num[Ultrasonic_Sensor.TIM_Num]->SR & (1<<1))==0))
	{
		TimeOut=TimeOut-1;
		if(TimeOut==0)
		{
			NVIC_Software_Reset();						//if the timeout is zero it means there is a problem
		}												//so software reset is used to re initialize system to avoid being blocked
	}

	  Timer_Num[Ultrasonic_Sensor.TIM_Num]->SR &= ~(1<<1);
	  x=Timer_Num[Ultrasonic_Sensor.TIM_Num]->CCR1;
	  Timer_Num[Ultrasonic_Sensor.TIM_Num]->CCER|=(1<<1);								//ENBALE CH1  //falling edge
	  while (!(Timer_Num[Ultrasonic_Sensor.TIM_Num]->SR &(1<<1)));
	  Timer_Num[Ultrasonic_Sensor.TIM_Num]->SR &= ~(1<<1);
	  y=Timer_Num[Ultrasonic_Sensor.TIM_Num]->CCR1;
	  Timer_Num[Ultrasonic_Sensor.TIM_Num]->CCER &= ~(1<<1);									//ENBALE CH1  //rising edge

		if (y> x)
		{
			time = y-x;
		}

		else if (x > y)
		{
			time = (0xffff - x) + y;
		}
		Distance= time*.034/2;					//distance = (speed of ultrasonic signal * time ) divided by 2 because we need only the transmitting time not the return time of the signal

		return Distance;
}
