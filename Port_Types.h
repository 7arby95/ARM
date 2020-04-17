/*
 * Port_Types.h
 *
 *  Created on: Apr 14, 2020
 *      Author: Youssef Harby
 */


#ifndef PORT_TYPES_H_
#define PORT_TYPES_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "std_types.h"


/********************************************************************************
 *								 Type  Declaration								*
 ********************************************************************************/

typedef uint8_t PortDriver_Channel_DirectionType;
#define PortDriver_Channel_Direction_INPUT			 	0
#define PortDriver_Channel_Direction_OUTPUT				1

typedef uint8_t PortDriver_Channel_Current_mAType;
#define PortDriver_Channel_Current_mA_2			 		0
#define PortDriver_Channel_Current_mA_4			 		1
#define PortDriver_Channel_Current_mA_8			 		2
			
typedef uint8_t PortDriver_Channel_SlewRateType;
#define PortDriver_Channel_SlewRate_Disable				0
#define PortDriver_Channel_SlewRate_Enable				1

typedef uint8_t PortDriver_Channel_AttachmentType;
#define PortDriver_Channel_Attachment_NotConnected		0
#define PortDriver_Channel_Attachment_openDrain			1
#define PortDriver_Channel_Attachment_PullUpRes 		2
#define PortDriver_Channel_Attachment_PullDownRes		3

typedef uint8_t PortDriver_Channel_FunctionType;
#define PortDriver_Channel_Function_X_DIO				0

#define PortDriver_Channel_Function_A0_U0RX				1
#define PortDriver_Channel_Function_A0_CAN1RX			8
#define PortDriver_Channel_Function_A1_U0TX				1
#define PortDriver_Channel_Function_A1_CAN1TX			8
#define PortDriver_Channel_Function_A2_SSI0CLK			2
#define PortDriver_Channel_Function_A3_SSI0FSS			2
#define PortDriver_Channel_Function_A4_SSI0RX			2
#define PortDriver_Channel_Function_A5_SSI0TX			2
#define PortDriver_Channel_Function_A6_I2C1SCL			3
#define PortDriver_Channel_Function_A6_M1PWM2			5
#define PortDriver_Channel_Function_A7_I2C1SDA			3
#define PortDriver_Channel_Function_A7_M1PWM3			5

#define PortDriver_Channel_Function_B0_U1RX				1
#define PortDriver_Channel_Function_B0_T2CCP0			7
#define PortDriver_Channel_Function_B1_U1TX				1
#define PortDriver_Channel_Function_B1_T2CCP1			7
#define PortDriver_Channel_Function_B2_I2C0SCL			3
#define PortDriver_Channel_Function_B2_T3CCP0			7
#define PortDriver_Channel_Function_B3_I2C0SDA			3
#define PortDriver_Channel_Function_B3_T3CCP1			7
#define PortDriver_Channel_Function_B4_SSI2CLK			2
#define PortDriver_Channel_Function_B4_M0PWM2			4
#define PortDriver_Channel_Function_B4_T1CCP0			7
#define PortDriver_Channel_Function_B4_CAN0RX			8
#define PortDriver_Channel_Function_B5_SSI2FSS			2
#define PortDriver_Channel_Function_B5_M0PWM3			4
#define PortDriver_Channel_Function_B5_T1CCP1			7
#define PortDriver_Channel_Function_B5_CAN0TX			8
#define PortDriver_Channel_Function_B6_SSI2RX			2
#define PortDriver_Channel_Function_B6_M0PWM0			4
#define PortDriver_Channel_Function_B6_T0CCP0			7
#define PortDriver_Channel_Function_B7_SSI2TX			2
#define PortDriver_Channel_Function_B7_M0PWM1			4
#define PortDriver_Channel_Function_B7_T0CCP1			7

/* PC3:0 are used for JTAG/SWD so they are unprogrammable */
#define PortDriver_Channel_Function_C4_U4RX				1
#define PortDriver_Channel_Function_C4_U1RX				2
#define PortDriver_Channel_Function_C4_M0PWM6			4
#define PortDriver_Channel_Function_C4_IDX1				6
#define PortDriver_Channel_Function_C4_WT0CCP0			7
#define PortDriver_Channel_Function_C4_U1RTS			8
#define PortDriver_Channel_Function_C5_U4TX				1
#define PortDriver_Channel_Function_C5_U1TX				2
#define PortDriver_Channel_Function_C5_M0PWM7			4
#define PortDriver_Channel_Function_C5_PHA1				6
#define PortDriver_Channel_Function_C5_WT0CCP1			7
#define PortDriver_Channel_Function_C5_U1CTS			8
#define PortDriver_Channel_Function_C6_U3RX				1
#define PortDriver_Channel_Function_C6_PHB1				6
#define PortDriver_Channel_Function_C6_WT1CCP0			7
#define PortDriver_Channel_Function_C6_USB0EPEN			8
#define PortDriver_Channel_Function_C7_U3TX				1
#define PortDriver_Channel_Function_C7_WT1CCP1			7
#define PortDriver_Channel_Function_C7_USB0PFLT			8

#define PortDriver_Channel_Function_D0_SSI3CLK			1
#define PortDriver_Channel_Function_D0_SSI1CLK			2
#define PortDriver_Channel_Function_D0_I2C3SCL			3
#define PortDriver_Channel_Function_D0_M0PWM6			4
#define PortDriver_Channel_Function_D0_M1PWM0			5
#define PortDriver_Channel_Function_D0_WT2CCP0			7
#define PortDriver_Channel_Function_D1_SSI3FSS			1
#define PortDriver_Channel_Function_D1_SSI1FSS			2
#define PortDriver_Channel_Function_D1_I2C3SDA			3
#define PortDriver_Channel_Function_D1_M0PWM7			4
#define PortDriver_Channel_Function_D1_M1PWM1			5
#define PortDriver_Channel_Function_D1_WT2CCP1			7
#define PortDriver_Channel_Function_D2_SSI3RX			1
#define PortDriver_Channel_Function_D2_SSI1RX			2
#define PortDriver_Channel_Function_D2_M0FAULT0			4
#define PortDriver_Channel_Function_D2_WT3CCP0			7
#define PortDriver_Channel_Function_D2_USB0EPEN			8
#define PortDriver_Channel_Function_D3_SSI3TX			1
#define PortDriver_Channel_Function_D3_SSI1TX			2
#define PortDriver_Channel_Function_D3_IDX0				6
#define PortDriver_Channel_Function_D3_WT3CCP1			7
#define PortDriver_Channel_Function_D3_USB0PFLT			8
#define PortDriver_Channel_Function_D4_U6RX				1
#define PortDriver_Channel_Function_D4_WT4CCP0			7
#define PortDriver_Channel_Function_D5_U6TX				1
#define PortDriver_Channel_Function_D5_WT4CCP1			7
#define PortDriver_Channel_Function_D6_U2RX				1
#define PortDriver_Channel_Function_D6_M0FAULT0			4
#define PortDriver_Channel_Function_D6_PHA0				6
#define PortDriver_Channel_Function_D6_WT5CCP0			7

#define PortDriver_Channel_Function_E0_U7RX				1
#define PortDriver_Channel_Function_E1_U7TX				1
#define PortDriver_Channel_Function_E4_U5RX				1
#define PortDriver_Channel_Function_E4_I2C2SCL			3
#define PortDriver_Channel_Function_E4_M0PWM4			4
#define PortDriver_Channel_Function_E4_M1PWM2			5
#define PortDriver_Channel_Function_E4_CAN0RX			8
#define PortDriver_Channel_Function_E5_U5TX				1
#define PortDriver_Channel_Function_E5_I2C2SDA			3
#define PortDriver_Channel_Function_E5_M0PWM5			4
#define PortDriver_Channel_Function_E5_M1PWM3			5
#define PortDriver_Channel_Function_E5_CAN0TX			8

#define PortDriver_Channel_Function_F1_U1CTS			1
#define PortDriver_Channel_Function_F1_SSI1TX			2
#define PortDriver_Channel_Function_F1_M1PWM5			5
#define PortDriver_Channel_Function_F1_PHB0				6
#define PortDriver_Channel_Function_F1_T0CCP1			7
#define PortDriver_Channel_Function_F1_C1O				9
#define PortDriver_Channel_Function_F1_TRD1				14
#define PortDriver_Channel_Function_F2_SSI1CLK			2
#define PortDriver_Channel_Function_F2_M0FAULT0			4
#define PortDriver_Channel_Function_F2_M1PWM6			5
#define PortDriver_Channel_Function_F2_T1CCP0			7
#define PortDriver_Channel_Function_F2_TRD0				14
#define PortDriver_Channel_Function_F3_SSI1FSS			2
#define PortDriver_Channel_Function_F3_CAN0TX			3
#define PortDriver_Channel_Function_F3_M1PWM7			5
#define PortDriver_Channel_Function_F3_T1CCP1			7
#define PortDriver_Channel_Function_F3_TRCLK			14
#define PortDriver_Channel_Function_F4_M1FAULT0			5
#define PortDriver_Channel_Function_F4_IDX0				6
#define PortDriver_Channel_Function_F4_T2CCP0			7
#define PortDriver_Channel_Function_F4_USB0EPEN			8

typedef uint8_t PortDriver_Channel_ExtiType;
#define PortDriver_Channel_Exti_Disable					0
#define PortDriver_Channel_Exti_RisingEdge				0b0001
#define PortDriver_Channel_Exti_FallingEdge				0b0010
#define PortDriver_Channel_Exti_BothEdge				0b1000
#define PortDriver_Channel_Exti_HighLevel				0b0101
#define PortDriver_Channel_Exti_LowLevel				0b0110

typedef enum{
	PortDriver_PortNum_A,
	PortDriver_PortNum_B,
	PortDriver_PortNum_C,
	PortDriver_PortNum_D,
	PortDriver_PortNum_E,
	PortDriver_PortNum_F
}PortDriver_PortNumType;

typedef enum{
	PortDriver_Channel_A0,
	PortDriver_Channel_A1,
	PortDriver_Channel_A2,
	PortDriver_Channel_A3,
	PortDriver_Channel_A4,
	PortDriver_Channel_A5,
	PortDriver_Channel_A6,
	PortDriver_Channel_A7,
	
	PortDriver_Channel_B0,
	PortDriver_Channel_B1,
	PortDriver_Channel_B2,
	PortDriver_Channel_B3,
	PortDriver_Channel_B4,
	PortDriver_Channel_B5,
	PortDriver_Channel_B6,
	PortDriver_Channel_B7,
	
	/* PC3:0 are used for JTAG/SWD so they are unprogrammable */
	PortDriver_Channel_C0_Reserved,
	PortDriver_Channel_C1_Reserved,
	PortDriver_Channel_C2_Reserved,
	PortDriver_Channel_C3_Reserved,
	PortDriver_Channel_C4,
	PortDriver_Channel_C5,
	PortDriver_Channel_C6,
	PortDriver_Channel_C7,
	
	PortDriver_Channel_D0,
	PortDriver_Channel_D1,
	PortDriver_Channel_D2,
	PortDriver_Channel_D3,
	PortDriver_Channel_D4,
	PortDriver_Channel_D5,
	PortDriver_Channel_D6,
	/* PD7: NMI */
	PortDriver_Channel_D7_Reserved,
	
	PortDriver_Channel_E0,
	PortDriver_Channel_E1,
	PortDriver_Channel_E2,
	PortDriver_Channel_E3,
	PortDriver_Channel_E4,
	PortDriver_Channel_E5,
	PortDriver_Channel_E6_Reserved,
	PortDriver_Channel_E7_Reserved,
	
	/* PF0: NMI */
	PortDriver_Channel_F0_Reserved,
	PortDriver_Channel_F1,
	PortDriver_Channel_F2,
	PortDriver_Channel_F3,
	PortDriver_Channel_F4,
	PortDriver_Channel_F5_Reserved,
	PortDriver_Channel_F6_Reserved,
	PortDriver_Channel_F7_Reserved
}PortDriver_ChannelType;

typedef struct{
	PortDriver_ChannelType				Channel;
	PortDriver_Channel_DirectionType	PortDriver_Channel_Direction;
	PortDriver_Channel_Current_mAType	PortDriver_Channel_Current_mA;
	PortDriver_Channel_SlewRateType		PortDriver_Channel_SlewRate;
	PortDriver_Channel_AttachmentType	PortDriver_Channel_Attachment;
	PortDriver_Channel_FunctionType		PortDriver_Channel_Function;
	PortDriver_Channel_ExtiType			PortDriver_Channel_Exti;
}PortDriver_CfgType;


#endif /* PORT_TYPES_H_ */
