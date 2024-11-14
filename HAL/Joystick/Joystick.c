/*
 * Joystick.c
 *
 *  Created on: Jan 22, 2023
 *      Author: saids
 */

#include"DMA_interface.h"
#include"ADC_interface.h"
#include"ADC_private.h"
#include"DIO_interface.h"
#include "Std_Types.h"
#include "joystick.h"

u32 Joystick_Values[2]={0,0};



void Init_Joystick()
{
	   DIO_PinMode(GPIOA, 5, INPUT_ANALOG);
	   DIO_PinMode(GPIOA, 6, INPUT_ANALOG);

	  	ADC_Config ADC_Config;

	  	ADC_Config.ADC_Prescaler=CLCK__8;
	  	ADC_Config.Scan_Mode=ADC_ENABLE;
	  	ADC_Config.Continous_Conversion=ADC_ENABLE;
	  	ADC_Config.Data_Alignment=Right_Alignment;
	  	ADC_Config.EOC_Interrupt=ADC_DISABLE;
	  	ADC_Config.Num_Of_Regular_Ch=_2Channel;
	  	ADC_Config.DMA_Transfer=ADC_ENABLE;
	  	ADC_Config.ADC_Trig=Software;

	  	ADC_Init(&ADC_Config);
	  	ADC1->SQR3|=(5<<(5*(1-1)));					 //order of ch5
	  	ADC1->SQR3|=(6<<(5*(2-1)));					 //order of ch6


	  	  	DMA_voidInit( USE_DMA_1);
	  	  	 // Define configuration struct for DMA
	  	  		sDMA_Config_t DMA_Config;
	  	  		DMA_Config.DMA_Number = USE_DMA_1;
	  	  		DMA_Config.ChannelPriority = DMA_VERY_HIGH;
	  	  		DMA_Config.DMA_Channel = DMA_Channel1;
	  	  		DMA_Config.DataDirection = ReadFromPeripheral;
	  	  		DMA_Config.M2M_Mode = DMA_DISABLE;
	  	  		DMA_Config.MemoryIncrement = DMA_ENABLE;
	  	  		DMA_Config.MemorySize = DMA_Word;
	  	  		DMA_Config.PeripheralIncrement = DMA_DISABLE;
	  	  		DMA_Config.PeripheralSize = DMA_Word;
	  	  		DMA_Config.TransferCompleteInterrupt = DMA_DISABLE;
	  	  		DMA_Config.HalfTransferInterrupt = DMA_DISABLE;
	  	  		DMA_Config.CircularMode=DMA_ENABLE;
	  	  		// initialize channel
	  	  		DMA_voidInitChannel(&DMA_Config);

	  	  		DMA_voidStartTransfer(&DMA_Config, &ADC1->DR, &Joystick_Values, 2);  //2  channels of adc

	  	  	   Start_ADC1_Conversion();

}

u8 Joystick_Set_Direction()
{
	u8	Direction;
	u32 y=Joystick_Values[0];
	u32 x=Joystick_Values[1];

	if(x>(Mid_Joystick_Value) && y>(Mid_Joystick_Value))
	{
		if(y>x)
		{
			Direction=Forward;
		}
		else if(x>y)
		{
			Direction=Left;
		}
	}
	else if (x<Mid_Joystick_Value && y>Mid_Joystick_Value)
	{
		if(y>(Max_Joystick_Value-x))
		{
			Direction=Forward;
		}
		else if (y<(Max_Joystick_Value-x))
		{
			Direction=Right;
		}
	}
	else if (y<(Mid_Joystick_Value) && x<(Mid_Joystick_Value))
	{
		Direction=Backward;
	}
	else if(y<(Mid_Joystick_Value) && x>(Mid_Joystick_Value))
	{
		Direction=Backward;
	}
	return Direction;
}




