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
 * file                   : intc_emios.c
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
 * Brief Description      : This  file contains  the interrupt service routine  for the EMIOS
 *
 ******************************************************************************** 
 *
 * Detail Description     : This file is generated when EMIOS function is
 *                         defined in INTC peripheral.This file contains the
 *                         Interrupt handlers routines for EMIOS. In Interrupt
 *                         handlers routine respective flags are cleared.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "intc_emios.h"
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */


/************************* INTERRUPT HANDLERS ************************/

void INT_EMIOS (void)
{
    EMIOS_0.CH[0].CSR.B.FLAG = 1;
    EMIOS_0.CH[1].CSR.B.FLAG = 1;

}


 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

