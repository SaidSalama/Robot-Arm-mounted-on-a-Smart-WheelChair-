#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"NVIC_interface.h"
#include	"NVIC_private.h"
#include	"NVIC_config.h"




void	NVIC_Init				(void)				//Initialize the group priority bits
{
	#ifndef	SCB_AIRCR
		#define	SCB_AIRCR		*((volatile u32 *)(0xE000ED00 + 0x0C))
	#endif
	SCB_AIRCR = MNVIC_GRP_SUB;
}
void NVIC_Software_Reset()
{
	SCB_AIRCR=MNVIC_GRP_SUB|(1<<2);
}
void	NVIC_EnableInterrupt	(u8 IntNum) //55
{
	/*		Ranage	Check 		*/
	if(IntNum < 32)
	{
		NVIC_ISER0 = (1<<IntNum);				//'=' not '|=' because 0 has no effect
	}else if(IntNum < 64)
	{
		IntNum -= 32 ;
		NVIC_ISER1 = (1<<IntNum);
	}else if(IntNum < 86)
	{
		IntNum -= 64 ;
		NVIC_ISER2 = (1<<IntNum);
	}else{		/*	return Error 			*/}		
}
void	NVIC_DisableInterrupt	(u8 IntNum)
{
	/*		Ranage	Check 		*/
	if(IntNum < 32)
	{
		NVIC_ICER0 = (1<<IntNum);
	}else if(IntNum < 64)
	{
		IntNum -= 32 ;
		NVIC_ICER1 = (1<<IntNum);
	}else if(IntNum < 86)
	{
		IntNum -= 64 ;
		NVIC_ICER2 = (1<<IntNum);
	}else{		/*	return Error 			*/}	
}
void	NVIC_SetPendingFlag	(u8 IntNum)
{
	/*		Ranage	Check 		*/
	if(IntNum < 32)
	{
		NVIC_ISPR0 = (1<<IntNum);
	}else if(IntNum < 64)
	{
		IntNum -= 32 ;
		NVIC_ISPR1 = (1<<IntNum);
	}else if(IntNum < 86)
	{
		IntNum -= 64 ;
		NVIC_ISPR2 = (1<<IntNum);
	}else{		/*	return Error 			*/}	
}
void	NVIC_ClearPendingFlag	(u8 IntNum)
{
	/*		Ranage	Check 		*/
	if(IntNum < 32)
	{
		NVIC_ICPR0 = (1<<IntNum);
	}else if(IntNum < 64)
	{
		IntNum -= 32 ;
		NVIC_ICPR1 = (1<<IntNum);
	}else if(IntNum < 86)
	{
		IntNum -= 64 ;
		NVIC_ICPR2 = (1<<IntNum);
	}else{		/*	return Error 			*/}	
}
u8		NVIC_GetActiveFlag		(u8 IntNum)
{
	u8 Local_u8Value = 0x55 ;
	/*		Ranage	Check 		*/
	if(IntNum < 32)
	{
		Local_u8Value	=	GET_BIT(NVIC_IABR0,IntNum);
	}else if(IntNum < 64)
	{
		IntNum -= 32 ;
		Local_u8Value	=	GET_BIT(NVIC_IABR1,IntNum);
	}else if(IntNum < 86)
	{
		IntNum -= 64 ;
		Local_u8Value	=	GET_BIT(NVIC_IABR2,IntNum);
	}else{		/*	return Error 	*/		}
	return Local_u8Value;
}


void	NVIC_SetPriority		(u8 IntNum,u8 Priority)
{
	/*		Range Check 				*/
	if(IntNum < 82)
	{
		NVIC_IPR[IntNum] =	(Priority<<4);		//shifted by 4 because 4 bits is used for priority grouping if not 4 we shift by another number
	}
	
}
