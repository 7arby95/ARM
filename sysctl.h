/*
 * privilege.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Youssef Harby
 */


#ifndef SYSCTL_H_
#define SYSCTL_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "sysctl_cfg.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/


/* Definitions of modules clock registers mask */
#define SYSCTL_CLOCK_ENABLED			1
#define SYSCTL_CLOCK_DISABLED			0

/* Watchdog Timer Modules */
#define SYSCTL_WATCHDOG_MODULE_REGMASK			(SYSCTL_WATCHDOG_MODULE_0_STATUS |		\
												(SYSCTL_WATCHDOG_MODULE_1_STATUS << 1))

/* Timer Modules */
#define SYSCTL_TIMER_MODULE_REGMASK				(SYSCTL_TIMER_MODULE_0_STATUS		|	\
												(SYSCTL_TIMER_MODULE_1_STATUS << 1)	|	\
												(SYSCTL_TIMER_MODULE_2_STATUS << 2)	|	\
												(SYSCTL_TIMER_MODULE_3_STATUS << 3)	|	\
												(SYSCTL_TIMER_MODULE_4_STATUS << 4)	|	\
												(SYSCTL_TIMER_MODULE_5_STATUS << 5))

/* Wider Timer Modules */
#define SYSCTL_WTIMER_MODULE_REGMASK			(SYSCTL_WTIMER_MODULE_0_STATUS			|	\
												(SYSCTL_WTIMER_MODULE_1_STATUS << 1)	|	\
												(SYSCTL_WTIMER_MODULE_2_STATUS << 2)	|	\
												(SYSCTL_WTIMER_MODULE_3_STATUS << 3)	|	\
												(SYSCTL_WTIMER_MODULE_4_STATUS << 4)	|	\
												(SYSCTL_WTIMER_MODULE_5_STATUS << 5))

/* GPIO Modules */
#define SYSCTL_GPIO_MODULE_REGMASK				(SYSCTL_GPIO_MODULE_0_STATUS		|	\
												(SYSCTL_GPIO_MODULE_1_STATUS << 1)	|	\
												(SYSCTL_GPIO_MODULE_2_STATUS << 2)	|	\
												(SYSCTL_GPIO_MODULE_3_STATUS << 3)	|	\
												(SYSCTL_GPIO_MODULE_4_STATUS << 4)	|	\
												(SYSCTL_GPIO_MODULE_5_STATUS << 5))

/* Micro Direct Memory Address (UDMA) */
#define SYSCTL_UDMA_MODULE_REGMASK				SYSCTL_UDMA_MODULE_STATUS

/* Hibernation Module */
#define SYSCTL_HIBERNATION_MODULE_REGMASK		SYSCTL_HIBERNATION_MODULE_STATUS

/* UART Modules */
#define SYSCTL_UART_MODULE_REGMASK				(SYSCTL_UART_MODULE_0_STATUS		|	\
												(SYSCTL_UART_MODULE_1_STATUS << 1)	|	\
												(SYSCTL_UART_MODULE_2_STATUS << 2)	|	\
												(SYSCTL_UART_MODULE_3_STATUS << 3)	|	\
												(SYSCTL_UART_MODULE_4_STATUS << 4)	|	\
												(SYSCTL_UART_MODULE_5_STATUS << 5)	|	\
												(SYSCTL_UART_MODULE_6_STATUS << 6)	|	\
												(SYSCTL_UART_MODULE_7_STATUS << 7))

/* SSI (SPI) Modules */
#define SYSCTL_SSI_MODULE_REGMASK				(SYSCTL_SSI_MODULE_0_STATUS			|	\
												(SYSCTL_SSI_MODULE_1_STATUS << 1)	|	\
												(SYSCTL_SSI_MODULE_2_STATUS << 2)	|	\
												(SYSCTL_SSI_MODULE_3_STATUS << 3))

/* I2C Modules */
#define SYSCTL_I2C_MODULE_REGMASK				(SYSCTL_I2C_MODULE_0_STATUS			|	\
												(SYSCTL_I2C_MODULE_1_STATUS << 1)	|	\
												(SYSCTL_I2C_MODULE_2_STATUS << 2)	|	\
												(SYSCTL_I2C_MODULE_3_STATUS << 3))

/* USB Module */
#define SYSCTL_USB_MODULE_REGMASK				SYSCTL_USB_MODULE_STATUS

/* CAN Module */
#define SYSCTL_CAN_MODULE_REGMASK				(SYSCTL_CAN_MODULE_0_STATUS			|	\
												(SYSCTL_CAN_MODULE_1_STATUS << 1))

/* ADC Modules */
#define SYSCTL_ADC_MODULE_REGMASK				(SYSCTL_ADC_MODULE_0_STATUS			|	\
												(SYSCTL_ADC_MODULE_1_STATUS << 1))

/* Analog Comparator Module */
#define SYSCTL_ACMP_MODULE_REGMASK				SYSCTL_ACMP_MODULE_STATUS

/* PWM Modules */
#define SYSCTL_PWM_MODULE_REGMASK				(SYSCTL_PWM_MODULE_0_STATUS			|	\
												(SYSCTL_PWM_MODULE_1_STATUS << 1))

/* Quadrature Encoder Interface Modules */
#define SYSCTL_QEI_MODULE_REGMASK				(SYSCTL_QEI_MODULE_0_STATUS			|	\
												(SYSCTL_QEI_MODULE_1_STATUS << 1))

/* EEPROM Module */
#define SYSCTL_EEPROM_MODULE_REGMASK			SYSCTL_EEPROM_MODULE_STATUS


/********************************************************************************
 * 								API's Declarations								*
 ********************************************************************************/

void Sysctl_init(void);


#endif /* SYSCTL_H_ */
