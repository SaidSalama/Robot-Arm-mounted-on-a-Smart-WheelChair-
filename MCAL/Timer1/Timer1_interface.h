/*
 * Timer1_interface.h
 *
 *  Created on: Sep 15, 2022
 *      Author: Said Salama
 */

#ifndef MCAL_TIMER1_TIMER1_INTERFACE_H_
#define MCAL_TIMER1_TIMER1_INTERFACE_H_
#include "Std_Types.h"
#include "BIT_MATH.h"

typedef enum
{
	CH_Not_Used,
	CH_Used

}Ch_Used;
typedef enum
{
	TIMER_DISABLE,
	TIMER_ENABLE

}Timer_Status;

typedef enum
{
	Edge_Aligned_mode,
	Center_Aligned_mode_1,
	Center_Aligned_mode_2,
	Center_Aligned_mode_3

}Center_Aligned_mode;

typedef enum
{
	Upcounter,
	Downcounter

}Counter_Direction;

typedef enum
{
	Output,
	Input_Ic1_On_Tl1,
	Input_Ic1_On_Tl2,
	Input_Ic1_On_TRC,

}Ch_Dir;

typedef enum
{
	Frozen,
	Ch_Active,
	Ch_Inactive,
	Toggle,
	Forced_Inactive,
	Forced_Active,
	PWMmode1,
	PWMmode2

}Output_Compare_mode;


typedef enum
{
	Ch_Active_High,
	Ch_Active_Low
}Output_Active_Level;
/***********************
 * INPUT CAPTURE
 * *****************************************/

typedef enum
{
	No_Filter,
	fSAMPLING__fCK_INT__N2,
	fSAMPLING__fCK_INT__N4,
	fSAMPLING__fCK_INT__N8
	/*and so on..." I didn't need other filters in my projects" */

}Input_Capture_Filter;

typedef enum
{
	Rising_Edge,
	Falling_Edge
}Input_Capture_Edge;

typedef enum
{
	No_PSC,
	Every_2events,
	Every_4events,
	Every_8events
}Input_Capture_PSC;

typedef enum
{
	TIMER1,
	TIMER2

}TIM_Num;
typedef struct
{
	TIM_Num 			 TIM_Num;
	Timer_Status         Auto_Reload_Preload;
	Center_Aligned_mode  Center_Aligned_mode;
	Counter_Direction    Counter_Direction;
	Ch_Used					Ch1;
	Ch_Used					Ch2;
	Ch_Used					Ch3;
	Ch_Used					Ch4;
	/*********ch1**********//*****************************************************/
	Timer_Status		 Ch1_OutputCompare_Preload;
	Ch_Dir		         Ch1_Dir;
	Output_Compare_mode  Ch1_Output_Compare_mode;
	Output_Active_Level  Ch1_Polarity;
	Input_Capture_Filter Ch1_Input_Filter;
	Input_Capture_Edge   Ch1_Input_Edge;
	Input_Capture_PSC    Ch1_Input_PSC;
	Timer_Status		Ch1_Capture_Compare_Interrupt;
	/*********ch2**********//******************************************************/
	Timer_Status		 Ch2_OutputCompare_Preload;
	Ch_Dir		         Ch2_Dir;
	Output_Compare_mode  Ch2_Output_Compare_mode;
	Output_Active_Level  Ch2_Polarity;
	Input_Capture_Filter Ch2_Input_Filter;
	Input_Capture_Edge   Ch2_Input_Edge;
	Input_Capture_PSC    Ch2_Input_PSC;
	Timer_Status		Ch2_Capture_Compare_Interrupt;
	/*********ch3**********//*******************************************************/
	Timer_Status		 Ch3_OutputCompare_Preload;
	Ch_Dir		         Ch3_Dir;
	Output_Compare_mode  Ch3_Output_Compare_mode;
	Output_Active_Level  Ch3_Polarity;
	Input_Capture_Filter Ch3_Input_Filter;
	Input_Capture_Edge   Ch3_Input_Edge;
	Input_Capture_PSC    Ch3_Input_PSC;
	Timer_Status		Ch3_Capture_Compare_Interrupt;
	/*********ch4**********//***************************************************************/
	Timer_Status		 Ch4_OutputCompare_Preload;
	Ch_Dir		         Ch4_Dir;
	Output_Compare_mode  Ch4_Output_Compare_mode;
	Output_Active_Level  Ch4_Polarity;
	Input_Capture_Filter Ch4_Input_Filter;
	Input_Capture_Edge   Ch4_Input_Edge;
	Input_Capture_PSC    Ch4_Input_PSC;
	Timer_Status		Ch4_Capture_Compare_Interrupt;


}Timer_Config;



void Timers_Init(Timer_Config* Timer1Config);


#endif /* MCAL_TIMER1_TIMER1_INTERFACE_H_ */
