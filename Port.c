/*
 * Port.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "tm4c123gh6pm_registers.h"
#include "Port.h"
#include "Port_lcfg.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define NUM_OF_CHANNELS_IN_PORT		8

#define GPIOIS_MASK					0b100
#define GPIOIBE_MASK				0b1000
#define GPIOIEV_MASK				0b01

#define GPIOLOCK_KEY				0x4C4F434B

/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

/*
	An array of pointers to structures, each structure contains the addresses of each GPIO instance, this array is
	used to make the register accessing easier
*/
PointerToPortRegisters ArrayOfPortRegisters[6] = {
	(PORT_RegType*)PORT_A,
	(PORT_RegType*)PORT_B,
	(PORT_RegType*)PORT_C,
	(PORT_RegType*)PORT_D,
	(PORT_RegType*)PORT_E,
	(PORT_RegType*)PORT_F
};

/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

void Port_Init(void)
{
	/* An item required to loop the array of GPIO structures */
	uint8_t au8_Counter;
	
	/* Items required to make the equations easier */
	PortDriver_PortNumType PortNum;
	PortDriver_ChannelType ChannelNum;
	uint8_t au8_ChannelOffset;
	
	/* Two pointers to represent the suitable registers when it comes to mA or attachment selection */
	uint32_t* PointerTo_mA_Regs;
	uint32_t* PointerTo_Attachment_Regs;
	
	/* Looping the array of GPIO structures, each structure represents a channel in a port */
	for(au8_Counter=0 ; au8_Counter<NUM_OF_ACTIVATED_CHANNELS ; au8_Counter++)
	{
		/* Holding the ChannelNum from the structure in our variable */
		ChannelNum = PortDriver_CfgArr[au8_Counter].Channel;
		/* A calculation to find the right channel offset */
		au8_ChannelOffset = ChannelNum % NUM_OF_CHANNELS_IN_PORT;
		/* A calculation to find the right port number */
		PortNum = (PortDriver_PortNumType)(ChannelNum / NUM_OF_CHANNELS_IN_PORT);
		
		/* Calculations to make the pointers point at the right register to be manipulated */
		PointerTo_mA_Regs = (uint32_t*)(&ArrayOfPortRegisters[PortNum]->GPIODR2R) \
						  + PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Current_mA;
		PointerTo_Attachment_Regs = (uint32_t*)(&ArrayOfPortRegisters[PortNum]->GPIOODR) \
								  + (PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Attachment - 1);
		
		/* Selection of the channel direction */
		ArrayOfPortRegisters[PortNum]->GPIODIR |= ((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Direction) << au8_ChannelOffset);
	
		/* The two following lines are used in order to be able to write to some registers, GPIOAFSEL, GPIOPDR, GPIOPUR and GPIODEN */
		ArrayOfPortRegisters[PortNum]->GPIOLOCK = GPIOLOCK_KEY;
		ArrayOfPortRegisters[PortNum]->GPIOCR |= (1 << au8_ChannelOffset);
		
		/* Selection of whether the function needed is alternate function or not */
		ArrayOfPortRegisters[PortNum]->GPIOAFSEL |= (((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Function)? 1 : 0) << au8_ChannelOffset);
		/* In case of an alternate function, the right value is then written to the GPIOPCTL register */
		ArrayOfPortRegisters[PortNum]->GPIOPCTL |= (PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Function << (au8_ChannelOffset * 4));
		
		/* Selection of the required mA drive option */
		REGISTER(PointerTo_mA_Regs) |= (1 << au8_ChannelOffset);

		/* Selection of the required attachment (pull up resistance, pull down resistance or open drain) */
		REGISTER(PointerTo_Attachment_Regs) |= ((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Attachment & 0b11? 1 : 0) << au8_ChannelOffset);
		
		/* Selection whether the slew rate option is activated or not */
		ArrayOfPortRegisters[PortNum]->GPIOSLR |= ((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_SlewRate) << au8_ChannelOffset);
		
		/* Selection of the digital signal option */
		ArrayOfPortRegisters[PortNum]->GPIODEN |= (1 << au8_ChannelOffset);
		
		/* In case the external interrupt option is required.. */
		if(PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Exti != PortDriver_Channel_Exti_Disable)
		{
/*
			1. Mask the corresponding port by clearing the IME field in the GPIOIM register.
*/
			ArrayOfPortRegisters[PortNum]->GPIOIM &= ~(1 << au8_ChannelOffset);
/*
			2. Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE register.
*/
			ArrayOfPortRegisters[PortNum]->GPIOIS |= ((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Exti & GPIOIS_MASK? 1 : 0) \
												  << au8_ChannelOffset);
			ArrayOfPortRegisters[PortNum]->GPIOIBE |= ((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Exti & GPIOIBE_MASK? 1 : 0) \
												   << au8_ChannelOffset);
			ArrayOfPortRegisters[PortNum]->GPIOIEV |= ((PortDriver_CfgArr[au8_Counter].PortDriver_Channel_Exti & GPIOIEV_MASK? 1 : 0) \
												   << au8_ChannelOffset);
/*
			3. Clear the GPIORIS register.
*/
			ArrayOfPortRegisters[PortNum]->GPIOICR |= (1 << au8_ChannelOffset);
/*
			4. Unmask the port by setting the IME field in the GPIOIM register.
*/
			ArrayOfPortRegisters[PortNum]->GPIOIM |= (1 << au8_ChannelOffset);
		}
		/* Otherwise.. */
		else
		{
			/* Do nothing */
		}
	}
}
