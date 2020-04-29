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

/* Definition of ADC modules in the microcontroller */
#define NUMBER_OF_ADC_INSTANCES			0x02

/* Some definitions to be used in the code */
#define ADCEMUX_MASK					0b1111
#define FIRST_ELEMENT					0x00
#define ADC_INSTANCE0					0x00
#define ADC_INSTANCE1					0x01
#define ADCSSMUX_SHIFT_BETWEEN_REGS		0x08
#define ADCSSCTL_SHIFT_BETWEEN_REGS		0x08
#define ADCSSFIFO_SHIFT_BETWEEN_REGS	0x08
#define ADCEMUX_REG_BLOCK_SIZE			0x04
#define ADCSSMUX_REG_BLOCK_SIZE			0x04
#define ADCSSCTL_REG_BLOCK_SIZE			0x04

#define PARS_VARS_UNINITIALIZED			0x00
#define PARS_VARS_INITIALIZED			0x01

/* Some definitions regarding error checking */
#define ADC_NOT_INITIALIZED				0x00
#define ADC_INITIALIZED					0x01
#define ADC_START_CONVERSION_STATE		0x00
#define ADC_GET_READING_STATE			0x01


/********************************************************************************
 * 							 	 Global Variables								*
 ********************************************************************************/

/* Two pointers to functions that take void and return void used to carry the addresses of the call back functions */
static volatile void (*pf_ADC0_CallBackPtr)(void);
static volatile void (*pf_ADC1_CallBackPtr)(void);

/* An array of two pointers to the register packs of ADC instances used to simplify the equations in the functions */
static PointerToADCRegisters ADC_ArrayOfRegisters[NUMBER_OF_ADC_INSTANCES];

/* An array containing two variables expressing the initialization status of each instance. */
uint8_t ADC_ArrayOfInitializationFlags[NUMBER_OF_ADC_INSTANCES];
uint8_t ADC_ArrayOfOperationFlags[NUMBER_OF_ADC_INSTANCES];

/********************************************************************************
 * 							 Static API's Declarations							*
 ********************************************************************************/

static void ADC_ParsVarsDefaults(void);
static void ADC0_SetCallBack(void(*LocalPointer)(void));
static void ADC1_SetCallBack(void(*LocalPointer)(void));


/********************************************************************************
 * 							 Static API's Definitions							*
 ********************************************************************************/

/*
	Description: A function to Initialize global variables.
*/
static void ADC_ParsVarsDefaults(void)
{
	/* A static variable so it can be initialized only once and therefore the global
	   variables will also be initialized only once */
	static uint8_t au8_InitializationStatus = PARS_VARS_UNINITIALIZED;
	
	/* In case this is the first call of this function.. */
	if(au8_InitializationStatus == PARS_VARS_UNINITIALIZED)
	{
		/* Do the initializations. */
		pf_ADC0_CallBackPtr = NULL;
		pf_ADC1_CallBackPtr = NULL;
		
		ADC_ArrayOfRegisters[ADC_INSTANCE0]  = (ADC_RegType*)ADC_0;
		ADC_ArrayOfRegisters[ADC_INSTANCE1] = (ADC_RegType*)ADC_1;
		
		ADC_ArrayOfInitializationFlags[ADC_INSTANCE0] = ADC_NOT_INITIALIZED;
		ADC_ArrayOfInitializationFlags[ADC_INSTANCE1] = ADC_NOT_INITIALIZED;
		
		ADC_ArrayOfOperationFlags[ADC_INSTANCE0] = ADC_START_CONVERSION_STATE;
		ADC_ArrayOfOperationFlags[ADC_INSTANCE1] = ADC_START_CONVERSION_STATE;
		
		/* And Change the status into initialized in order to avoid double initialization. */
		au8_InitializationStatus = PARS_VARS_INITIALIZED;
	}
	/* Otherwise.. */
	else
	{
		/* Do nothing. */
	}
}

/*
	Description: A function used to set the call back function for ADC0 module.
*/
static void ADC0_SetCallBack(void(*LocalPointer)(void))
{
	pf_ADC0_CallBackPtr = (volatile void(*)(void))LocalPointer;
}

/*
	Description: A function used to set the call back function for ADC1 module.
*/
static void ADC1_SetCallBack(void(*LocalPointer)(void))
{
	pf_ADC1_CallBackPtr = (volatile void(*)(void))LocalPointer;
}

/********************************************************************************
 * 								 API's Definitions								*
 ********************************************************************************/

/*
	Description: A function used to initialize the required ADC module according to the configurations files.
*/
ADC_ERROR_STATUS ADC_Init(void)
{
/************************************************* 1. VARIABLES *************************************************/
/****************************************************************************************************************/
	/* The following are two variables used to loop both the array of structures and the array of inputs in the 
	   configurations files. */
	uint8_t au8_Counter;
	uint8_t au8_Max;
	
	/* The return of the function, which is the error status. */
	sint8_t as8_Ret = ADC_E_OK;
	
	/* A variable to simplify the ADCEMUX equation. */
	uint8_t au8_ADCEMUX_RegisterShift = ADC_Cfg.ADC_SampleSequencer * ADCEMUX_REG_BLOCK_SIZE;
	
	/* The following are two pointers used to point at the right register needed in the steps. */
	uint32_t* PointerTo_ADCSSMUX_Regs = (uint32_t*)(&(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSMUX0)) \
									  + (ADC_Cfg.ADC_SampleSequencer * ADCSSMUX_SHIFT_BETWEEN_REGS);
	uint32_t* PointerTo_ADCSSCTL_Regs = (uint32_t*)(&(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSCTL0)) \
									  + (ADC_Cfg.ADC_SampleSequencer * ADCSSCTL_SHIFT_BETWEEN_REGS);
									  
	/* A variable to store the content of the ADCSSCTL to simplify the final equation of that register. */
	uint32_t au32_ControlRegisterContent;
	
	/* A pointer to function that takes an address of a call back function and returns void, used to point at
	   the right function between setcallback for ADC0 instance and for ADC1 instance. */
	void_FunPtrType_void_ptr_void PointerTo_ADC_SetCallBackFunction = ADC_Cfg.ADC_InstanceNum? &ADC1_SetCallBack : &ADC0_SetCallBack;
	
	
/*************************************************** 2. STEPS ***************************************************/
/****************************************************************************************************************/

	/* Setting the global variables to their default (initial) values. */
	ADC_ParsVarsDefaults();
/*
1.	Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
	ADCACTSS register. Programming of the sample sequencers is allowed without having them
	enabled. Disabling the sequencer during programming prevents erroneous execution if a trigger
	event were to occur during the configuration process. 
*/
	/*
		This switch-case statement is to determine the number of times the loop will go in order to 
		fill the whole register with the required channels.
	*/
	switch(ADC_Cfg.ADC_SampleSequencer)
	{
	case ADC_SampleSequencer_SS0:
		/* EIGHT because this sequencer can sample 8 channels. */
		au8_Max = EIGHT;
		break;
	case ADC_SampleSequencer_SS1:
	case ADC_SampleSequencer_SS2:
		/* FOUR because this sequencer can sample 4 channels. */
		au8_Max = FOUR;
		break;
	case ADC_SampleSequencer_SS3:
		/* ONE because this sequencer can sample only one channel. */
		au8_Max = ONE;
		break;
	default:
		break;
	}
	
	for(au8_Counter = ZERO ; au8_Counter < au8_Max ; au8_Counter++)
	{
		if(ADC_Cfg.ADC_Input[au8_Counter] > ADC_Input_AIN11_B5 || \
		(ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_EndOfSequence != ADC_EndOfSequence_SamplingContinues && \
		ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_EndOfSequence != ADC_EndOfSequence_EndOfSequence) || \
		(ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_Input != ADC_Input_Channels && \
		ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_Input != ADC_Input_InternalTempSensor) || \
		(ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_Interrupt != ADC_Interrupt_Disable && \
		ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_Interrupt != ADC_Interrupt_Enable) || \
		ADC_Cfg.ADC_SSCtl[au8_Counter].ADC_SamplingMode > ADC_SamplingMode_DifferentialSampling)
		{
			as8_Ret = ADC_E_INVALID_PARAMETERS;
		}
	}
	
	if(ADC_ArrayOfInitializationFlags[ADC_Cfg.ADC_InstanceNum] == ADC_INITIALIZED)
	{
		as8_Ret = ADC_E_MULTIPLE_MODULE_INITIALIZATION;
	}else if(ADC_Cfg.ADC_InstanceNum > ADC_InstanceNum_ADC1 || \
			(ADC_Cfg.ADC_SampleSequencer > ADC_SampleSequencer_SS3) || \
			(ADC_Cfg.ADC_TriggerSource > ADC_TriggerSource_ContinuousSampling) || \
			(ADC_Cfg.ADC_TriggerSource > ADC_TriggerSource_PWM_Gen3 && ADC_Cfg.ADC_TriggerSource < ADC_TriggerSource_ContinuousSampling))
	{
		as8_Ret = ADC_E_INVALID_PARAMETERS;
	}else if(as8_Ret == ADC_E_OK)
	{
		CLEAR_BIT(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCACTSS, ADC_Cfg.ADC_SampleSequencer);

/*
2.	Configure the trigger event for the sample sequencer in the ADCEMUX register.
*/
		ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCEMUX = \
			(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCEMUX & ~(ADCEMUX_MASK << au8_ADCEMUX_RegisterShift)) | \
			(ADC_Cfg.ADC_TriggerSource << au8_ADCEMUX_RegisterShift);

/*
3. When using a PWM generator as the trigger source, use the ADC Trigger Source Select
(ADCTSSEL) register to specify in which PWM module the generator is located. The default
register reset selects PWM module 0 for all generators.
(Step 3 is ignored for now, because we don't have any other module drivers.. So we use the processor option)

4. For each sample in the sample sequence, configure the corresponding input source in the
ADCSSMUXn register.
(Full configurations regarding this matter are not yet available)
*/
		/* A for loop used to loop the contents of the configuration structure arrays and fill
		   the registers with the proper values. */
		for(au8_Counter = ZERO ; au8_Counter < au8_Max ; au8_Counter++)
		{
			/* Update the variable with the current block content according to the counter. */
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
5. For each sample in the sample sequence, configure the sample control bits in the corresponding
nibble in the ADCSSCTLn register. When programming the last nibble, ensure that the END bit
is set. Failure to set the END bit causes unpredictable behavior.
*/
			/*
				The following line is an equation to put the right value in the right place in the appropriate
				register.
			*/
			*PointerTo_ADCSSCTL_Regs |= au32_ControlRegisterContent;
		}
		
/*
6. If interrupts are to be used, set the corresponding MASK bit in the ADCIM register.
*/
		/* This switch-case statement is to determine whether the selected interrupt mode is on or off. */
		switch(ADC_Cfg.ADC_SSCtl[FIRST_ELEMENT].ADC_Interrupt)
		{
		/* In case Interrupts are disabled.. */
		case ADC_Interrupt_Disable:
			/* Do nothing. */
			break;
		/* In case Interrupts are enabled.. */
		case ADC_Interrupt_Enable:
			/* Activate the interrupt option from the Interrupt Mask register, */
			SET_BIT(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCIM, ADC_Cfg.ADC_SampleSequencer);
			/* and set the call back function sent through the configurations structure */
			PointerTo_ADC_SetCallBackFunction(ADC_Cfg.CallBckFunPtr);
			break;
		default:
			break;
		}

/*	
7. Enable the sample sequencer logic by setting the corresponding ASENn bit in the ADCACTSS
register.
*/
		SET_BIT(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCACTSS, ADC_Cfg.ADC_SampleSequencer);
		
		/* Change the initialization status into initialized status in order to avoid multiple initializations. */
		ADC_ArrayOfInitializationFlags[ADC_Cfg.ADC_InstanceNum] = ADC_INITIALIZED;
	}
	
	return as8_Ret;
}

/* Description: A function used to initiate the ADC Processor Sample Sequence. */
ADC_ERROR_STATUS ADC_StartConversion(void)
{
	/* The return of the function, which is the error status. */
	sint8_t as8_Ret = ADC_E_OK;
	
	if(ADC_ArrayOfInitializationFlags[ADC_Cfg.ADC_InstanceNum] == ADC_NOT_INITIALIZED)
	{
		as8_Ret = ADC_E_NOT_INITIALIZED;
	}else if(ADC_ArrayOfOperationFlags[ADC_Cfg.ADC_InstanceNum] == ADC_GET_READING_STATE)
	{
		as8_Ret = ADC_E_MULTIPLE_STARTING_CONVERSION;
	}else
	{
		/* This line is used to initiate the required instance's sample sequencer according to the channels used. */
		SET_BIT(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCPSSI, ADC_Cfg.ADC_SampleSequencer);
		
		ADC_ArrayOfOperationFlags[ADC_Cfg.ADC_InstanceNum] = ADC_GET_READING_STATE;
	}
	return as8_Ret;
}

/* Description: A function used to get the conversion result. */
ADC_ERROR_STATUS ADC_Read(uint16_t* Result)
{
	/* The return of the function, which is the error status. */
	sint8_t as8_Ret = ADC_E_OK;

	/* A pointer to register used to carry the address of the right register of the right instance. */
	uint32_t* PointerTo_ADCSSFIFO_Regs = (uint32_t*)(&(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCSSFIFO0)) \
									   + (ADC_Cfg.ADC_SampleSequencer * ADCSSFIFO_SHIFT_BETWEEN_REGS);
	
	if(ADC_ArrayOfInitializationFlags[ADC_Cfg.ADC_InstanceNum] == ADC_NOT_INITIALIZED)
	{
		as8_Ret = ADC_E_NOT_INITIALIZED;
	}else if(ADC_ArrayOfOperationFlags[ADC_Cfg.ADC_InstanceNum] == ADC_START_CONVERSION_STATE)
	{
		as8_Ret = ADC_E_READ_WITHOUT_STARTING_CONVERSION;
	}else if(Result == NULL)
	{
		as8_Ret = ADC_E_NULL_POINTER;
	}else
	{
		/*
			A switch-case statement used to busy-wait the completion flag in case the interrupts are disabled,
			or to do nothing in case the interrupts are enabled, because this will be controller by the ADC
			interrupt handler.
		*/
		switch(ADC_Cfg.ADC_SSCtl[FIRST_ELEMENT].ADC_Interrupt)
		{
		case ADC_Interrupt_Disable:
			/* Busy-waiting the completion flag. */
			while(BIT_IS_CLEAR(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCRIS, ADC_Cfg.ADC_SampleSequencer));
			break;
		case ADC_Interrupt_Enable:
			/* Do nothing. */
			break;
		default:
			break;
		}
		
		/* Store the result in the address given to the function. */
		*Result = *PointerTo_ADCSSFIFO_Regs;
		
		/* Clear the interrupt automatic flag. */
		SET_BIT(ADC_ArrayOfRegisters[ADC_Cfg.ADC_InstanceNum]->ADCISC, ADC_Cfg.ADC_SampleSequencer);
		
		ADC_ArrayOfOperationFlags[ADC_Cfg.ADC_InstanceNum] = ADC_START_CONVERSION_STATE;
	}
	
	return as8_Ret;
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
