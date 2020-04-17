/*
 * Port_lcfg.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


#include "Port_lcfg.h"


/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

PortDriver_CfgType PortDriver_CfgArr[NUM_OF_ACTIVATED_CHANNELS] =
{/*	 Channel					PortDriver_Channel_Direction				PortDriver_Channel_Current_mA			PortDriver_Channel_SlewRate					PortDriver_Channel_Attachment					PortDriver_Channel_Function				PortDriver_Channel_Exti	*/
	{PortDriver_Channel_A0,		PortDriver_Channel_Direction_OUTPUT,		PortDriver_Channel_Current_mA_2,		PortDriver_Channel_SlewRate_Disable,		PortDriver_Channel_Attachment_NotConnected,		PortDriver_Channel_Function_X_DIO,		PortDriver_Channel_Exti_Disable},
	{PortDriver_Channel_B1,		PortDriver_Channel_Direction_OUTPUT,		PortDriver_Channel_Current_mA_2,		PortDriver_Channel_SlewRate_Disable,		PortDriver_Channel_Attachment_NotConnected,		PortDriver_Channel_Function_X_DIO,		PortDriver_Channel_Exti_Disable},
	{PortDriver_Channel_D2,		PortDriver_Channel_Direction_OUTPUT,		PortDriver_Channel_Current_mA_2,		PortDriver_Channel_SlewRate_Disable,		PortDriver_Channel_Attachment_NotConnected,		PortDriver_Channel_Function_X_DIO,		PortDriver_Channel_Exti_Disable},
	{PortDriver_Channel_E3,		PortDriver_Channel_Direction_OUTPUT,		PortDriver_Channel_Current_mA_2,		PortDriver_Channel_SlewRate_Disable,		PortDriver_Channel_Attachment_NotConnected,		PortDriver_Channel_Function_X_DIO,		PortDriver_Channel_Exti_Disable},
	{PortDriver_Channel_F4,		PortDriver_Channel_Direction_OUTPUT,		PortDriver_Channel_Current_mA_2,		PortDriver_Channel_SlewRate_Disable,		PortDriver_Channel_Attachment_NotConnected,		PortDriver_Channel_Function_X_DIO,		PortDriver_Channel_Exti_Disable}
};

/*
	The previous structures are not for the purpose of debugging and register checking.. change
	them into the desired channels with the suitable options
*/
