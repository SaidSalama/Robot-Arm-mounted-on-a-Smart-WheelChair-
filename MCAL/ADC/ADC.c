/*
 * ADC.c
 *
 *  Created on: Sep 29, 2022
 *      Author: Said Salama
 */
#include <ADC_interface.h>

#include "ADC_private.h"
#include "STD_Types.h"
#include "RCC_interface.h"
#include "RCC_private.h"

void ADC_Init(ADC_Config* ADC_Config)
{
	RCC_PerClock_State(APB2,ADC1_PERIPHERAL,PClock_enable);
	ADC1->CR1|=( ADC_Config->EOC_Interrupt<<5);
	ADC1->CR1|=( ADC_Config->JEOC_Interrupt<<7);
	ADC1->CR1|=( ADC_Config->Scan_Mode<<8);
	ADC1->CR1|=( ADC_Config->JAUTO<<10);
	ADC1->CR1|=( ADC_Config->Regular_Disc_Mode<<11);
	ADC1->CR1|=( ADC_Config->Injected_Disc_Mode<<12);
	ADC1->CR1|=( ADC_Config->DiscNum<<13);

	ADC1->CR2|=( ADC_Config->Data_Alignment<<11);
	ADC1->CR2|=( ADC_Config->Continous_Conversion<<1);
	ADC1->CR2|=( ADC_Config->DMA_Transfer<<8);
	ADC1->CR2|=(ADC_Config->ADC_Trig<<17);
	ADC1->SQR1|=(ADC_Config->Num_Of_Regular_Ch <<20);

	RCC->CFGR|=(ADC_Config->ADC_Prescaler <<14);			//ADC preascaler from RCC

	ADC1->CR2|=(1<<0)|(1<<20);							//enable adc conversion on external(can be software see datasheet)
}

void Select_ADC1_Ch_SampleTime(u8 Ch,u8 SampleTime)/*PROBLEM############*/
{
	//if(Ch<10)
	{
		ADC1->SMPR2|=(SampleTime<<(3*Ch));
	}

}

void Select_ADC1_Ch_Order(u8 Ch,u8 Order)
{
	if(Order<7)
	{
		ADC1->SQR3|=(Ch<<(5*(Order-1)));
	}
	else if(Order>6 && Order<13)
	{
		ADC1->SQR2|=(Ch<<(5*(Order-7)));
	}
	else if(Order>12 && Order<17)
	{
		ADC1->SQR1|=(Ch<<(5*(Order-13)));
	}

}
void Start_ADC1_Conversion()
{
	ADC1->CR2|=(1<<22);
}

/*    HOW TO USE MULTIPLE ADC CHANNELS ? */

/* we use dma in circular mode and adc in cont mode num of transmition by dma is the number of channels
 * and the result of conversion are stored in an array of[n] where n is the number of channels
 * the results will be stored in the array in the same order seleced
 */
 /*  ADC_Config ADC_Config;
  ADC_Config.ADC_Prescaler=CLCK__8;
  ADC_Config.Scan_Mode=ADC_ENABLE;
  ADC_Config.Continous_Conversion=ADC_ENABLE;
  ADC_Config.Data_Alignment=Right_Alignment;
  ADC_Config.EOC_Interrupt=ADC_DISABLE;
  ADC_Config.Num_Of_Regular_Ch=_2Channel;
  ADC_Config.DMA_Transfer=ADC_ENABLE;
  ADC_Config.ADC_Trig=Software;
  ADC_Init(&ADC_Config);

   //Select_ADC1_Ch_Order(CH2,Order_2);
   //Select_ADC1_Ch_Order(0,1);
  ADC1->SQR3|=(0<<(5*(1-1)));
  ADC1->SQR3|=(2<<(5*(2-1)));

  // Init clock for DMA
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

			DMA_voidStartTransfer(&DMA_Config, &ADC1->DR, &ARR, 2);  //2  channels of adc
			Start_ADC1_Conversion();*/

 //*********************************************************************************************/
// in order to trigger adc by software we need to select the external trigger but the external source is
//software
/*ex
 */
/*RCC_PerClock_State(APB2, IOPB_PERIPHERAL, PClock_enable);
DIO_PinMode(GPIOB, 8, INPUT_ANALOG);
ADC_Config ADC_Config;

ADC_Config.ADC_Prescaler=CLCK__8;
ADC_Config.Scan_Mode=ADC_DISABLE;
ADC_Config.Continous_Conversion=ADC_ENABLE;
ADC_Config.Data_Alignment=Right_Alignment;
ADC_Config.EOC_Interrupt=ADC_DISABLE;
ADC_Config.Num_Of_Regular_Ch=_1Channel;
ADC_Config.DMA_Transfer=ADC_DISABLE;
ADC_Config.ADC_Trig=Software;

ADC_Init(&ADC_Config);

Select_ADC1_Ch_Order(8,1);
Select_ADC1_Ch_SampleTime(0, _239andHalf);		//to avoid cpu load we have to preascale freq

Start_ADC1_Conversion();*/

