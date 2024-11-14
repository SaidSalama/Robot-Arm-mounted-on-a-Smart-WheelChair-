/*
 * ADC_interface.h
 *
 *  Created on: Sep 29, 2022
 *      Author: Said Salama
 */

#ifndef INC_ADC_INTERFACE_H_
#define INC_ADC_INTERFACE_H_
#include "STD_Types.h"

/*CHANNELS NUMBERS*/
#define CH0 0
#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 4
#define CH5 5
#define CH6 6
#define CH7 7
/*ORDER OF CONVERSION*/
#define Order_1 1
#define Order_2 2
#define Order_3 3
#define Order_4 4
#define Order_5 5
#define Order_6 6
#define Order_7 7



typedef enum
{
	ADC_DISABLE,
	ADC_ENABLE

}ADC_Status;

/*typedef enum
{
	_1Channel,
	_2Channel,
	_3Channel,
	_4Channel,
	_5Channel,
	_6Channel,
	_7Channel,
	_8Channel

}DiscNum;*/						//number of regular channels to be converted in disc mode
								//In injected channels this number is always 1
typedef enum
{
	Right_Alignment,
	Left_Alignment
}Data_Alignment;

typedef enum
{
	_1andHalf,
	_7andHalf,
	_13andHalf,
	_28andHalf,
	_41andHalf,
	_55andHalf,
	_71andHalf,
	_239andHalf

}Sample_Time;

typedef enum
{
	_1Channel,
	_2Channel,
	_3Channel,
	_4Channel,
	_5Channel,
	_6Channel,
	_7Channel,
	_8Channel,
	_9Channel,
	_10Channel,
	_11Channel,
	_12Channel,
	_13Channel,
	_14Channel,
	_15Channel,
	_16Channel

}Ch_Length;

typedef enum
{
	NOT_USED,
	USED
}Used_Ch;

typedef enum
{
	CLCK__2 ,				/*CLOCK DIVIDED BY 2*/
	CLCK__4 ,				/*CLOCK DIVIDED BY 4*/
	CLCK__6 ,				/*CLOCK DIVIDED BY 6*/
	CLCK__8 ,				/*CLOCK DIVIDED BY 8*/


}ADC_Prescaler;

typedef enum
{
	Timer_1_CC1_event,
	Timer_1_CC2_event,
	Timer_1_CC3_event,
	Timer_2_CC2_event,
	Timer_3_TRGO_event,
	Timer_4_CC4_event,
	EXTI_Line,
	Software


}ADC_Trigger;
typedef struct

{
	//Used_Ch				Channel[17];
	ADC_Status 			EOC_Interrupt;
	ADC_Status 			JEOC_Interrupt;
	ADC_Status 			Scan_Mode;
	ADC_Status 			JAUTO;
	ADC_Status			Regular_Disc_Mode;
	ADC_Status 			Injected_Disc_Mode;
	Ch_Length	   		DiscNum;
	ADC_Status 			Continous_Conversion;
	Data_Alignment		Data_Alignment;
	u16 				Offset;
	Ch_Length		 	Num_Of_Regular_Ch;
	ADC_Status			DMA_Transfer;
	ADC_Prescaler		ADC_Prescaler;
	ADC_Trigger			ADC_Trig;


}ADC_Config;


/*********************************************************************************/
void ADC_Init(ADC_Config* ADC_Config);
void Select_ADC1_Ch_SampleTime(u8 Ch,u8 SampleTime);
void Select_ADC1_Ch_Order(u8 Ch,u8 Order);
void Start_ADC1_Conversion();

#endif /* INC_ADC_INTERFACE_H_ */
