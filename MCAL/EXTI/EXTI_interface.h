#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

void	MEXTI_voidInit			(void);
void	MEXTI_voidEnableExti	(u8	Copy_u8ExtiNum);
void	MEXTI_voidSetExtiEdge	(u8 Copy_u8ExtiNum , u8 Copy_u8Edge);
void	MEXTI_voidDisableExti	(u8	Copy_u8ExtiNum);
void	MEXTI_voidEnableSWI		(u8	Copy_u8ExtiNum);
void	MEXTI_voidSetCallBack	(void (*ptr) (void));

#define	MEXTI_RISING_EDGE			0
#define	MEXTI_FALLING_EDGE			1
#define	MEXTI_IOC_EDGE				2

#define	MEXTI_LINE0					0
#define	MEXTI_LINE1					1
#define	MEXTI_LINE2					2

#define JOYSTICK_Mode 				1
#define BCI_Mode 					2
#define EYE_Mode 					3
#define VOICE_Mode 				4


#endif
