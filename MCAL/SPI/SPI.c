/*
 * SPI.c
 *
 *  Created on: 23 Feb 2023
 *      Author: saids
 */


#include <interface_SPI.h>
#include <private_SPI.h>
#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

SPI_t * SPI_x[3]={									//array containing the adresses of the 3 SPIs to use one of them directly through its index
		(SPI_t*)SPI1_BASE_ADRESS,
		(SPI_t*)SPI2_BASE_ADRESS,
		(SPI_t*)SPI3_BASE_ADRESS,
};


void SPI_Init(SPI_Config *SPI_Config)
{

	SPI_x[SPI_Config->SPI_NUM]->CR1=0;										//initialize cr1

	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Phase<<0);				//bit 0 of CR1 to determine phase
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Polarity<<1);				//bit 1 of CR1 to determine polarity
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Slave_Select<<9);			//the way spi select its slaves
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Slave_Select<<8);			//this bit should be set if bit9 is set to avoid mode fault
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Mode<<2);					//bit 2 of CR1 master or slave
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->BaudRate<<3);				//bits[3:5]to determine baudrate
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Frame_Format<<7);			//bit 7 to deetrmine lsb or msb
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(SPI_Config->Data_Size<<11);			//bit 11 dtetrmine data drame size
	SPI_x[SPI_Config->SPI_NUM]->CR2|=(SPI_Config->RX_Buffer_DMA<<0);		//bit 0 of CR2 to recieve data by DMA
	SPI_x[SPI_Config->SPI_NUM]->CR2|=(SPI_Config->TX_Buffer_DMA<<1);		//bit 1 of CR2 to send data by DMA
	SPI_x[SPI_Config->SPI_NUM]->CR2|=(SPI_Config->TX_Buffer_Interrupt<<7);	//enable Interrupt sending buffer empty
	SPI_x[SPI_Config->SPI_NUM]->CR2|=(SPI_Config->RX_Buffer_Inetrrupt<<6);	//enable Interrupt recieving buffer empty
	SPI_x[SPI_Config->SPI_NUM]->CR1|=(1<<6);								//enable spi bit 6 of CR1

}



void SPI_Send(u16 Data,SPI_Config *SPI_Config)
{
	while(GET_BIT(SPI_x[SPI_Config->SPI_NUM]->SR,7)==1);				//wait while busy flag is 1 this means SPI is busy communicating
	SPI_x[SPI_Config->SPI_NUM]->DR=Data;								//data in data register

}
