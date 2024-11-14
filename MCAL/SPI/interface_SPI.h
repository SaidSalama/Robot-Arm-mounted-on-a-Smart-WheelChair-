/*
 * SPI__interface.h
 *
 *  Created on: 23 Feb 2023
 *      Author: saids
 */

#ifndef INTERFACE_SPI_H_
#define INTERFACE_SPI_H_
#include  "STD_TYPES.h"

typedef enum
{
	SPI_1,
	SPI_2,
	SPI_3
}SPI_NUM;

typedef enum
{
	First_Edge,       //sampling is done on the fist edge
	Second_Edge			//sampling is done on the second edge

}SPI_Phase;

typedef enum
{
	Non_Inverted,       //the clock is at logic low when slave select transitions to logic low
	Inverted			//the clock is at logic high when slave select transitions to logic low

}SPI_Polarity;

typedef enum
{
	 Slave ,
	 Master

}SPI_Mode;

typedef enum
{
	fPCLK_2,						//speed of data transmission = bus speed/2 ..etc
	fPCLK_4,
	fPCLK_8,
	fPCLK_16,
	fPCLK_32,
	fPCLK_64,
	fPCLK_128,
	fPCLK_256,

}SPI_BaudRate;

typedef enum
{
	SPI_DSABLE,
	SPI_ENABLE

}SPI_State;

typedef enum
{
	Hardware_Slave_Selcet,
	Software_Slave_Selcet

}SPI_Slave_Select;

typedef enum
{
	 MSB_First,									//most or least  significant bit first
	 LSB_First									//should be the same as the slave

}SPI_Frame_Format;


typedef enum
{
	 _8bit ,
	 _16bit

}SPI_Data_Size;

typedef struct
{
	SPI_NUM			 SPI_NUM;
	SPI_Phase        Phase;
	SPI_Polarity     Polarity;
	SPI_Mode		 Mode;
	SPI_BaudRate     BaudRate;
	SPI_Frame_Format Frame_Format;
	SPI_Data_Size    Data_Size;
	SPI_Slave_Select  Slave_Select;
	SPI_State		TX_Buffer_Interrupt;
	SPI_State       RX_Buffer_Inetrrupt;
	SPI_State		TX_Buffer_DMA;					//ENABLE SENDING VIA DMA
	SPI_State		RX_Buffer_DMA;					//ENABLE RECIEVING DATA VIA DMA


}SPI_Config;


/*Function Declaration*/

void SPI_Init(SPI_Config *SPI_Config);
void SPI_Send(u16 Data,SPI_Config *SPI_Config);

#endif /* INTERFACE_SPI_H_ */
