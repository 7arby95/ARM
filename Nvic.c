/*
 * NVIC.c
 *
 *  Created on: Apr 8, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "tm4c123gh6pm_registers.h"
#include "NVIC.h"
#include "NVIC_lcfg.h"
#include "privilege.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define USE_COMBINATION(COMB)		(COMB + 4)


/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

void NVIC_Init(void)
{
	/* An item required to loop the array of interrupt structures */
	uint8_t au8_Counter;
	
	/* Items required to make the final equation easier */
	uint8_t au8_numberOfReservedBlocks;
	uint8_t au8_numberOfIntPriBlocks;
	uint8_t au8_numberOfShifts;
	uint8_t au8_priorityBits;

	/* Two pointers to represent the two registers required addresses; EN, PRI */
	uint32_t* pu8_PointerToEN_Reg;
	uint32_t* pu8_PointerToPRI_Reg;
	
	/* Items required to possess each structure contents */
	IntNumType NVIC_IntNum;
	Group_PriorityType NVIC_Group_Priority;
	SubGroup_PriorityType	NVIC_SubGroup_Priority;
	
	/* Switch first to privileged mode to be able to use the PRI and EN registers */
	System_SwitchToPrivileged();
	
	/* Set the user's required combination XXX XXY XYY YYY */
	REGISTER(SCB_APINT_R) |= (SCB_APINT_VECTKEY_VALUE << SCB_APINT_VECTKEY_B16)| USE_COMBINATION(REQUIRED_COMBINATION);
	
	/* Looping the array of structures to enable the required interrupts */
	for(au8_Counter = 0 ; au8_Counter < NUM_OF_ACTIVATED_INTERRUPTS ; au8_Counter++)
	{
		/* Holding the structure elements in our variables */
		NVIC_IntNum = NVIC_CfgArr[au8_Counter].IntNum;
		NVIC_Group_Priority = NVIC_CfgArr[au8_Counter].Group_Priority;
		NVIC_SubGroup_Priority = NVIC_CfgArr[au8_Counter].SubGroup_Priority;
		
		/** Enable Interrupt **/
		/* This line is an equation to make the pointer have the required register address */
		pu8_PointerToEN_Reg = (uint32_t*)(&EN_REGS) + (NVIC_IntNum / REGISTER_SIZE_IN_BITS);
		
		/* And this equation is used to enable the required interrupt */
		REGISTER(pu8_PointerToEN_Reg) |= (1 << (NVIC_IntNum % REGISTER_SIZE_IN_BITS));		
		
		/** Set Priority Group/SubGroup **/
		/* This line is an equation to make the pointer have the required register address */
		pu8_PointerToPRI_Reg = (uint32_t*)(&PRI_REGS) + (NVIC_IntNum / REGISTER_SIZE_IN_BYTES);
		
		/* The following three lines are equations to make the final equation easier */
		au8_numberOfIntPriBlocks = NVIC_IntNum % REGISTER_SIZE_IN_BYTES;
		au8_numberOfReservedBlocks = au8_numberOfIntPriBlocks + 1;
		/* Here, we have the final number of shifts needed to write in the suitable bits in the register */
		au8_numberOfShifts = (au8_numberOfIntPriBlocks * 3) + (au8_numberOfReservedBlocks * 5);
		
		/* This line is an equation to calculate the value to be put into the three priority bits */
		au8_priorityBits = NVIC_SubGroup_Priority | (NVIC_Group_Priority << REQUIRED_COMBINATION);
		
		/* The final equation to place the right priority bits into the right bitfields */
		REGISTER(pu8_PointerToPRI_Reg) |= (au8_priorityBits << au8_numberOfShifts);
	}

	/* Switch back to unprivileged mode */
	System_SwitchToPrivileged();	
}
