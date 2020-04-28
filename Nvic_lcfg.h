/*
 * NVIC_lcfg.h
 *
 *  Created on: Apr 8, 2020
 *      Author: Youssef Harby
 */


#ifndef NVIC_LCFG_H_
#define NVIC_LCFG_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "NVIC_Types.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define REQUIRED_COMBINATION								XXY
#define NUM_OF_ACTIVATED_INTERRUPTS							5


/********************************************************************************
 * 								 External Variables								*
 ********************************************************************************/

extern NVIC_CfgType NVIC_CfgArr[];


#endif /* NVIC_LCFG_H_ */
