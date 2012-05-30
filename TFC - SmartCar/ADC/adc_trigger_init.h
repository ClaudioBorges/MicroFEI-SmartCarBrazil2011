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
 * file                   : adc_trigger_init.h
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
 * Brief Description      : This File contains functions declaration of ADC Trigger code file
 *
 *
 *######################################################################
*/

#ifndef  _ADC_TRIGGER_INIT_H
#define  _ADC_TRIGGER_INIT_H
/********************  Dependent Include files here **********************/

/**********************  Function Prototype here *************************/

void adc_normal_start_fnc(void);
void adc_injected_start_fnc(void);
void adc_normal_stop_fnc(void);
void adc_chain_stop_fnc(void);
void adc_enter_powerdown_mode(void);
void adc_exit_powerdown_mode(void);


#endif  /*_ADC_TRIGGER_INIT_H*/

/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

