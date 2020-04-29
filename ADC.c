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

#define ADCEMUX_REG_BLOCK_SIZE				4
#define ADCEMUX_MASK					0b1111
#define ADCSSMUX_SHIFT_BETWEEN_REGS		0x08
#define ADCSSCTL_SHIFT_BETWEEN_REGS		0x08
#define ADCSSFIFO_SHIFT_BETWEEN_REGS	0x08

#define FIRST_ELEMENT					0
#define ADCSSMUX_REG_BLOCK_SIZE			4
#define ADCSSCTL_REG_BLOCK_SIZE			4

/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

static volatile void (*pf_ADC0_CallBackPtr)(void) = NULL;
static volatile void (*pf_ADC1_CallBackPtr)(void) = NULL;

static PointerToADCRegisters ArrayOfADCRegisters[NUMBER_OF_ADC_INSTANCES] = {
	(ADC_RegType*)ADC_0,
	(ADC_RegType*)ADC_1
};


/********************************************************************************
 * 							 Static API's Declarations							*
 ********************************************************************************/

static void ADC0_SetCallBack(void(*LocalPointer)(void));
static void ADC1_SetCallBack(void(*LocalPointer)(void));


/********************************************************************************
 * 							 Static API's Definitions							*
 ********************************************************************************/

static void ADC0_SetCallBack(void(*LocalPointer)(void))
{
	pf_ADC0_CallBackPtr = (volatile void(*)(void))LocalPointer;
}

static void ADC1_SetCallBack(void(*LocalPointer)(void))
{
	pf_ADC1_CallBackPtr = (volatile void(*)(void))LocalPointer;
}

/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

void ADC_Init(void)
{
	uint8_t au8_ADCEMUX_RegisterShift = ADC_Cfg.ADC_SampleSequencer * ADCEMUX_REG_BLOCK_SIZE;
	uint8_t au8_Counter;
	uint8_t au8_Max;
	uint32_t* PointerTo_ADCSSMUX_Regs = (uint32_t*)(&(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSMUX0)) \
									  + (ADC_Cfg.ADC_SampleSequencer * ADCSSMUX_SHIFT_BETWEEN_REGS);
	uint32_t* PointerTo_ADCSSCTL_Regs = (uint32_t*)(&(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSCTL0)) \
									  + (ADC_Cfg.ADC_SampleSequencer * ADCSSCTL_SHIFT_BETWEEN_REGS);
	uint32_t au32_ControlRegisterContent;
	void_FunPtrType_void_ptr_void PointerTo_ADC_SetCallBackFunction = ADC_Cfg.ADC_InstanceNum? &ADC1_SetCallBack : &ADC0_SetCallBack;
	
	
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
/*
	This switch case is to determine the number of times the loop will go in order to 
	fill the whole register with the required channels.
*/
	switch(ADC_Cfg.ADC_SampleSequencer)
	{
	case ADC_SampleSequencer_SS0:
		au8_Max = EIGHT;
		break;
	case ADC_SampleSequencer_SS1:
	case ADC_SampleSequencer_SS2:
		au8_Max = FOUR;
		break;
	case ADC_SampleSequencer_SS3:
		au8_Max = ONE;
		break;
	default:
		/* Handle appropriately */
		break;
	}
	
	for(au8_Counter = ZERO ; au8_Counter < au8_Max ; au8_Counter++)
	{

		au32_ControlRegisterContent = (ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_SamplingMode | \
									  ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_EndOfSequence | \
									  ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_Interrupt | \
									  ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_Input) << (au8_Counter * ADCSSCTL_REG_BLOCK_SIZE);
/*
The following line is an equation to put each element of the array in the right place
in the appropriate register.
*/
		*PointerTo_ADCSSMUX_Regs |= (ADC_Cfg.ADC_Input[au8_Counter] << (au8_Counter * ADCSSMUX_REG_BLOCK_SIZE));
/*
The following line is an equation to put the right value in the right place in the appropriate
register.
*/
		*PointerTo_ADCSSCTL_Regs |= au32_ControlRegisterContent;
	}
	
	switch(ADC_Cfg.ADC_SSCtl[FIRST_ELEMENT].ADC_Interrupt)
	{
	case ADC_Interrupt_Disable:
		/* Do nothing. */
		break;
	case ADC_Interrupt_Enable:
		SET_BIT(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCIM, ADC_Cfg.ADC_SampleSequencer);
		PointerTo_ADC_SetCallBackFunction(ADC_Cfg.CallBckFunPtr);
		break;
	default:
		/* Handle appropriately. */
		break;
	}
	
	SET_BIT(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCACTSS, ADC_Cfg.ADC_SampleSequencer);
}

void ADC_StartConversion(void)
{
	SET_BIT(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCPSSI, ADC_Cfg.ADC_SampleSequencer);
}

void ADC_Read(uint16_t* Result)
{
	uint32_t* PointerTo_ADCSSFIFO_Regs = (uint32_t*)(&(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSFIFO0)) \
									   + (ADC_Cfg.ADC_SampleSequencer * ADCSSFIFO_SHIFT_BETWEEN_REGS);

	switch(ADC_Cfg.ADC_SSCtl[FIRST_ELEMENT].ADC_Interrupt)
	{
	case ADC_Interrupt_Disable:
		while(BIT_IS_CLEAR(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCRIS, ADC_Cfg.ADC_SampleSequencer));
		break;
	case ADC_Interrupt_Enable:
		/* Do nothing. */
		break;
	default:
		/* Handle appropriately. */
		break;
	}
	
	*Result = *PointerTo_ADCSSFIFO_Regs;
	
	CLEAR_BIT(ArrayOfADCRegisters[ADC_Cfg.ADC_InstanceNum]->ADCISC, ADC_Cfg.ADC_SampleSequencer);
}


/********************************************************************************
 * 							 Interrupt Service Routines							*
 ********************************************************************************/

void ADC0SS0_Handler(void)
{
	if(pf_ADC0_CallBackPtr != NULL)
	{
		pf_ADC0_CallBackPtr();
	}
}

void ADC0SS1_Handler(void)
{
	if(pf_ADC0_CallBackPtr != NULL)
	{
		pf_ADC0_CallBackPtr();
	}
}

void ADC0SS2_Handler(void)
{
	if(pf_ADC0_CallBackPtr != NULL)
	{
		pf_ADC0_CallBackPtr();
	}
}

void ADC0SS3_Handler(void)
{
	if(pf_ADC0_CallBackPtr != NULL)
	{
		pf_ADC0_CallBackPtr();
	}
}

void ADC1SS0_Handler(void)
{
	if(pf_ADC1_CallBackPtr != NULL)
	{
		pf_ADC1_CallBackPtr();
	}
}

void ADC1SS1_Handler(void)
{
	if(pf_ADC1_CallBackPtr != NULL)
	{
		pf_ADC1_CallBackPtr();
	}
}

void ADC1SS2_Handler(void)
{
	if(pf_ADC1_CallBackPtr != NULL)
	{
		pf_ADC1_CallBackPtr();
	}
}

void ADC1SS3_Handler(void)
{
	if(pf_ADC1_CallBackPtr != NULL)
	{
		pf_ADC1_CallBackPtr();
	}
}
