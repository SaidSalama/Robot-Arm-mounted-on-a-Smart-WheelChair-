#ifndef			NVIC_PRIVATE_H
#define			NVIC_PRIVATE_H

/*               THE ADDRESSES ARE NOT DEFINED IN STRUCT TYPE BECAUSE OFFSET ADDDRESSES  ARE NOT IN SERIES */

#define			NVIC_BASE_ADD		(0xE000E100)
/*				Enable for the external interrupts from 0 to 31			*/
#define			NVIC_ISER0			*((volatile u32 *)(NVIC_BASE_ADD+0x00))//*((volatile u32 *)0xE000E100)
/*				Enable for the external interrupts from 32 to 63		*/
#define			NVIC_ISER1			*((volatile u32 *)(NVIC_BASE_ADD+0x04))//*((volatile u32 *)0xE000E104)
/*				Enable for the external interrupts from 64 to 85		*/
#define			NVIC_ISER2			*((volatile u32 *)(NVIC_BASE_ADD+0x08))//*((volatile u32 *)0xE000E108)		*/

#define			NVIC_ICER0			*((volatile u32 *)(NVIC_BASE_ADD+0x80))
#define			NVIC_ICER1			*((volatile u32 *)(NVIC_BASE_ADD+0x84))
#define			NVIC_ICER2			*((volatile u32 *)(NVIC_BASE_ADD+0x88))

#define			NVIC_ISPR0			*((volatile u32 *)(NVIC_BASE_ADD+0x100))
#define			NVIC_ISPR1			*((volatile u32 *)(NVIC_BASE_ADD+0x104))
#define			NVIC_ISPR2			*((volatile u32 *)(NVIC_BASE_ADD+0x108))

#define			NVIC_ICPR0			*((volatile u32 *)(NVIC_BASE_ADD+0x180))
#define			NVIC_ICPR1			*((volatile u32 *)(NVIC_BASE_ADD+0x184))
#define			NVIC_ICPR2			*((volatile u32 *)(NVIC_BASE_ADD+0x188))

#define			NVIC_IABR0			*((volatile u32 *)(NVIC_BASE_ADD+0x200))
#define			NVIC_IABR1			*((volatile u32 *)(NVIC_BASE_ADD+0x204))
#define			NVIC_IABR2			*((volatile u32 *)(NVIC_BASE_ADD+0x208))

#define			NVIC_IPR			((volatile u8 *)(NVIC_BASE_ADD+0x300))//u8 it means that ipr0 for interrupt 0 and ipr1 for interrupt1 and so on
/* in datasheet ipr0 is for interrupt 0,1,2,3 and so on but in this case it will be u32 */

#define			MNVIC_16_GROUP_0_SUB			(0x05FA0300)
#define			MNVIC_8_GROUP_2_SUB				(0x05FA0400)
#define			MNVIC_4_GROUP_4_SUB				(0x05FA0500)
#define			MNVIC_2_GROUP_8_SUB				(0x05FA0600)
#define			MNVIC_0_GROUP_16_SUB			(0x05FA0700)

#endif







