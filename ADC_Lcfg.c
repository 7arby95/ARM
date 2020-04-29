/*
 * ADC_Lcfg.c
 *
 *  Created on: Apr 25, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "ADC_Lcfg.h"


/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/
//typedef struct{
//	ADC_SamplingModeType		ADC_SamplingMode;
//	ADC_EndOfSequenceType		ADC_EndOfSequence;
//	ADC_InterruptType			ADC_Interrupt;
//	ADC_InputType				ADC_Input;
//}ADC_SSCtlType;

ADC_CfgType ADC_Cfg = {
	.ADC_InstanceNum		=	ADC_InstanceNum_ADC0,
	.ADC_SampleSequencer	=	ADC_SampleSequencer_SS3,
	.ADC_TriggerSource		=	ADC_TriggerSource_Processor,
	.ADC_Input				=	{ADC_Input_AIN0_E3},
	.ADC_SSCtl				=	{{ADC_SamplingMode_SingleEndedSampling,		ADC_EndOfSequence_EndOfSequence,		ADC_Interrupt_Disable,		ADC_Input_Channels}}
};
