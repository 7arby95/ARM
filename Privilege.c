/*
 * privilege.c
 *
 *  Created on: Apr 6, 2020
 *      Author: Youssef Harby
 */

#include "Privilege.h"


/********************************************************************************
 * 						  ISR (Interrupt Service Routine)						*
 ********************************************************************************/

void SVC_Handler(void)
{
    asm(
			"MRS R12, CONTROL\n"
            "AND R12, 0\n"
            "MSR CONTROL, R12\n"
    );
}


/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

void System_switchToPrivileged(void)
{
    asm(
            "SVC #0\n"
    );
}

void System_switchToUnprivileged(void)
{
   asm(
			"MRS R12, CONTROL\n"
            "ORR R12, 1\n"
            "MSR CONTROL, R12\n"
    ); 
}
