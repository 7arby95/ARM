/*
 * tm4c123gh6pm_registers.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Youssef Harby
 */

#ifndef TM4C123GH6PM_REGISTERS_H_
#define TM4C123GH6PM_REGISTERS_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "std_types.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define ALIAS_BASE_ADDRESS				0x42000000
#define PERIPHERAL_REG_BASE_ADDRESS		0x40000000
#define REGISTER_SIZE_IN_BYTES			4
#define REGISTER_SIZE_IN_BITS			32
#define BYTE_WIDTH						8

#define WRITE_BIT(REG_ADDRESS, BIT_OFFSET)  (*((volatile uint32_t*)(ALIAS_BASE_ADDRESS +													\
											(REG_ADDRESS - PERIPHERAL_REG_BASE_ADDRESS + BIT_OFFSET / BYTE_WIDTH) * REGISTER_SIZE_IN_BITS +	\
											(BIT_OFFSET % BYTE_WIDTH) * REGISTER_SIZE_IN_BYTES)))
											
											
#define READ_BIT(REG_ADDRESS, BIT_OFFSET)	((*((volatile uint32_t*)(REG_ADDRESS))) & (1 << BIT_OFFSET))

#define REGISTER(REG_ADDRESS)				(*((volatile uint32_t*)(REG_ADDRESS)))


/* SYSCTL Registers */
/* Register RCC and its bits definition */
#define SYSCTL_RCC_R            0x400FE060

#define SYSCTL_RCC_MOSCDIS_B0		0
#define SYSCTL_RCC_OSCSRC_B4		4
#define SYSCTL_RCC_OSCSRC_B5		5
#define SYSCTL_RCC_XTAL_B6			6
#define SYSCTL_RCC_XTAL_B7			7
#define SYSCTL_RCC_XTAL_B8			8
#define SYSCTL_RCC_XTAL_B9			9
#define SYSCTL_RCC_XTAL_B10			10
#define SYSCTL_RCC_BYPASS_B11		11
#define SYSCTL_RCC_PWRDN_B13		13
#define SYSCTL_RCC_PWMDIV_B17		17
#define SYSCTL_RCC_PWMDIV_B18		18
#define SYSCTL_RCC_PWMDIV_B19		19
#define SYSCTL_RCC_USEPWMDIV_B20	20
#define SYSCTL_RCC_USESYSDIV_B22	22
#define SYSCTL_RCC_SYSDIV_B23		23
#define SYSCTL_RCC_SYSDIV_B24		24
#define SYSCTL_RCC_SYSDIV_B25		25
#define SYSCTL_RCC_SYSDIV_B26		26
#define SYSCTL_RCC_ACG_B27			27


/* Register RCC2 and its bits definition */
#define SYSCTL_RCC2_R           0x400FE070

#define SYSCTL_RCC2_OSCSRC2_B4		4
#define SYSCTL_RCC2_OSCSRC2_B5		5
#define SYSCTL_RCC2_OSCSRC2_B6		6
#define SYSCTL_RCC2_BYPASS2_B11		11
#define SYSCTL_RCC2_PWRDN2_B13		13
#define SYSCTL_RCC2_USBPWRDN_B14	14
#define SYSCTL_RCC2_SYSDIV2LSB_B22	22
#define SYSCTL_RCC2_SYSDIV2_B23		23
#define SYSCTL_RCC2_SYSDIV2_B24		24
#define SYSCTL_RCC2_SYSDIV2_B25		25
#define SYSCTL_RCC2_SYSDIV2_B26		26
#define SYSCTL_RCC2_SYSDIV2_B27		27
#define SYSCTL_RCC2_SYSDIV2_B28		28
#define SYSCTL_RCC2_DIV400_B30		30
#define SYSCTL_RCC2_USERCC2_B31		31


/* Register RIS and its bits definition */
#define SYSCTL_RIS_R			0x400FE050

#define SYSCTL_RIS_BOR1RIS_B1		1
#define SYSCTL_RIS_MOFRIS_B3		3
#define SYSCTL_RIS_PLLLRIS_B6		6
#define SYSCTL_RIS_USBPLLLRIS_B7	7
#define SYSCTL_RIS_MOSCPUPRIS_B8	8
#define SYSCTL_RIS_VDDARIS_B10		10
#define SYSCTL_RIS_BOR0RIS_B11		11

/* RCGC Registers */
#define SYSCTL_RCGCWD_R				0x400FE600
#define SYSCTL_RCGCTIMER_R			0x400FE604
#define SYSCTL_RCGCGPIO_R			0x400FE608
#define SYSCTL_RCGCDMA_R			0x400FE60C

#define SYSCTL_RCGCHIB_R			0x400FE614
#define SYSCTL_RCGCUART_R			0x400FE618
#define SYSCTL_RCGCSSI_R			0x400FE61C
#define SYSCTL_RCGCI2C_R			0x400FE620

#define SYSCTL_RCGCUSB_R			0x400FE628
#define SYSCTL_RCGCCAN_R			0x400FE634
#define SYSCTL_RCGCADC_R			0x400FE638
#define SYSCTL_RCGCACMP_R			0x400FE63C

#define SYSCTL_RCGCPWM_R			0x400FE640
#define SYSCTL_RCGCQEI_R			0x400FE644
#define SYSCTL_RCGCEEPROM_R			0x400FE658
#define SYSCTL_RCGCWTIMER_R			0x400FE65C

/* SCB Registers */
/* Register APINT  and its bits definition */
#define SCB_APINT_R					0xE000ED0C

#define SCB_APINT_PRIGROUP_B8		8			/* Bits 8, 9 and 10 */
#define SCB_APINT_VECTKEY_B16		16			/* Bits from 16 to 31 */
#define SCB_APINT_VECTKEY_VALUE		0x05FA

/* NVIC Registers */
/* Register PRI0 definition */
#define NVIC_PRI0_R					0xE000E400

typedef struct{
	uint32_t PRI0;
	uint32_t PRI1;
	uint32_t PRI2;
	uint32_t PRI3;
	uint32_t PRI4;
	uint32_t PRI5;
	uint32_t PRI6;
	uint32_t PRI7;
	uint32_t PRI8;
	uint32_t PRI9;
	uint32_t PRI10;
	uint32_t PRI11;
	uint32_t PRI12;
	uint32_t PRI13;
	uint32_t PRI14;
	uint32_t PRI15;
	uint32_t PRI16;
	uint32_t PRI17;
	uint32_t PRI18;
	uint32_t PRI19;
	uint32_t PRI20;
	uint32_t PRI21;
	uint32_t PRI22;
	uint32_t PRI23;
	uint32_t PRI24;
	uint32_t PRI25;
	uint32_t PRI26;
	uint32_t PRI27;
	uint32_t PRI28;
	uint32_t PRI29;
	uint32_t PRI30;
	uint32_t PRI31;
	uint32_t PRI32;
	uint32_t PRI33;
	uint32_t PRI34;
}PRI_RegType;

#define PRI_REGS					(*((volatile PRI_RegType*)NVIC_PRI0_R))

/* Register PRI0 definition */
#define NVIC_EN0_R					0xE000E100

typedef struct{
	uint32_t EN0;
	uint32_t EN1;
	uint32_t EN2;
	uint32_t EN3;
	uint32_t EN4;
}EN_RegType;

#define EN_REGS					(*((volatile EN_RegType*)NVIC_EN0_R))


#endif /* TM4C123GH6PM_REGISTERS_H_ */
