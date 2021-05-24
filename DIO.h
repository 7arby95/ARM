/*
 * DIO.h
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


#ifndef DIO_H_
#define DIO_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/
 
#include "std_types.h"
#include "DIO_Types.h"


/********************************************************************************
 * 								API's Declarations								*
 ********************************************************************************/

void DIO_ReadPort(uint8_t GPIO_Port, uint8_t* Destination);
void DIO_WritePort(uint8_t GPIO_Port, uint8_t Value);
void DIO_ReadChannel(uint8_t GPIO_Port, uint8_t GPIO_Channel, uint8_t* Destination);
void DIO_WriteChannel(uint8_t GPIO_Port, uint8_t GPIO_Channel, uint8_t Value);
void DIO_ToggleChannel(uint8_t GPIO_Port, uint8_t GPIO_Channel);


#endif /* DIO_H_ */
