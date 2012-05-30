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
 * file                   : emios_init.c
 *
 * Target Compiler        : Diab
 *
 * Target Part            : MPC5604B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 06-Aug-2011 14:36:06
 *
 * Created on Date        : 06-Aug-2011 14:36:09
 *
 * Brief Description      : This file initializes eMIOS registers
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File contains function definitions that initialize eMIOS
 *                         peripherals. The initialization function configures the Module
 *                         Configuration Register and Unified Channel Registers for all
 *                         eMIOS modules present in the selected part. The module
 *                         provides upto 56 Unified Channels to generate or measure
 *                         time events.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "emios_init.h"
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */


/**********************  Initialization Function(s) *************************/


void emios_init_fnc (void) 
{
    emios_0_init_fnc();
    emios_1_init_fnc();
}
void emios_0_init_fnc (void) 
{
/* ----------------------------------------------------------- */
/*	EMIOS Module Configuration Register (EMIOS_MCR)            */
/* ----------------------------------------------------------- */
   EMIOS_0.MCR.R = 0x00000000;
            /* Module : Enable    */
            /* Global Freeze: Disabled                  */
            /* Global Time Base Enable: No              */
            /* Global Prescaler Enable: No              */
            /* Global Prescaler Value:   1              */

	EMIOS_0.MCR.B.GPREN = 1;  							/* Enable eMIOS clock */
	EMIOS_0.MCR.B.GTBE = 1;   							/* Enable global time base */
	EMIOS_0.MCR.B.FRZ = 1;    							/* Enable stopping channels when in debug mode */

/* ----------------------------------------------------------- */
/* EMIOS Output Update Disable Register (EMIOS_OUDR)           */
/* ----------------------------------------------------------- */
  EMIOS_0.OUDR.R = 0x00000000;
            /* Channel n output is Enabled  */
            /*   n = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 */

/* ----------------------------------------------------------- */
/* EMIOS Channel Disable Register  (EMIOS_UCDIS)           */
/* ----------------------------------------------------------- */
  EMIOS_0.UCDIS.R = 0x00000000;
            /* Channel n is Disabled  */
            /*   n = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27, */

/* ----------------------------------------------------------- */
/*	Unified Channel 00 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[0].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR0 Data Register - eMIOS_0_CADR0 : Value = 0*/

  EMIOS_0.CH[0].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR0 Data Register - eMIOS_0_CBDR0 : Value = 0*/

  EMIOS_0.CH[0].CCR.R = 0x00020002;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ generated          */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :Single                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Single action input capture       */

/* ----------------------------------------------------------- */
/*	Unified Channel 01 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[1].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR1 Data Register - eMIOS_0_CADR1 : Value = 0*/

  EMIOS_0.CH[1].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR1 Data Register - eMIOS_0_CBDR1 : Value = 0*/

  EMIOS_0.CH[1].CCR.R = 0x02000658;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Enable                */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Not Applicable                */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Internal counter                */
            /* Edge Selection Bit :Not Applicable                 */
            /* Edge Polarity :Clear on Match A                   */
            /* Mode : Output Pulse Width and Frequency M*/
            /* odulation Buffered                       */

	EMIOS_0.CH[1].CCR.B.BSL = 0x1;				/* Use counter bus B,C,D,or E */
	EMIOS_0.CH[1].CCR.B.EDPOL = 0;			/* u8Pol selects polarity the Ipwm must capture */
//  EMIOS_0.CH[1].CCR.B.FCK = 0;	    		/* Input filter bit clock reference is the system clock*/
//  EMIOS_0.CH[1].CCR.B.IF = 1;				    /* Input filter bit of 2 clock cycles*/ 
	EMIOS_0.CH[1].CCR.B.MODE = 0b0000100; 		/* Mode is IPWM Input Pulse Width Measurement */
	EMIOS_0.CH[1].CCR.B.FREN = 1;	    		/* Freeze channel counting when in debug mode */
	EMIOS_0.CH[1].CCR.B.DMA = 0;	  			/* Flag/overrun assigned to interrupt request */
  	EMIOS_0.CH[1].CCR.B.FEN = 0;	    		/* FLAG does not generate an interrupt request or a CTU trigger*/

/* ----------------------------------------------------------- */
/*	Unified Channel 02 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[2].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR2 Data Register - eMIOS_0_CADR2 : Value = 0*/

  EMIOS_0.CH[2].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR2 Data Register - eMIOS_0_CBDR2 : Value = 0*/

  EMIOS_0.CH[2].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 03 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[3].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR3 Data Register - eMIOS_0_CADR3 : Value = 0*/

  EMIOS_0.CH[3].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR3 Data Register - eMIOS_0_CBDR3 : Value = 0*/

  EMIOS_0.CH[3].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 04 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[4].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR4 Data Register - eMIOS_0_CADR4 : Value = 0*/

  EMIOS_0.CH[4].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR4 Data Register - eMIOS_0_CBDR4 : Value = 0*/

  EMIOS_0.CH[4].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 05 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[5].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR5 Data Register - eMIOS_0_CADR5 : Value = 0*/

  EMIOS_0.CH[5].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR5 Data Register - eMIOS_0_CBDR5 : Value = 0*/

  EMIOS_0.CH[5].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 06 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[6].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR6 Data Register - eMIOS_0_CADR6 : Value = 0*/

  EMIOS_0.CH[6].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR6 Data Register - eMIOS_0_CBDR6 : Value = 0*/

  EMIOS_0.CH[6].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 07 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[7].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR7 Data Register - eMIOS_0_CADR7 : Value = 0*/

  EMIOS_0.CH[7].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR7 Data Register - eMIOS_0_CBDR7 : Value = 0*/

  EMIOS_0.CH[7].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 08 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[8].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR8 Data Register - eMIOS_0_CADR8 : Value = 0*/

  EMIOS_0.CH[8].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR8 Data Register - eMIOS_0_CBDR8 : Value = 0*/

  EMIOS_0.CH[8].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 09 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[9].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR9 Data Register - eMIOS_0_CADR9 : Value = 0*/

  EMIOS_0.CH[9].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR9 Data Register - eMIOS_0_CBDR9 : Value = 0*/

  EMIOS_0.CH[9].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 10 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[10].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR10 Data Register - eMIOS_0_CADR10 : Value = 0*/

  EMIOS_0.CH[10].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR10 Data Register - eMIOS_0_CBDR10 : Value = 0*/

  EMIOS_0.CH[10].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 11 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[11].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR11 Data Register - eMIOS_0_CADR11 : Value = 0*/

  EMIOS_0.CH[11].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR11 Data Register - eMIOS_0_CBDR11 : Value = 0*/

  EMIOS_0.CH[11].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 12 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[12].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR12 Data Register - eMIOS_0_CADR12 : Value = 0*/

  EMIOS_0.CH[12].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR12 Data Register - eMIOS_0_CBDR12 : Value = 0*/

  EMIOS_0.CH[12].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 13 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[13].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR13 Data Register - eMIOS_0_CADR13 : Value = 0*/

  EMIOS_0.CH[13].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR13 Data Register - eMIOS_0_CBDR13 : Value = 0*/

  EMIOS_0.CH[13].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 14 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[14].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR14 Data Register - eMIOS_0_CADR14 : Value = 0*/

  EMIOS_0.CH[14].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR14 Data Register - eMIOS_0_CBDR14 : Value = 0*/

  EMIOS_0.CH[14].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 15 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[15].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR15 Data Register - eMIOS_0_CADR15 : Value = 0*/

  EMIOS_0.CH[15].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR15 Data Register - eMIOS_0_CBDR15 : Value = 0*/

  EMIOS_0.CH[15].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 16 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[16].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR16 Data Register - eMIOS_0_CADR16 : Value = 0*/

  EMIOS_0.CH[16].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR16 Data Register - eMIOS_0_CBDR16 : Value = 0*/

  EMIOS_0.CH[16].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 17 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[17].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR17 Data Register - eMIOS_0_CADR17 : Value = 0*/

  EMIOS_0.CH[17].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR17 Data Register - eMIOS_0_CBDR17 : Value = 0*/

  EMIOS_0.CH[17].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 18 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[18].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR18 Data Register - eMIOS_0_CADR18 : Value = 0*/

  EMIOS_0.CH[18].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR18 Data Register - eMIOS_0_CBDR18 : Value = 0*/

  EMIOS_0.CH[18].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 19 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[19].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR19 Data Register - eMIOS_0_CADR19 : Value = 0*/

  EMIOS_0.CH[19].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR19 Data Register - eMIOS_0_CBDR19 : Value = 0*/

  EMIOS_0.CH[19].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 20 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[20].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR20 Data Register - eMIOS_0_CADR20 : Value = 0*/

  EMIOS_0.CH[20].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR20 Data Register - eMIOS_0_CBDR20 : Value = 0*/

  EMIOS_0.CH[20].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 21 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[21].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR21 Data Register - eMIOS_0_CADR21 : Value = 0*/

  EMIOS_0.CH[21].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR21 Data Register - eMIOS_0_CBDR21 : Value = 0*/

  EMIOS_0.CH[21].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 22 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[22].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR22 Data Register - eMIOS_0_CADR22 : Value = 0*/

  EMIOS_0.CH[22].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR22 Data Register - eMIOS_0_CBDR22 : Value = 0*/

  EMIOS_0.CH[22].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 23 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[23].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR23 Data Register - eMIOS_0_CADR23 : Value = 0*/

  EMIOS_0.CH[23].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR23 Data Register - eMIOS_0_CBDR23 : Value = 0*/

  EMIOS_0.CH[23].CCR.R = 0x00000010;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Not Applicable                */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :Not Applicable                 */
            /* Edge Polarity :Not Applicable                   */
            /* Mode : Modulus Counter (Up counter with c*/
            /* lear on match start)                     */

/* ----------------------------------------------------------- */
/*	Unified Channel 24 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[24].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR24 Data Register - eMIOS_0_CADR24 : Value = 0*/

  EMIOS_0.CH[24].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CBDR24 Data Register - eMIOS_0_CBDR24 : Value = 0*/

  EMIOS_0.CH[24].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 25 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[25].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR25 Data Register - eMIOS_0_CADR25 : Value = 0*/

  EMIOS_0.CH[25].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 26 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[26].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR26 Data Register - eMIOS_0_CADR26 : Value = 0*/

  EMIOS_0.CH[26].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 27 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_0.CH[27].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_0_CADR27 Data Register - eMIOS_0_CADR27 : Value = 0*/

  EMIOS_0.CH[27].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/* EMIOS Channel Disable Register  (EMIOS_UCDIS)           */
/* ----------------------------------------------------------- */
  EMIOS_0.UCDIS.R = 0x0F7FFFFC;
            /* Channel n is Enabled  */
            /*   n = 0,1,23 */
            /* Channel n is Disabled  */
            /*   n = 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,24,25,26,27 */

}


void emios_1_init_fnc (void) 
{
/* ----------------------------------------------------------- */
/*	EMIOS Module Configuration Register (EMIOS_MCR)            */
/* ----------------------------------------------------------- */
   EMIOS_1.MCR.R = 0x00000000;
            /* Module : Enable    */
            /* Global Freeze: Disabled                  */
            /* Global Time Base Enable: No              */
            /* Global Prescaler Enable: No              */
            /* Global Prescaler Value:   1              */

/* ----------------------------------------------------------- */
/* EMIOS Output Update Disable Register (EMIOS_OUDR)           */
/* ----------------------------------------------------------- */
  EMIOS_1.OUDR.R = 0x00000000;
            /* Channel n output is Enabled  */
            /*   n = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 */

/* ----------------------------------------------------------- */
/* EMIOS Channel Disable Register  (EMIOS_UCDIS)           */
/* ----------------------------------------------------------- */
  EMIOS_1.UCDIS.R = 0x00000000;
            /* Channel n is Disabled  */
            /*   n = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27, */

/* ----------------------------------------------------------- */
/*	Unified Channel 00 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[0].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR0 Data Register - eMIOS_1_CADR0 : Value = 0*/

  EMIOS_1.CH[0].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR0 Data Register - eMIOS_1_CBDR0 : Value = 0*/

  EMIOS_1.CH[0].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 01 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[1].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR1 Data Register - eMIOS_1_CADR1 : Value = 0*/

  EMIOS_1.CH[1].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR1 Data Register - eMIOS_1_CBDR1 : Value = 0*/

  EMIOS_1.CH[1].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 02 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[2].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR2 Data Register - eMIOS_1_CADR2 : Value = 0*/

  EMIOS_1.CH[2].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR2 Data Register - eMIOS_1_CBDR2 : Value = 0*/

  EMIOS_1.CH[2].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 03 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[3].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR3 Data Register - eMIOS_1_CADR3 : Value = 0*/

  EMIOS_1.CH[3].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR3 Data Register - eMIOS_1_CBDR3 : Value = 0*/

  EMIOS_1.CH[3].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 04 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[4].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR4 Data Register - eMIOS_1_CADR4 : Value = 0*/

  EMIOS_1.CH[4].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR4 Data Register - eMIOS_1_CBDR4 : Value = 0*/

  EMIOS_1.CH[4].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 05 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[5].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR5 Data Register - eMIOS_1_CADR5 : Value = 0*/

  EMIOS_1.CH[5].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR5 Data Register - eMIOS_1_CBDR5 : Value = 0*/

  EMIOS_1.CH[5].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 06 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[6].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR6 Data Register - eMIOS_1_CADR6 : Value = 0*/

  EMIOS_1.CH[6].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR6 Data Register - eMIOS_1_CBDR6 : Value = 0*/

  EMIOS_1.CH[6].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 07 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[7].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR7 Data Register - eMIOS_1_CADR7 : Value = 0*/

  EMIOS_1.CH[7].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR7 Data Register - eMIOS_1_CBDR7 : Value = 0*/

  EMIOS_1.CH[7].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 08 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[8].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR8 Data Register - eMIOS_1_CADR8 : Value = 0*/

  EMIOS_1.CH[8].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR8 Data Register - eMIOS_1_CBDR8 : Value = 0*/

  EMIOS_1.CH[8].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 09 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[9].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR9 Data Register - eMIOS_1_CADR9 : Value = 0*/

  EMIOS_1.CH[9].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR9 Data Register - eMIOS_1_CBDR9 : Value = 0*/

  EMIOS_1.CH[9].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 10 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[10].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR10 Data Register - eMIOS_1_CADR10 : Value = 0*/

  EMIOS_1.CH[10].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR10 Data Register - eMIOS_1_CBDR10 : Value = 0*/

  EMIOS_1.CH[10].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 11 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[11].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR11 Data Register - eMIOS_1_CADR11 : Value = 0*/

  EMIOS_1.CH[11].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR11 Data Register - eMIOS_1_CBDR11 : Value = 0*/

  EMIOS_1.CH[11].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 12 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[12].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR12 Data Register - eMIOS_1_CADR12 : Value = 0*/

  EMIOS_1.CH[12].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR12 Data Register - eMIOS_1_CBDR12 : Value = 0*/

  EMIOS_1.CH[12].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 13 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[13].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR13 Data Register - eMIOS_1_CADR13 : Value = 0*/

  EMIOS_1.CH[13].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR13 Data Register - eMIOS_1_CBDR13 : Value = 0*/

  EMIOS_1.CH[13].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 14 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[14].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR14 Data Register - eMIOS_1_CADR14 : Value = 0*/

  EMIOS_1.CH[14].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR14 Data Register - eMIOS_1_CBDR14 : Value = 0*/

  EMIOS_1.CH[14].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 15 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[15].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR15 Data Register - eMIOS_1_CADR15 : Value = 0*/

  EMIOS_1.CH[15].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR15 Data Register - eMIOS_1_CBDR15 : Value = 0*/

  EMIOS_1.CH[15].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 16 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[16].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR16 Data Register - eMIOS_1_CADR16 : Value = 0*/

  EMIOS_1.CH[16].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR16 Data Register - eMIOS_1_CBDR16 : Value = 0*/

  EMIOS_1.CH[16].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 17 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[17].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR17 Data Register - eMIOS_1_CADR17 : Value = 0*/

  EMIOS_1.CH[17].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR17 Data Register - eMIOS_1_CBDR17 : Value = 0*/

  EMIOS_1.CH[17].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 18 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[18].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR18 Data Register - eMIOS_1_CADR18 : Value = 0*/

  EMIOS_1.CH[18].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR18 Data Register - eMIOS_1_CBDR18 : Value = 0*/

  EMIOS_1.CH[18].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 19 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[19].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR19 Data Register - eMIOS_1_CADR19 : Value = 0*/

  EMIOS_1.CH[19].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR19 Data Register - eMIOS_1_CBDR19 : Value = 0*/

  EMIOS_1.CH[19].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 20 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[20].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR20 Data Register - eMIOS_1_CADR20 : Value = 0*/

  EMIOS_1.CH[20].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR20 Data Register - eMIOS_1_CBDR20 : Value = 0*/

  EMIOS_1.CH[20].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 21 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[21].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR21 Data Register - eMIOS_1_CADR21 : Value = 0*/

  EMIOS_1.CH[21].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR21 Data Register - eMIOS_1_CBDR21 : Value = 0*/

  EMIOS_1.CH[21].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 22 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[22].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR22 Data Register - eMIOS_1_CADR22 : Value = 0*/

  EMIOS_1.CH[22].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR22 Data Register - eMIOS_1_CBDR22 : Value = 0*/

  EMIOS_1.CH[22].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 23 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[23].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR23 Data Register - eMIOS_1_CADR23 : Value = 0*/

  EMIOS_1.CH[23].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR23 Data Register - eMIOS_1_CBDR23 : Value = 0*/

  EMIOS_1.CH[23].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 24 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[24].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR24 Data Register - eMIOS_1_CADR24 : Value = 0*/

  EMIOS_1.CH[24].CBDR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CBDR24 Data Register - eMIOS_1_CBDR24 : Value = 0*/

  EMIOS_1.CH[24].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 25 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[25].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR25 Data Register - eMIOS_1_CADR25 : Value = 0*/

  EMIOS_1.CH[25].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 26 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[26].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR26 Data Register - eMIOS_1_CADR26 : Value = 0*/

  EMIOS_1.CH[26].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/*	Unified Channel 27 Registers                               */
/* ----------------------------------------------------------- */
  EMIOS_1.CH[27].CADR.R = 0x00000000;
            /*  [16-31]  Channel eMIOS_1_CADR27 Data Register - eMIOS_1_CADR27 : Value = 0*/

  EMIOS_1.CH[27].CCR.R = 0x00000000;
            /* Channel Control Register                 */
            /* Freeze Enable : Normal operation         */
            /* Prescaler Divide Ratio : 1             */
            /* Prescaler Enable : Disable               */
            /* Flag generation Request: Assigned to Interrupt */
            /* Input Filter: Bypassed                   */
            /* Filter clock select : Prescaler clock    */
            /* Flag Enable : IRQ not generated      */
            /* Force Match A : Disabled                 */
            /* Force Match B : Disabled                 */
            /* Bus Select : Counter bus[A]                */
            /* Edge Selection Bit :FLAG                 */
            /* Edge Polarity :Falling                   */
            /* Mode : Default Mode                      */

/* ----------------------------------------------------------- */
/* EMIOS Channel Disable Register  (EMIOS_UCDIS)           */
/* ----------------------------------------------------------- */
  EMIOS_1.UCDIS.R = 0x00000000;
            /* Channel n is Enabled  */
            /*   n = 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27 */
}



 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

