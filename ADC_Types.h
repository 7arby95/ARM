/*
 * ADC_Types.h
 *
 *  Created on: Apr 25, 2020
 *      Author: Youssef Harby
 */


#ifndef ADC_TYPES_H_
#define ADC_TYPES_H_


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "std_types.h"


/********************************************************************************
 *								 Type  Declaration								*
 ********************************************************************************/

typedef uint8_t ADC_InstanceNumType;
#define ADC_InstanceNum_ADC0		0x00
#define ADC_InstanceNum_ADC1		0x01

typedef uint8_t ADC_SampleSequencerType;
#define ADC_SampleSequencer_SS0					0x00
#define ADC_SampleSequencer_SS1					0x01
#define ADC_SampleSequencer_SS2					0x02
#define ADC_SampleSequencer_SS3					0x03

typedef uint8_t ADC_TriggerSourceType;
#define ADC_TriggerSource_Processor				0x00
#define ADC_TriggerSource_AC0					0x01
#define ADC_TriggerSource_AC1					0x02
#define ADC_TriggerSource_External_GPIO_Pins	0x04
#define ADC_TriggerSource_Timer					0x05
#define ADC_TriggerSource_PWM_Gen0				0x06
#define ADC_TriggerSource_PWM_Gen1				0x07
#define ADC_TriggerSource_PWM_Gen2				0x08
#define ADC_TriggerSource_PWM_Gen3				0x09
#define ADC_TriggerSource_ContinuousSampling	0x0F

typedef uint8_t ADC_InputType;
#define ADC_Input_AIN0_E3				0x00
#define ADC_Input_AIN1_E2				0x01
#define ADC_Input_AIN2_E1				0x02
#define ADC_Input_AIN3_E0				0x03
#define ADC_Input_AIN4_D3				0x04
#define ADC_Input_AIN5_D2				0x05
#define ADC_Input_AIN6_D1				0x06
#define ADC_Input_AIN7_D0				0x07
#define ADC_Input_AIN8_E5				0x08
#define ADC_Input_AIN9_E4				0x09
#define ADC_Input_AIN10_B4				0x0A
#define ADC_Input_AIN11_B5				0x0B

#define ADC_Input_Channels				0x00
#define ADC_Input_InternalTempSensor	0x08

typedef uint8_t ADC_SamplingModeType;
#define ADC_SamplingMode_SingleEndedSampling	0x00
#define ADC_SamplingMode_DifferentialSampling	0x01

typedef uint8_t ADC_EndOfSequenceType;
#define ADC_EndOfSequence_SamplingContinues		0x00
#define ADC_EndOfSequence_EndOfSequence			0x02

typedef uint8_t ADC_InterruptType;
#define ADC_Interrupt_Disable		0x00
#define ADC_Interrupt_Enable		0x04

typedef struct{
	ADC_SamplingModeType		ADC_SamplingMode;
	ADC_EndOfSequenceType		ADC_EndOfSequence;
	ADC_InterruptType			ADC_Interrupt;
	ADC_InputType				ADC_Input;
}ADC_SSCtlType;

typedef struct{
	ADC_InstanceNumType			ADC_InstanceNum;
	ADC_SampleSequencerType		ADC_SampleSequencer;
	ADC_TriggerSourceType		ADC_TriggerSource;
	ADC_InputType				ADC_Input[8];
	ADC_SSCtlType				ADC_SSCtl[8];
	void_FunPtrType_void		CallBckFunPtr;
}ADC_CfgType;

typedef sint8_t ADC_ERROR_STATUS;
#define ADC_E_OK									(0)
#define ADC_E_NOT_INITIALIZED						(-1)
#define ADC_E_NULL_POINTER							(-2)
#define ADC_E_READ_WITHOUT_STARTING_CONVERSION		(-3)
#define ADC_E_MULTIPLE_STARTING_CONVERSION			(-4)
#define ADC_E_MULTIPLE_MODULE_INITIALIZATION		(-5)
#define ADC_E_INVALID_PARAMETERS					(-6)


#endif /* ADC_TYPES_H_ */
