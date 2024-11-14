/*
 * ADC_private.h
 *
 *  Created on: Sep 29, 2022
 *      Author: Said Salama
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
#include "Std_Types.h"
#include "BIT_MATH.h"

#define    ADC1    ((volatile ADC_t *) 0x40012400)
#define    ADC2    ((volatile ADC_t *) 0x40012800)
#define    ADC3    ((volatile ADC_t *) 0x40013C00)

typedef struct

{
  u32	SR;
  u32   CR1;
  u32   CR2;
  u32   SMPR1;
  u32	SMPR2;
  u32   JOFR1;
  u32   JOFR2;
  u32   JOFR3;
  u32   JOFR4;
  u32   HTR;
  u32   LTR;
  u32   SQR1;
  u32   SQR2;
  u32   SQR3;
  u32   JSQR;
  u32   JDR1;
  u32   JDR2;
  u32   JDR3;
  u32   JDR4;
  u32   DR;

}ADC_t;

#endif /* ADC_PRIVATE_H_ */
