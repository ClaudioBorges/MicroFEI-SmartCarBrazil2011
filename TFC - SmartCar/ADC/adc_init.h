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
 * file                   : adc_init.h
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
 * Brief Description      : This file contains function declaration for ADC code File.
 *
 *
 *######################################################################
*/

#ifndef  _ADC_INIT_H
#define  _ADC_INIT_H
/********************  Dependent Include files here **********************/


/**********************  Function Prototype here *************************/

void adc_init_fnc(void);
void adc_channel_setup_fnc(void);
void adc_ctuevent_init_fnc(void);
void adc_trigger_setup_fnc(void);


#endif  /*_ADC_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

