/*
 * NVIC_lcfg.c
 *
 *  Created on: Apr 8, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "NVIC_lcfg.h"


/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

NVIC_CfgType NVIC_CfgArr[NUM_OF_ACTIVATED_INTERRUPTS] = 
{/*IntNum				Group_Priority			SubGroup_Priority */
	{GPIOA_IRQn,			2,						0					},
	{GPIOB_IRQn,			1,						1					},
	{GPIOF_IRQn,			2,						1					},
	{UART0_IRQn,			0,						1					}
};
