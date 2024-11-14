#ifndef			NVIC_INTERFACE_H
#define			NVIC_INTERFACE_H

void	NVIC_Init				(void);
void	NVIC_EnableInterrupt	(u8 Copy_u8IntNum);
void	NVIC_DisableInterrupt	(u8 Copy_u8IntNum);
void	NVIC_SetPendingFlag	(u8 Copy_u8IntNum);
void	NVIC_ClearPendingFlag	(u8 Copy_u8IntNum);
u8		NVIC_GetActiveFlag		(u8 Copy_u8IntNum);
void	NVIC_SetPriority		(u8 Copy_u8IntNum,u8 Copy_u8Priority);
void NVIC_Software_Reset();

#endif







