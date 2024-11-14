/*
 * interface_UART.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Said Salama
 */

#ifndef INTERFACE_UART_H_
#define INTERFACE_UART_H_


#include "STD_TYPES.h"

typedef enum {
	UART1 ,
	UART2 ,
	UART3 ,
	UART4 ,
	UART5 ,

}UART_NUM;

typedef enum {
	UART_DISABLE ,
	UART_ENABLE

}UART_State;

typedef enum {
	data_8 ,
	data_9

}UART_WordLengh;
typedef enum {
	EVEN_PARITY ,
	ODD_PARITY

}UART_Parity;

typedef enum {
	ONE_STOPBIT ,
	HALF_STOPBIT,
	TWO_STOPBIT,
	ONEANDHALF_STOPBIT

}UART_StopBits;

typedef struct{

	UART_State     Reciever;
	UART_NUM        UartNum;
	UART_WordLengh  WordLengh;
	UART_StopBits   StopBits;
	UART_Parity     Parity;
	UART_State     Transmitter;
	UART_State     CLCKEN;
	UART_State     DMA_Transmitter;
	UART_State     DMA_Reciever;

}UART_config;


/**  funnction decleration  */
void UART_voidInit(UART_config * UARTConfig,int baudrate);
u32 UART_Read(UART_config * UARTConfig);

void UART_Send(u8 data,UART_config * UARTConfig);
void Set_Baudrate(int baudrate,UART_config * UARTConfig);

#endif /* INTERFACE_UART_H_ */
