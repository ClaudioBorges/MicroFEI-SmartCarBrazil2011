/*
 *######################################################################
 *                                RAppIDJDP
 *           Rapid Application Initialization and Documentation Tool
 *                         Freescale Semiconductor Inc.
 *
 *######################################################################
 *
 * Project Name           : SAIC ADC
 *
 * Project File           : SAIC ADC.rsp
 *
 * Revision Number        : 1.0
 *
 * Tool Version           : 1.3.1.6
 *
 * file                   : intc_adc.c
 *
 * Target Compiler        : Diab
 *
 * Target Part            : MPC5604B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 06-Aug-2011 12:22:55
 *
 * Created on Date        : 06-Aug-2011 12:33:44
 *
 * Brief Description      : This  file contains  the interrupt service routine  for the ADC
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when ADC function is defined
 *                         in INTC peripheral.This file contains the Interrupt
 *                         handlers routines for ADC. In Interrupt handlers
 *                         routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_adc.h"
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */

/************************* INTERRUPT HANDLERS ************************/
volatile uint32_t adcIsrMirror = 0;

void INT_ADC (void)
{
	if (ADC.CEOCFR[32].B.EOC_CH0)
		adcIsrMirror = ADC.CDR[32].B.CDATA;

    ADC.ISR.R=0x0000001F;

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

