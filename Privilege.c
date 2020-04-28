/*
 * Privilege.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "Privilege.h"
#include "tm4c123gh6pm_registers.h"


/********************************************************************************
 * 						  ISR (Interrupt Service Routine)						*
 ********************************************************************************/

void SVC_Handler(void)
{
    asm(
			"MRS R12, CONTROL\n"
            "AND R12, 0b110\n"
            "MSR CONTROL, R12\n"
    );
}


/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

void System_SwitchToPrivileged(void)
{
    asm(
            "SVC #0\n"
    );
}

void System_SwitchToUnPrivileged(void)
{
   asm(
			"MRS R12, CONTROL\n"
            "ORR R12, 1\n"
            "MSR CONTROL, R12\n"
    ); 
}
