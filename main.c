/*
 * main.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "SysCtl.h"
#include "NVIC.h"
#include "Port.h"
#include "DIO.h"
#include "ADC.h"


/********************************************************************************
 *								 Type  Declaration								*
 ********************************************************************************/


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define POTENTIOMETER_MIDWAY_VALUE		2048


/********************************************************************************
 * 							  Global Static Variables							*
 ********************************************************************************/


/********************************************************************************
 * 							  	   Main Function								*
 ********************************************************************************/

int main(void)
{
	/* A variable to store the ADC conversion result. */
	uint16_t au16_Result;

	/* System Initialization. */
	SysCtl_Init();
	NVIC_Init();
	Port_Init();
	
	/* Module Initialization. */
	ADC_Init();

	while(1)
	{
		/* Start the conversion. */
		ADC_StartConversion();
		
		/* Get the conversion result. */
		ADC_Read(&au16_Result);
		
		/* Mini-application on the adc conversion result on two leds for keil simulation */
		if(au16_Result < POTENTIOMETER_MIDWAY_VALUE)
		{
			/* Led4 on and led5 off in case the value is less than half the total value. */
			DIO_WriteChannel(DIO_GPIOD, DIO_Channel_4, DIO_High);
			DIO_WriteChannel(DIO_GPIOD, DIO_Channel_5, DIO_Low);
		}else if(au16_Result >= POTENTIOMETER_MIDWAY_VALUE)
		{
			/* Led5 on and Led4 off in case the value is more than half the total value. */
			DIO_WriteChannel(DIO_GPIOD, DIO_Channel_5, DIO_High);
			DIO_WriteChannel(DIO_GPIOD, DIO_Channel_4, DIO_Low);
		}
	}
}
