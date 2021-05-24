/*
 * DIO.c
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "tm4c123gh6pm_registers.h"
#include "DIO.h"
#include "DIO_Types.h"

/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define FIRST_BYTE_MASK				0xFF

/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

/* An array of the addresses of the GPIODATA register of each GPIO instance */
uint32_t* ArrayOfDataRegisters[6] = {
	(uint32_t*)(&PORT_A->GPIODATA),
	(uint32_t*)(&PORT_B->GPIODATA),
	(uint32_t*)(&PORT_C->GPIODATA),
	(uint32_t*)(&PORT_D->GPIODATA),
	(uint32_t*)(&PORT_E->GPIODATA),
	(uint32_t*)(&PORT_F->GPIODATA)
};

/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

/* A function to read the required port value into the destination variable */
void DIO_ReadPort(uint8_t GPIO_Port, uint8_t* Destination)
{
	*Destination = (uint8_t)(REGISTER(ArrayOfDataRegisters[GPIO_Port]) & FIRST_BYTE_MASK);
}

/* A function to write a value to the required port */
void DIO_WritePort(uint8_t GPIO_Port, uint8_t Value)
{
	REGISTER(ArrayOfDataRegisters[GPIO_Port]) = Value;
}

/* A function to read a specific channel in a specific port */
void DIO_ReadChannel(uint8_t GPIO_Port, uint8_t GPIO_Channel, uint8_t* Destination)
{
	*Destination = REGISTER(ArrayOfDataRegisters[GPIO_Port]) & (1 << GPIO_Channel)? 1 : 0;
}

/* A function to write a specific channel in a specific port */
void DIO_WriteChannel(uint8_t GPIO_Port, uint8_t GPIO_Channel, uint8_t Value)
{
	/* A switch case to determine whether the required value is high or low */
	switch(Value)
	{
	case DIO_High:
		/* If high, then set the required channel bit.. */
		REGISTER(ArrayOfDataRegisters[GPIO_Port]) |= (1 << GPIO_Channel);
		break;
	case DIO_Low:
		/* And if low, then clear the required channel bit */
		REGISTER(ArrayOfDataRegisters[GPIO_Port]) &= ~(1 << GPIO_Channel);
		break;
	default:
		/* Handle Accordingly */
		break;
	}
}

/* A function to toggle a specific channel in a specific port */
void DIO_ToggleChannel(uint8_t GPIO_Port, uint8_t GPIO_Channel)
{
	REGISTER(ArrayOfDataRegisters[GPIO_Port]) ^= (1 << GPIO_Channel);
}
