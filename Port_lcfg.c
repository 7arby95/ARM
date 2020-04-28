/*
 * Port_lcfg.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "Port_lcfg.h"


/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS] =
{/*	 Channel					PortDriver_Channel_Direction				PortDriver_Channel_Current_mA			PortDriver_Channel_SlewRate					PortDriver_Channel_Attachment					PortDriver_Channel_Function				PortDriver_Channel_Exti					PortDriver_Channel_ADFunctionType*/				
	{PortDriver_Channel_E3,		PortDriver_Channel_Direction_INPUT,			PortDriver_Channel_Current_mA_2,		PortDriver_Channel_SlewRate_Disable,		PortDriver_Channel_Attachment_NotConnected,		PortDriver_Channel_Function_X_DIO,		PortDriver_Channel_Exti_Disable,		PortDriver_Channel_ADFunction_Analog}
};

/*
	The previous structures are for the purpose of debugging and register checking.. change
	them into the desired channels with the suitable options
*/
