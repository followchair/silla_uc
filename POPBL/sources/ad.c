/*********************************************************************
** 																	**
** project : POPBL			 										**
** filename : ad.c													**
** version : 1 														**
** date : January 16, 2013 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2003, 					 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : January 16, 2013											**
**Revised by :														**
**Description : Original version. 									**
*********************************************************************/
#define AD_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "ad.h"
#include "stdio.h"
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
unsigned long ulADC1_Value[1];
unsigned long ulADC2_Value[1];
unsigned long ulADC3_Value[1];
float infra1 = 0;
float infra2 = 0;
char str[10];
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
float AD_ObtenerValorADC_Channel1() {
	//ADC CHANNEL 2
	ADCSequenceStepConfigure(ADC0_BASE, 3, // - Sequence 3
			0, // - Step 0:
			ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END // - Analog Input 0, Single-ended, No temp sensor, Interrupt, End of sequence
	);
	// Trigger the ADC conversion.
	ADCProcessorTrigger(ADC0_BASE, 3);
	// Wait for conversion to be completed.
	while (!ADCIntStatus(ADC0_BASE, 3, false)) {
	}
	// Read ADC Value.
	ADCSequenceDataGet(ADC0_BASE, 3, ulADC1_Value);
	ADCIntClear(ADC0_BASE, 3);
	infra1 = ulADC1_Value[0] * (10.0 / 1023.0);
	return infra1;

}

/**
 * @brief  Función que mira el valor del canal 2 del ADC.
 *
 * @return        -
 *
*/
float AD_ObtenerValorADC_Channel2() {
	//ADC CHANNEL 2
	ADCSequenceStepConfigure(ADC0_BASE, 3, // - Sequence 3
			0, // - Step 0:
			ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END // - Analog Input 0, Single-ended, No temp sensor, Interrupt, End of sequence
	);
	// Trigger the ADC conversion.
	ADCProcessorTrigger(ADC0_BASE, 3);
	// Wait for conversion to be completed.
	while (!ADCIntStatus(ADC0_BASE, 3, false)) {
	}
	// Read ADC Value.
	ADCSequenceDataGet(ADC0_BASE, 3, ulADC2_Value);
	ADCIntClear(ADC0_BASE, 3);
	infra1 = ulADC2_Value[0] * (10.0 / 1023.0);
	return infra1;

}

float AD_ObtenerValorADC_Channel3()
{

	//ADC CHANNEL 0
	ADCSequenceStepConfigure(ADC0_BASE, 3, 0,
	                         ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH3);
	// Trigger the ADC conversion.
	ADCProcessorTrigger(ADC0_BASE, 3);

	// Wait until the sample sequence has completed.
	while(!ADCIntStatus(ADC0_BASE, 3, false))
	{
	}
	// Read the value from the ADC.
	ADCSequenceDataGet(ADC0_BASE, 3, ulADC3_Value);
	ADCIntClear(ADC0_BASE, 3);
	infra2 = ulADC3_Value[0] * (10.0 / 1023.0);
	return infra2;
}
