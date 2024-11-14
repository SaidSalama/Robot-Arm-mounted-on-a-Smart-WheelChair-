/*
 * private_UART.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Said Salama
 */

#ifndef PRIVATE_UART_H_
#define PRIVATE_UART_H_

#define UART1_BASE_ADDRES  0x40013800
#define UART2_BASE_ADDRES  0x40004400
#define UART3_BASE_ADDRES  0x40004800
#define UART4_BASE_ADDRES  0x40004C00
#define UART5_BASE_ADDRES  0x40005000

typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART_t;

/*UART_t *UARTx[5]={
		( UART_t* )UART1_BASE_ADDRES,
		( UART_t* )UART2_BASE_ADDRES,
		( UART_t* )UART3_BASE_ADDRES,
		( UART_t* )UART4_BASE_ADDRES,
		( UART_t* )UART5_BASE_ADDRES,

};*/


#endif /* PRIVATE_UART_H_ */
