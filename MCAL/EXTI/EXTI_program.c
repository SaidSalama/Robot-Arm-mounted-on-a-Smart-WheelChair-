#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"EXTI_interface.h"
#include	"EXTI_private.h"
#include	"DIO_interface.h"
#include    "NVIC_Interface.h"

//#include	"EXTI_config.h"


#ifndef	NULL
#define NULL	(void *)0
#endif


static void	(* EXTI0_CallBack)	(void) = NULL;
static void	(* EXTI1_CallBack)	(void) = NULL;

volatile u8  mode=JOYSTICK_Mode;  /*this variable will be used in main.c as extern varr file to check for the mode
 	 	 	 the external interupt is used to change the value of this variable	 	 */

void	MEXTI_voidInit			(void)
{/*		Initialize Interrupts (Edges)	and pin Number(A0 or B0 or C0)	*/

}
void	MEXTI_voidEnableExti	(u8	Copy_u8ExtiNum)
{	
	SET_BIT( EXTI -> IMR , Copy_u8ExtiNum);
}
void	MEXTI_voidSetExtiEdge	(u8 Copy_u8ExtiNum , u8 Copy_u8Edge)
{
	switch(Copy_u8Edge)
	{
		case	MEXTI_RISING_EDGE	:	CLR_BIT( EXTI -> FSTR , Copy_u8ExtiNum);
										SET_BIT( EXTI -> RSTR , Copy_u8ExtiNum);	break;
		
		case	MEXTI_FALLING_EDGE	:	CLR_BIT( EXTI -> RSTR , Copy_u8ExtiNum);
										SET_BIT( EXTI -> FSTR , Copy_u8ExtiNum);	break;
										
		case	MEXTI_IOC_EDGE		:	SET_BIT( EXTI -> RSTR , Copy_u8ExtiNum);	
										SET_BIT( EXTI -> FSTR , Copy_u8ExtiNum);	break;
	}
}
void	MEXTI_voidDisableExti	(u8	Copy_u8ExtiNum)
{
	CLR_BIT( EXTI -> IMR , Copy_u8ExtiNum);
}
void	MEXTI_voidEnableSWI		(u8	Copy_u8ExtiNum)
{
	SET_BIT( EXTI -> SWIER , Copy_u8ExtiNum);
}
void	MEXTI0_voidSetCallBack	(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		EXTI0_CallBack  = 	ptr ;
	}
}
void	MEXTI1_voidSetCallBack	(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		EXTI1_CallBack  = 	ptr ;
	}
}

void	EXTI0_IRQHandler(void)
{
	EXTI0_CallBack();		//ISR0();
}
void	EXTI1_IRQHandler(void)
{
	EXTI1_CallBack();		//ISR1();
}
void EXTI15_10_IRQHandler()
{
	if(EXTI->PR &(1<<12))				//if it is line 12 was detected
		{
			mode=JOYSTICK_Mode;
			EXTI->PR |=(1<<12);				//clear flag by writing 1 it is a must because if not cleared this function will only respond to EXTI12
		}

	else if(EXTI->PR &(1<<11))				//if it is line 13 was detected
	{
			mode=BCI_Mode;
			EXTI->PR |=(1<<11);
	}
	else if(EXTI->PR &(1<<15))				//if it is line 15 was detected
		{
				mode=EYE_Mode;
				EXTI->PR |=(1<<15);
		}

}
void EXTI9_5_IRQHandler()
{

	 if(EXTI->PR &(1<<7))				//if it is line 7 was detected
		{
				mode=VOICE_Mode;
				EXTI->PR |=(1<<7);
		}
}

void Init_External_Interrupts()
{
	    NVIC_Init();
		NVIC_EnableInterrupt(40);				//enable exti 10:15
		NVIC_SetPriority(40,0);
		NVIC_EnableInterrupt(23);				//enable exti 5:9
		NVIC_SetPriority(23,0);

		DIO_PinMode(GPIOA, 12, INPUT_FLOATING);
		MEXTI_voidEnableExti(12);					//enable interrupt on line 12
		MEXTI_voidSetExtiEdge(12 , MEXTI_RISING_EDGE);

		DIO_PinMode(GPIOA, 11, INPUT_FLOATING);
		MEXTI_voidEnableExti(11);
		MEXTI_voidSetExtiEdge(11 , MEXTI_RISING_EDGE);

		DIO_PinMode(GPIOA, 15, INPUT_FLOATING);
		MEXTI_voidEnableExti(15);
		MEXTI_voidSetExtiEdge(15 , MEXTI_RISING_EDGE);

		DIO_PinMode(GPIOA, 7, INPUT_FLOATING);
		MEXTI_voidEnableExti(7);
		MEXTI_voidSetExtiEdge(7 , MEXTI_RISING_EDGE);

}








