/*
 * ADC.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Youssef Harby
 */


#ifndef ADC_H_
#define ADC_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/
 
#include "std_types.h"
#include "ADC_Types.h"


/********************************************************************************
 * 								API's Declarations								*
 ********************************************************************************/

void ADC_Init(void);

void ADC_StartConversion(void);

void ADC_Read(uint16_t* Result);


#endif /* ADC_H_ */
