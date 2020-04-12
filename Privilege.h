/*
 * privilege.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Youssef Harby
 */

#ifndef PRIVILEGE_H_
#define PRIVILEGE_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "tm4c123gh6pm_registers.h"


/********************************************************************************
 * 								API's Declarations								*
 ********************************************************************************/

void System_switchToPrivileged(void);

void System_switchToUnprivileged(void);


#endif /* PRIVILEGE_H_ */
