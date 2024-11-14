/*
 * SPI__interface.h
 *
 *  Created on: 23 Feb 2023
 *      Author: saids
 */

#ifndef PRIVATE_SPI_H_
#define PRIVATE_SPI_H_

#include "STD_TYPES.h"


#define SPI1_BASE_ADRESS   0x40013000
#define SPI2_BASE_ADRESS   0x40003800
#define SPI3_BASE_ADRESS   0x40003C00

typedef struct{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;


} SPI_t;





#endif /* PRIVATE_SPI_H_ */
