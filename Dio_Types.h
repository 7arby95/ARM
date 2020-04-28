/*
 * DIO_Types.h
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "std_types.h"
#include "tm4c123gh6pm_registers.h"

/********************************************************************************
 *								 Type  Declaration								*
 ********************************************************************************/

typedef enum{
	DIO_GPIOA,
	DIO_GPIOB,
	DIO_GPIOC,
	DIO_GPIOD,
	DIO_GPIOE,
	DIO_GPIOF
}DIO_PortType;

typedef enum{
	DIO_Channel_0,
	DIO_Channel_1,
	DIO_Channel_2,
	DIO_Channel_3,
	DIO_Channel_4,
	DIO_Channel_5,
	DIO_Channel_6,
	DIO_Channel_7
}DIO_ChannelType;

typedef enum{
	DIO_Low,
	DIO_High
}DIO_ValueType;


#endif /* DIO_TYPES_H_ */
