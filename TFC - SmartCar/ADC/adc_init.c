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
 * file                   : adc_init.c
 *
 * Target Compiler        : Diab
 *
 * Target Part            : MPC5604B
 *
 * Part Errata Fixes      : none
 *
 * Project Last Save Date : 06-Aug-2011 13:15:20
 *
 * Created on Date        : 06-Aug-2011 13:15:23
 *
 * Brief Description      : This file contains the ADC-CTU Configuration and
 *                          initialization functions.
 *
 ******************************************************************************** 
 *
 * Detail Description     : This File contains function that setup Normal &
 *                         injected channels, Sampling, PreSampling, interrupt,
 *                         Threshold and CTU.
 *
 ******************************************************************************** 
 *
 *######################################################################
*/

 
 
/********************  Dependent Include files here **********************/

#include "adc_init.h"
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */



/*********************  Initialization Function(s) ************************/

void adc_init_fnc(void)
{

    ADC.MCR.B.PWDN = 0x1;
        /* Enter power down state */
    ADC.MCR.B.ABORT =0x1;
        /* Abort all conversion in process */

/*-----------------------------------------------------------*/
/* Clear All Interrupt Flags - Write 1 to Clear              */
/*-----------------------------------------------------------*/
    //ADC.ISR.R = 0x0000001F; 
    ADC.ISR.R = 0x00000000;
        /* B27: End of CTU Conversion EOCTU Flag */
        /* B28: End of Injected Channel Conversion JEOC Flag */
        /* B29: End of Injected Chain Conversion interrupt JECH Flag */
        /* B30: End of Channel Conversion EOC Flag */
        /* B31: End of Chain Conversion ECH Flag */

/*-----------------------------------------------------------*/
/* All Init that can be done in Power Down State             */
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/* ADC General Setup                                         */
/*-----------------------------------------------------------*/
     ADC.MCR.R = 0xA0000000;
        /* Conversion data Overwrite : Enabled */
        /* Conversion Data Aligned: Right Aligned */
        /* Conversion Mode Selected :  Scan */
        /* Normal Start conversion Disabled :- can be configured using adc_normal_Start_fnc */
        /* Injected Start conversion Disabled :- can be configured using adc_injected_Start_fnc */
        /* Injection external trigger : Configured in adc_trigger_setup_fnc */
        /* Injection trigger edge : Configured in adc_trigger_setup_fnc */
        /* Cross Triggering Unit needs to be configured after CTU initialization */
        /* ADC Conversion clock selected as :  System Clock /*System Clock/2 */
        /* ADCLKSEL Init needs to be done in POWER DOWN State */
        /* Abort chain Conversion Disabled can be configured using adc_abort_chain_fnc */
        /* Abort Normal Conversion Disabled can be configured using adc_normal_stop_fnc */
        /* Auto Clock Off feature: Disabled */
        /* Power Down Mode is Enabled while ADC Clock initialization */


     //ADC.MCR.B.PWDN = 0x1;
        /* ADC Power down state :Enabled */
     ADC.DSDR.R = 0x00000000;
        /* The Decode Signal Delay : 0 clock Cycle      */

     ADC.PDEDR.R = 0x00000000;
        /* The Power Down Delay : 0 clock Cycle      */



/*-----------------------------------------------------------*/
/*      Conversion Timing Register 0(ADC_CTR0)               */
/*-----------------------------------------------------------*/
    ADC.CTR[0].R = 0x00000203;
        /* Phase duration Latch : 0 */
        /* Input Sampling Duration : 4 clock Cycles  */
        /* Input Comparison Duration : 2 clock Cycles*/
        /* Offset Shift Duration : 0 clock Cycles*/

/*-----------------------------------------------------------*/
/*      Conversion Timing Register 0(ADC_CTR1)               */
/*-----------------------------------------------------------*/
    ADC.CTR[1].R = 0x00000203;
        /* Phase duration Latch : 0 */
        /* Input Sampling Duration : 4 clock Cycles  */
        /* Input Comparison Duration : 2 clock Cycles*/

/*-----------------------------------------------------------*/
/*      Conversion Timing Register 0(ADC_CTR2)               */
/*-----------------------------------------------------------*/
    ADC.CTR[2].R = 0x00000203;
        /* Phase duration Latch : 0 */
        /* Input Sampling Duration : 4 clock Cycles  */
        /* Input Comparison Duration : 2 clock Cycles*/
/*-----------------------------------------------------------*/
/*   ADC PreSampling Configuration                           */
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/*     PreSampling Control Register(ADC_PSCR)              */
/*-----------------------------------------------------------*/
    ADC.PSCR.R = 0x00000000;
        /* Sampling bypass : Disabled */
        /* PreSampling Voltage Selected for internal precision channels : V0    */
        /* PreSampling Voltage Selected for internal extended channels : V0    */
        /* PreSampling Voltage Selected for external channels : V0    */


/*-----------------------------------------------------------*/
/*        PreSampling Channel Enable Register(ADC_PRER0)        */
/*-----------------------------------------------------------*/
    ADC.PSR[0].R = 0x00000000;
        /* ADC Channel 0 PreSampling : Disabled */
        /* ADC Channel 1 PreSampling : Disabled */
        /* ADC Channel 2 PreSampling : Disabled */
        /* ADC Channel 3 PreSampling : Disabled */
        /* ADC Channel 4 PreSampling : Disabled */
        /* ADC Channel 5 PreSampling : Disabled */
        /* ADC Channel 6 PreSampling : Disabled */
        /* ADC Channel 7 PreSampling : Disabled */
        /* ADC Channel 8 PreSampling : Disabled */
        /* ADC Channel 9 PreSampling : Disabled */
        /* ADC Channel 10 PreSampling : Disabled */
        /* ADC Channel 11 PreSampling : Disabled */
        /* ADC Channel 12 PreSampling : Disabled */
        /* ADC Channel 13 PreSampling : Disabled */
        /* ADC Channel 14 PreSampling : Disabled */
        /* ADC Channel 15 PreSampling : Disabled */

/*-----------------------------------------------------------*/
/*        PreSampling Channel Enable Register(ADC_PRER1)        */
/*-----------------------------------------------------------*/
    ADC.PSR[1].R = 0x00000000;
        /* ADC Channel 32 PreSampling : Disabled */
        /* ADC Channel 33 PreSampling : Disabled */
        /* ADC Channel 34 PreSampling : Disabled */
        /* ADC Channel 35 PreSampling : Disabled */
        /* ADC Channel 36 PreSampling : Disabled */
        /* ADC Channel 37 PreSampling : Disabled */
        /* ADC Channel 38 PreSampling : Disabled */
        /* ADC Channel 39 PreSampling : Disabled */
        /* ADC Channel 40 PreSampling : Disabled */
        /* ADC Channel 41 PreSampling : Disabled */
        /* ADC Channel 42 PreSampling : Disabled */
        /* ADC Channel 43 PreSampling : Disabled */
        /* ADC Channel 44 PreSampling : Disabled */
        /* ADC Channel 45 PreSampling : Disabled */
        /* ADC Channel 46 PreSampling : Disabled */
        /* ADC Channel 47 PreSampling : Disabled */

/*-----------------------------------------------------------*/
/*        PreSampling Channel Enable Register(ADC_PRER2)        */
/*-----------------------------------------------------------*/
    ADC.PSR[2].R = 0x00000000;
        /* ADC Channel 64 PreSampling : Disabled */
        /* ADC Channel 65 PreSampling : Disabled */
        /* ADC Channel 66 PreSampling : Disabled */
        /* ADC Channel 67 PreSampling : Disabled */
        /* ADC Channel 68 PreSampling : Disabled */
        /* ADC Channel 69 PreSampling : Disabled */
        /* ADC Channel 70 PreSampling : Disabled */
        /* ADC Channel 71 PreSampling : Disabled */
        /* ADC Channel 72 PreSampling : Disabled */
        /* ADC Channel 73 PreSampling : Disabled */
        /* ADC Channel 74 PreSampling : Disabled */
        /* ADC Channel 75 PreSampling : Disabled */
        /* ADC Channel 76 PreSampling : Disabled */
        /* ADC Channel 77 PreSampling : Disabled */
        /* ADC Channel 78 PreSampling : Disabled */
        /* ADC Channel 79 PreSampling : Disabled */
        /* ADC Channel 80 PreSampling : Disabled */
        /* ADC Channel 81 PreSampling : Disabled */
        /* ADC Channel 82 PreSampling : Disabled */
        /* ADC Channel 83 PreSampling : Disabled */
        /* ADC Channel 84 PreSampling : Disabled */
        /* ADC Channel 85 PreSampling : Disabled */
        /* ADC Channel 86 PreSampling : Disabled */
        /* ADC Channel 87 PreSampling : Disabled */
        /* ADC Channel 88 PreSampling : Disabled */
        /* ADC Channel 89 PreSampling : Disabled */
        /* ADC Channel 90 PreSampling : Disabled */
        /* ADC Channel 91 PreSampling : Disabled */
        /* ADC Channel 92 PreSampling : Disabled */
        /* ADC Channel 93 PreSampling : Disabled */
        /* ADC Channel 94 PreSampling : Disabled */
        /* ADC Channel 95 PreSampling : Disabled */



/*-----------------------------------------------------------*/
/*  ADC CTU Configuration                                    */
/*-----------------------------------------------------------*/
        adc_ctuevent_init_fnc();            

/*-----------------------------------------------------------*/
/* ADC Channel/Interrupt/Watchdog Configuration              */
/*-----------------------------------------------------------*/

        adc_channel_setup_fnc();            

/*-----------------------------------------------------------*/
/* ADC Trigger Configuration                                 */
/*-----------------------------------------------------------*/

        adc_trigger_setup_fnc();      
        
    ADC.CTR[1].B.INPLATCH 	=	1;
	ADC.CTR[1].B.INPCMP		=	2;
	ADC.CTR[1].B.INPSAMP	=	9;
              
/*-----------------------------------------------------------*/
/* All Init that can be done in Normal State                 */
/*-----------------------------------------------------------*/

    ADC.MCR.B.ABORT =0x0;  
    /* ADC can start conversion */

}

/*********************  CTU Initialization Function(s)  ************************/

void adc_ctuevent_init_fnc()
{
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/
/* CTU Event Register 0(CTU_EVTCFGR0)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[0].R = 0x00000000;
        /* Trigger Mask for CTU Channel 0 : Disabled */
        /* CTU Channel 0 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 0 */

/*-----------------------------------------------------------*/
/* CTU Event Register 1(CTU_EVTCFGR1)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[1].R = 0x00000000;
        /* Trigger Mask for CTU Channel 1 : Disabled */
        /* CTU Channel 1 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 1 */

/*-----------------------------------------------------------*/
/* CTU Event Register 2(CTU_EVTCFGR2)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[2].R = 0x00000000;
        /* Trigger Mask for CTU Channel 2 : Disabled */
        /* CTU Channel 2 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 2 */

/*-----------------------------------------------------------*/
/* CTU Event Register 3(CTU_EVTCFGR3)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[3].R = 0x00000000;
        /* Trigger Mask for CTU Channel 3 : Disabled */
        /* CTU Channel 3 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 3 */

/*-----------------------------------------------------------*/
/* CTU Event Register 4(CTU_EVTCFGR4)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[4].R = 0x00000000;
        /* Trigger Mask for CTU Channel 4 : Disabled */
        /* CTU Channel 4 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 4 */

/*-----------------------------------------------------------*/
/* CTU Event Register 5(CTU_EVTCFGR5)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[5].R = 0x00000000;
        /* Trigger Mask for CTU Channel 5 : Disabled */
        /* CTU Channel 5 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 5 */

/*-----------------------------------------------------------*/
/* CTU Event Register 6(CTU_EVTCFGR6)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[6].R = 0x00000000;
        /* Trigger Mask for CTU Channel 6 : Disabled */
        /* CTU Channel 6 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 6 */

/*-----------------------------------------------------------*/
/* CTU Event Register 7(CTU_EVTCFGR7)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[7].R = 0x00000000;
        /* Trigger Mask for CTU Channel 7 : Disabled */
        /* CTU Channel 7 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 7 */

/*-----------------------------------------------------------*/
/* CTU Event Register 8(CTU_EVTCFGR8)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[8].R = 0x00000000;
        /* Trigger Mask for CTU Channel 8 : Disabled */
        /* CTU Channel 8 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 8 */

/*-----------------------------------------------------------*/
/* CTU Event Register 9(CTU_EVTCFGR9)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[9].R = 0x00000000;
        /* Trigger Mask for CTU Channel 9 : Disabled */
        /* CTU Channel 9 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 9 */

/*-----------------------------------------------------------*/
/* CTU Event Register 10(CTU_EVTCFGR10)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[10].R = 0x00000000;
        /* Trigger Mask for CTU Channel 10 : Disabled */
        /* CTU Channel 10 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 10 */

/*-----------------------------------------------------------*/
/* CTU Event Register 11(CTU_EVTCFGR11)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[11].R = 0x00000000;
        /* Trigger Mask for CTU Channel 11 : Disabled */
        /* CTU Channel 11 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 11 */

/*-----------------------------------------------------------*/
/* CTU Event Register 12(CTU_EVTCFGR12)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[12].R = 0x00000000;
        /* Trigger Mask for CTU Channel 12 : Disabled */
        /* CTU Channel 12 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 12 */

/*-----------------------------------------------------------*/
/* CTU Event Register 13(CTU_EVTCFGR13)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[13].R = 0x00000000;
        /* Trigger Mask for CTU Channel 13 : Disabled */
        /* CTU Channel 13 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 13 */

/*-----------------------------------------------------------*/
/* CTU Event Register 14(CTU_EVTCFGR14)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[14].R = 0x00000000;
        /* Trigger Mask for CTU Channel 14 : Disabled */
        /* CTU Channel 14 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 14 */

/*-----------------------------------------------------------*/
/* CTU Event Register 15(CTU_EVTCFGR15)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[15].R = 0x00000000;
        /* Trigger Mask for CTU Channel 15 : Disabled */
        /* CTU Channel 15 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 15 */

/*-----------------------------------------------------------*/
/* CTU Event Register 16(CTU_EVTCFGR16)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[16].R = 0x00000000;
        /* Trigger Mask for CTU Channel 16 : Disabled */
        /* CTU Channel 16 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 16 */

/*-----------------------------------------------------------*/
/* CTU Event Register 17(CTU_EVTCFGR17)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[17].R = 0x00000000;
        /* Trigger Mask for CTU Channel 17 : Disabled */
        /* CTU Channel 17 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 17 */

/*-----------------------------------------------------------*/
/* CTU Event Register 18(CTU_EVTCFGR18)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[18].R = 0x00000000;
        /* Trigger Mask for CTU Channel 18 : Disabled */
        /* CTU Channel 18 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 18 */

/*-----------------------------------------------------------*/
/* CTU Event Register 19(CTU_EVTCFGR19)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[19].R = 0x00000000;
        /* Trigger Mask for CTU Channel 19 : Disabled */
        /* CTU Channel 19 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 19 */

/*-----------------------------------------------------------*/
/* CTU Event Register 20(CTU_EVTCFGR20)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[20].R = 0x00000000;
        /* Trigger Mask for CTU Channel 20 : Disabled */
        /* CTU Channel 20 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 20 */

/*-----------------------------------------------------------*/
/* CTU Event Register 21(CTU_EVTCFGR21)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[21].R = 0x00000000;
        /* Trigger Mask for CTU Channel 21 : Disabled */
        /* CTU Channel 21 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 21 */

/*-----------------------------------------------------------*/
/* CTU Event Register 22(CTU_EVTCFGR22)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[22].R = 0x00000000;
        /* Trigger Mask for CTU Channel 22 : Disabled */
        /* CTU Channel 22 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 22 */

/*-----------------------------------------------------------*/
/* CTU Event Register 23(CTU_EVTCFGR23)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[23].R = 0x00000000;
        /* Trigger Mask for CTU Channel 23 : Disabled */
        /* CTU Channel 23 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : PIT_Channel 3 */

/*-----------------------------------------------------------*/
/* CTU Event Register 24(CTU_EVTCFGR24)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[24].R = 0x00000000;
        /* Trigger Mask for CTU Channel 24 : Disabled */
        /* CTU Channel 24 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS0_Channel 24 */

/*-----------------------------------------------------------*/
/* CTU Event Register 25(CTU_EVTCFGR25)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[25].R = 0x00000000;
        /* Trigger Mask for CTU Channel 25 : Disabled */
        /* CTU Channel 25 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 26(CTU_EVTCFGR26)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[26].R = 0x00000000;
        /* Trigger Mask for CTU Channel 26 : Disabled */
        /* CTU Channel 26 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 27(CTU_EVTCFGR27)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[27].R = 0x00000000;
        /* Trigger Mask for CTU Channel 27 : Disabled */
        /* CTU Channel 27 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 28(CTU_EVTCFGR28)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[28].R = 0x00000000;
        /* Trigger Mask for CTU Channel 28 : Disabled */
        /* CTU Channel 28 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 29(CTU_EVTCFGR29)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[29].R = 0x00000000;
        /* Trigger Mask for CTU Channel 29 : Disabled */
        /* CTU Channel 29 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 30(CTU_EVTCFGR30)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[30].R = 0x00000000;
        /* Trigger Mask for CTU Channel 30 : Disabled */
        /* CTU Channel 30 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 31(CTU_EVTCFGR31)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[31].R = 0x00000000;
        /* Trigger Mask for CTU Channel 31 : Disabled */
        /* CTU Channel 31 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 32(CTU_EVTCFGR32)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[32].R = 0x00000000;
        /* Trigger Mask for CTU Channel 32 : Disabled */
        /* CTU Channel 32 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 0 */

/*-----------------------------------------------------------*/
/* CTU Event Register 33(CTU_EVTCFGR33)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[33].R = 0x00000000;
        /* Trigger Mask for CTU Channel 33 : Disabled */
        /* CTU Channel 33 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 1 */

/*-----------------------------------------------------------*/
/* CTU Event Register 34(CTU_EVTCFGR34)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[34].R = 0x00000000;
        /* Trigger Mask for CTU Channel 34 : Disabled */
        /* CTU Channel 34 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 2 */

/*-----------------------------------------------------------*/
/* CTU Event Register 35(CTU_EVTCFGR35)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[35].R = 0x00000000;
        /* Trigger Mask for CTU Channel 35 : Disabled */
        /* CTU Channel 35 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 3 */

/*-----------------------------------------------------------*/
/* CTU Event Register 36(CTU_EVTCFGR36)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[36].R = 0x00000000;
        /* Trigger Mask for CTU Channel 36 : Disabled */
        /* CTU Channel 36 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 4 */

/*-----------------------------------------------------------*/
/* CTU Event Register 37(CTU_EVTCFGR37)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[37].R = 0x00000000;
        /* Trigger Mask for CTU Channel 37 : Disabled */
        /* CTU Channel 37 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 5 */

/*-----------------------------------------------------------*/
/* CTU Event Register 38(CTU_EVTCFGR38)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[38].R = 0x00000000;
        /* Trigger Mask for CTU Channel 38 : Disabled */
        /* CTU Channel 38 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 6 */

/*-----------------------------------------------------------*/
/* CTU Event Register 39(CTU_EVTCFGR39)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[39].R = 0x00000000;
        /* Trigger Mask for CTU Channel 39 : Disabled */
        /* CTU Channel 39 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 7 */

/*-----------------------------------------------------------*/
/* CTU Event Register 40(CTU_EVTCFGR40)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[40].R = 0x00000000;
        /* Trigger Mask for CTU Channel 40 : Disabled */
        /* CTU Channel 40 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 8 */

/*-----------------------------------------------------------*/
/* CTU Event Register 41(CTU_EVTCFGR41)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[41].R = 0x00000000;
        /* Trigger Mask for CTU Channel 41 : Disabled */
        /* CTU Channel 41 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 9 */

/*-----------------------------------------------------------*/
/* CTU Event Register 42(CTU_EVTCFGR42)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[42].R = 0x00000000;
        /* Trigger Mask for CTU Channel 42 : Disabled */
        /* CTU Channel 42 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 10 */

/*-----------------------------------------------------------*/
/* CTU Event Register 43(CTU_EVTCFGR43)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[43].R = 0x00000000;
        /* Trigger Mask for CTU Channel 43 : Disabled */
        /* CTU Channel 43 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 11 */

/*-----------------------------------------------------------*/
/* CTU Event Register 44(CTU_EVTCFGR44)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[44].R = 0x00000000;
        /* Trigger Mask for CTU Channel 44 : Disabled */
        /* CTU Channel 44 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 12 */

/*-----------------------------------------------------------*/
/* CTU Event Register 45(CTU_EVTCFGR45)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[45].R = 0x00000000;
        /* Trigger Mask for CTU Channel 45 : Disabled */
        /* CTU Channel 45 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 13 */

/*-----------------------------------------------------------*/
/* CTU Event Register 46(CTU_EVTCFGR46)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[46].R = 0x00000000;
        /* Trigger Mask for CTU Channel 46 : Disabled */
        /* CTU Channel 46 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 14 */

/*-----------------------------------------------------------*/
/* CTU Event Register 47(CTU_EVTCFGR47)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[47].R = 0x00000000;
        /* Trigger Mask for CTU Channel 47 : Disabled */
        /* CTU Channel 47 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 15 */

/*-----------------------------------------------------------*/
/* CTU Event Register 48(CTU_EVTCFGR48)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[48].R = 0x00000000;
        /* Trigger Mask for CTU Channel 48 : Disabled */
        /* CTU Channel 48 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 16 */

/*-----------------------------------------------------------*/
/* CTU Event Register 49(CTU_EVTCFGR49)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[49].R = 0x00000000;
        /* Trigger Mask for CTU Channel 49 : Disabled */
        /* CTU Channel 49 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 17 */

/*-----------------------------------------------------------*/
/* CTU Event Register 50(CTU_EVTCFGR50)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[50].R = 0x00000000;
        /* Trigger Mask for CTU Channel 50 : Disabled */
        /* CTU Channel 50 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 18 */

/*-----------------------------------------------------------*/
/* CTU Event Register 51(CTU_EVTCFGR51)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[51].R = 0x00000000;
        /* Trigger Mask for CTU Channel 51 : Disabled */
        /* CTU Channel 51 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 19 */

/*-----------------------------------------------------------*/
/* CTU Event Register 52(CTU_EVTCFGR52)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[52].R = 0x00000000;
        /* Trigger Mask for CTU Channel 52 : Disabled */
        /* CTU Channel 52 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 20 */

/*-----------------------------------------------------------*/
/* CTU Event Register 53(CTU_EVTCFGR53)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[53].R = 0x00000000;
        /* Trigger Mask for CTU Channel 53 : Disabled */
        /* CTU Channel 53 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 21 */

/*-----------------------------------------------------------*/
/* CTU Event Register 54(CTU_EVTCFGR54)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[54].R = 0x00000000;
        /* Trigger Mask for CTU Channel 54 : Disabled */
        /* CTU Channel 54 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 22 */

/*-----------------------------------------------------------*/
/* CTU Event Register 55(CTU_EVTCFGR55)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[55].R = 0x00000000;
        /* Trigger Mask for CTU Channel 55 : Disabled */
        /* CTU Channel 55 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : Reserved  */

/*-----------------------------------------------------------*/
/* CTU Event Register 56(CTU_EVTCFGR56)         */
/*-----------------------------------------------------------*/
    CTU.EVTCFGR[56].R = 0x00000000;
        /* Trigger Mask for CTU Channel 56 : Disabled */
        /* CTU Channel 56 will Trigger ADC Channel : 0 */
        /* Source for the CTU trigger is : eMIOS1_Channel 24 */

/*-----------------------------------------------------------*/
/* CTU Event Register (CTU_CSR)                              */
/*-----------------------------------------------------------*/
    CTU.CSR.R = 0x00000000;
        /* Trigger Interrupt Request: Disabled */
        /* Trigger Interrupt Flag: Disabled */

    ADC.MCR.B.CTUEN= 0x0;
        /* Cross Triggering Unit : Disabled */
}

/*********************  Channel/Interrupt/Watchdog Initialization Function(s) ************************/

void adc_channel_setup_fnc()
{
/*-----------------------------------------------------------*/
/*    Interrupt Mask Register(ADC_IMR)                       */
/*-----------------------------------------------------------*/
    ADC.IMR.R = 0x00000000;
        /* End of Chain Conversion Interrupt : Enabled */
        /* End of Injected Chain Interrupt : Disabled */
        /* End of Channel Conversion Interrupt : Disabled */
        /* End of Injected Channel Interrupt : Disabled */
        /* End of CTU conversion Interrupt : Disabled */


    /* ADC Channel 40 Interrupt : Enable */
	//ADC.CIMR[1].B.CIM8 = 1;


/*-----------------------------------------------------------*/
/*      ADC 0 Channel Setup                                  */
/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
/* Normal Channel Conversion Mask Register 0(ADC_NCMR0)      */
/*-----------------------------------------------------------*/
    ADC.NCMR[0].R = 0x00000000;
        /* ADC Channel 0 in Normal Mode : Disabled */
        /* ADC Channel 1 in Normal Mode : Disabled */
        /* ADC Channel 2 in Normal Mode : Disabled */
        /* ADC Channel 3 in Normal Mode : Disabled */
        /* ADC Channel 4 in Normal Mode : Disabled */
        /* ADC Channel 5 in Normal Mode : Disabled */
        /* ADC Channel 6 in Normal Mode : Disabled */
        /* ADC Channel 7 in Normal Mode : Disabled */
        /* ADC Channel 8 in Normal Mode : Disabled */
        /* ADC Channel 9 in Normal Mode : Disabled */
        /* ADC Channel 10 in Normal Mode : Disabled */
        /* ADC Channel 11 in Normal Mode : Disabled */
        /* ADC Channel 12 in Normal Mode : Disabled */
        /* ADC Channel 13 in Normal Mode : Disabled */
        /* ADC Channel 14 in Normal Mode : Disabled */
        /* ADC Channel 15 in Normal Mode : Disabled */


/*-----------------------------------------------------------*/
/* Normal Channel Conversion Mask Register 1(ADC_NCMR1)      */
/*-----------------------------------------------------------*/
	/* ADC Channel 40 in Normal Mode : Enabled */
	ADC.NCMR[1].B.CH8 = 1;


/*-----------------------------------------------------------*/
/*         Threshold Control Register 0 (ADC_TRC0)           */
/*-----------------------------------------------------------*/
    ADC.TRC[0].R = 0x00000000;
        /* Threshold detection for WatchDog 0 : Disabled */
        /* Threshold Inversion for WatchDog 0:Disabled */
        /* Threshold Channel Select for WatchDog 0 : 0 */

/*-----------------------------------------------------------*/
/*         Threshold Control Register 1 (ADC_TRC1)           */
/*-----------------------------------------------------------*/
    ADC.TRC[1].R = 0x00000000;
        /* Threshold detection for WatchDog 1 : Disabled */
        /* Threshold Inversion for WatchDog 1:Disabled */
        /* Threshold Channel Select for WatchDog 1 : 0 */

/*-----------------------------------------------------------*/
/*         Threshold Control Register 2 (ADC_TRC2)           */
/*-----------------------------------------------------------*/
    ADC.TRC[2].R = 0x00000000;
        /* Threshold detection for WatchDog 2 : Disabled */
        /* Threshold Inversion for WatchDog 2:Disabled */
        /* Threshold Channel Select for WatchDog 2 : 0 */

/*-----------------------------------------------------------*/
/*         Threshold Control Register 3 (ADC_TRC3)           */
/*-----------------------------------------------------------*/
    ADC.TRC[3].R = 0x00000000;
        /* Threshold detection for WatchDog 3 : Disabled */
        /* Threshold Inversion for WatchDog 3:Disabled */
        /* Threshold Channel Select for WatchDog 3 : 0 */

/*-----------------------------------------------------------*/
/*     Threshold Register 0 (ADC_THRHLR0)                    */
/*-----------------------------------------------------------*/
    ADC.THRHLR[0].R = 0x03FF0000;
        /* Lower Threshold value : 0 */
        /* Higher Threshold value : 1023 */

/*-----------------------------------------------------------*/
/*     Threshold Register 1 (ADC_THRHLR1)                    */
/*-----------------------------------------------------------*/
    ADC.THRHLR[1].R = 0x03FF0000;
        /* Lower Threshold value : 0 */
        /* Higher Threshold value : 1023 */

/*-----------------------------------------------------------*/
/*     Threshold Register 2 (ADC_THRHLR2)                    */
/*-----------------------------------------------------------*/
    ADC.THRHLR[2].R = 0x03FF0000;
        /* Lower Threshold value : 0 */
        /* Higher Threshold value : 1023 */

/*-----------------------------------------------------------*/
/*     Threshold Register 3 (ADC_THRHLR3)                    */
/*-----------------------------------------------------------*/
    ADC.THRHLR[3].R = 0x03FF0000;
        /* Lower Threshold value : 0 */
        /* Higher Threshold value : 1023 */

/*-----------------------------------------------------------*/
/* Watchdog Threshold Interrupt Mask Register (ADC_WTIMR)    */
/*-----------------------------------------------------------*/
    ADC.WTIMR.R = 0x00000000;
        /* Low Threshold Interrupt for Watchdog 0 : Disabled */
        /* Low Threshold Interrupt for Watchdog 1 : Disabled */
        /* Low Threshold Interrupt for Watchdog 2 : Disabled */
        /* Low Threshold Interrupt for Watchdog 3 : Disabled */
        /* High Threshold Interrupt for Watchdog 0 : Disabled */
        /* High Threshold Interrupt for Watchdog 1 : Disabled */
        /* High Threshold Interrupt for Watchdog 2 : Disabled */
        /* High Threshold Interrupt for Watchdog 3 : Disabled */

}

/*********************  Trigger Initialization Function(s) ************************/

void adc_trigger_setup_fnc()
{
/*-----------------------------------------------------------*/
/*          ADC 0 Trigger Configuration                      */
/*-----------------------------------------------------------*/
     ADC.MCR.B.JTRGEN = 0x0;
            /* B9: Injection Trigger : Disabled     */
     ADC.MCR.B.JEDGE = 0x0;
            /* Injection trigger edge : Falling*/
}
 
/*
 *######################################################################
 *                           End of File
 *######################################################################
*/

