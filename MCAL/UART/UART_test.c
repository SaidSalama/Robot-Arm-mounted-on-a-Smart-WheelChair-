/*
 * UART_test.c
 *
 *  Created on: Aug 31, 2022
 *      Author: Said Salama
 */
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// Include files
#include "RCC_interface.h"
#include "private_UART.h"
#include "interface_UART.h"
#include "DIO_interface.h"

UART_t *UARTx[5]={
		( UART_t* )UART1_BASE_ADDRES,
		( UART_t* )UART2_BASE_ADDRES,
		( UART_t* )UART3_BASE_ADDRES,
		( UART_t* )UART4_BASE_ADDRES,
		( UART_t* )UART5_BASE_ADDRES,

};


void UART_voidInit(UART_config * UARTConfig,int baudrate)
{

	if(UARTConfig->UartNum==UART1)
	{
		RCC_PerClock_State(APB2 ,14 , PClock_enable);
		UARTx[UARTConfig->UartNum]->CR1|=(1<<13); //EN UART
	}
	else
	{
		RCC_PerClock_State(APB1 ,UARTConfig->UartNum +16 , PClock_enable);
		UARTx[UARTConfig->UartNum]->CR1|=(1<<13); //EN UART
	}
	/* Baud rate config*/
	int Mantissa=8000000/(baudrate*16);
	int Fraction=((8000000%(baudrate*16))/baudrate);
	UARTx[UARTConfig->UartNum]->BRR = (Mantissa<<4)+Fraction;

	/*Config wordlengh*/
	if(UARTConfig->WordLengh==data_9)
	{
		UARTx[UARTConfig->UartNum]->CR1|=(1<<12);
	}
	else if(UARTConfig->WordLengh==data_8)
	{
		UARTx[UARTConfig->UartNum]->CR1 &= ~(1<<12);
	}
	/*ENABLE Transmitter*/
	if(UARTConfig->Transmitter==UART_ENABLE)
	{
		UARTx[UARTConfig->UartNum]->CR1|=(1<<3);
	}
	/*ENABLE parity*/
	if(UARTConfig->Parity==ODD_PARITY)
	{
		UARTx[UARTConfig->UartNum]->CR1|=(1<<9);
	}
	/*ENABLE Stopbits*/
	if(UARTConfig->StopBits==TWO_STOPBIT)
	{
		UARTx[UARTConfig->UartNum]->CR2|=(1<<13);
	}
	else if(UARTConfig->StopBits==ONE_STOPBIT)
		{
			UARTx[UARTConfig->UartNum]->CR2 &= ~(1<<13);
		}
	else if(UARTConfig->StopBits==HALF_STOPBIT)
		{
			UARTx[UARTConfig->UartNum]->CR2|=(1<<12);
		}
	else if(UARTConfig->StopBits==ONEANDHALF_STOPBIT)
		{
			UARTx[UARTConfig->UartNum]->CR2|=(1<<13);
			UARTx[UARTConfig->UartNum]->CR2|=(1<<12);
		}
	/*ENABLE reciever*/
	if(UARTConfig->Reciever==UART_ENABLE)
	{
		UARTx[UARTConfig->UartNum]->CR1|=(1<<2);
	}

}


void UART_Send(u8 data,UART_config * UARTConfig)
{
	while(GET_BIT(UARTx[UARTConfig->UartNum]->SR,6)==0);
	UARTx[UARTConfig->UartNum]->DR=data;
}
u32 UART_Read(UART_config * UARTConfig)
{
	while(GET_BIT(UARTx[UARTConfig->UartNum]->SR,5)==0);
	return UARTx[UARTConfig->UartNum]->DR ;
}
void Set_Baudrate(int baudrate,UART_config * UARTConfig)
{
	int Mantissa=8000000/(baudrate*16);
	int Fraction=((8000000%(baudrate*16))/baudrate);
	UARTx[UARTConfig->UartNum]->BRR = (Mantissa<<4)+Fraction;
}
