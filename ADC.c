/*
 * ADC.c
 *
 *  Created on: Apr 25, 2020
 *      Author: Youssef Harby
 */


/********************************************************************************
 * 								  Included Files								*
 ********************************************************************************/

#include "tm4c123gh6pm_registers.h"
#include "ADC.h"
#include "ADC_Types.h"
#include "ADC_Lcfg.h"


/********************************************************************************
 * 								Preprocessor Macros								*
 ********************************************************************************/

#define NUMBER_OF_ADC_INSTANCES			2

#define ADCEMUX_BLOCK_SIZE				4
#define ADCEMUX_MASK					0b1111
#define ADCSSMUX_SHIFT_BETWEEN_REGS		0x08


/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

static volatile void (*pf_CallBackPtr)(void) = NULL;

static PointerToADCRegisters ArrayOfADCRegisters[NUMBER_OF_ADC_INSTANCES] = {
	(ADC_RegType*)ADC_0,
	(ADC_RegType*)ADC_1
};


/********************************************************************************
 * 							 Static API's Declarations							*
 ********************************************************************************/

static void ADC_SetCallBack(void(*LocalPointer)(void));


/********************************************************************************
 * 							 Static API's Definitions							*
 ********************************************************************************/

static void ADC_SetCallBack(void(*LocalPointer)(void))
{
	pf_CallBackPtr = (volatile void(*)(void))LocalPointer;
}


/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

void ADC_Init(void)
{
	uint8_t au8_ADCEMUX_RegisterShift = ADC_Cfg.ADC_SampleSequencer * ADCEMUX_BLOCK_SIZE;
	uint32_t* PointerTo_ADCSSMUX_Regs = (uint32_t*)(&(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSMUX0)) \
									  + (ADC_Cfg.ADC_SampleSequencer * ADCSSMUX_SHIFT_BETWEEN_REGS);
	
/*
1.	Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
	ADCACTSS register. Programming of the sample sequencers is allowed without having them
	enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
	event were to occur during the configuration process. 
*/
	CLEAR_BIT(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCACTSS, ADC_Cfg.ADC_SampleSequencer);

/*
2.	Configure the trigger event for the sample sequencer in the ADCEMUX register.
*/
	ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCEMUX = \
		(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCEMUX & ~(ADCEMUX_MASK << au8_ADCEMUX_RegisterShift)) | \
		(ADC_Cfg.ADC_TriggerSource << au8_ADCEMUX_RegisterShift);

/*
3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
(ADCTSSEL) register to specify in which PWM module the generator is located. The default
register reset selects PWM module 0 for all generators.
(Step 3 is ignored for now, because we don't have any other module driver..)

4. For each sample in the sample sequence, configure the corresponding input source in the
ADCSSMUXn register.
(Full configurations regarding this matter are not yet available)
*/
	*PointerTo_ADCSSMUX_Regs = ADC_Cfg.ADC_Input[0];
	
}

void ADC_StartConversion(void)
{
	
}

uint16_t ADC_Read(void)
{
	
}
