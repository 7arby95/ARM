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

extern ADC_ERROR_STATUS ADC_Init(void);

extern ADC_ERROR_STATUS ADC_StartConversion(void);

extern ADC_ERROR_STATUS ADC_Read(uint16_t* Result);


#endif /* ADC_H_ */
