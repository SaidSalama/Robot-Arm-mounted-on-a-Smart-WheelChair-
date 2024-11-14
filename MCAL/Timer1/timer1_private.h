/*
 * timer1_private.h
 *
 *  Created on: Sep 15, 2022
 *      Author: Said Salama
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define Timer1   ((/*volatile*/ TIMER_t*) 0x40012C00)
#define Timer2   ((/*volatile*/ TIMER_t*) 0x40000000)

typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 RCR;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 BDTR;
	u32 DCR;
	u32 DMAR;


}TIMER_t;

#endif /* TIMER1_PRIVATE_H_ */
