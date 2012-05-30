/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

/*
 *		Includes
 */
#include "MPC5604B_M27V.h"
#include "Setup.h"

/*
 *		Functions
 */
void vfnDisable_Watchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}        

void vfnEnable_Watchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  
  SWT.TO.R = SWTGetInIncFromMs(300);
  
  SWT.CR.R = 0x8000010B;     /* Reset on a time-out, Set watchdog enable (WEN) */
  
  ClearWDT();
}

#ifdef ENABLE_WATCHDOG
void ClearWDT(void) 
{
  SWT.SR.R = 0x0000a602;
  SWT.SR.R = 0x0000b480;
}
#endif // ENABLE_WATCHDOG

void vfnInit_Peri_Clk_Gen(void) 
{
  /* The following code is required for MPC56xxB or MPC56xxS:*/
  CGM.SC_DC[0].R = 0x80;   /* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
  CGM.SC_DC[2].R = 0x80;   /* MPC56xxB/S: Enable peri set 3 sysclk divided by 1 */
}

void vfnInit_Modes_And_Clock(void) 
{
  ME.MER.R = 0x0000001D;          		/* Enable DRUN, RUN0, SAFE, RESET modes */
                                  		/* Initialize PLL before turning it on: */
  CGM.FMPLL_CR.R = 0x02400100;    		/* 8 MHz xtal: Set PLL0 to 64 MHz */   
  ME.RUN[0].R = 0x001F0074;       		/* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  ME.RUNPC[1].R = 0x00000010; 	  		/* Peri. Cfg. 1 settings: only run in RUN0 mode */
  
  
  ME.PCTL[92].R = 0x01;           		/* PIT, RTI: select ME_RUN_PC[1] */
  ME.PCTL[32].R = 0x01; 	      		/* MPC56xxB/P/S ADC 0: select ME.RUNPC[1] */	
  ME.PCTL[68].R = 0x01; 	      		/* MPC56xxB/S SIU: select ME.RUNPC[1] */
  ME.PCTL[72].R = 0x01;           		/* MPC56xxB/S EMIOS 0:  select ME.RUNPC[0] */	
  ME.PCTL[48].R = 0x01;           		/* MPC56xxB/P/S LINFlex 0: select ME.RUNPC[1] */
  
                                  		/* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         		/* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         		/* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     		/* Wait for mode transition to complete */    
                                  		/* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} 	/* Verify RUN0 is the current mode */
}

void vfnInit_Clock(void)
{
  vfnInit_Modes_And_Clock();    /* Initialize mode entries and system clock */
  #ifdef ENABLE_WATCHDOG
  vfnEnable_Watchdog();      	/* Enable watchdog */
  #else // ENABLE_WATCHDOG
  vfnDisable_Watchdog();      	/* Disable watchdog */
  #endif // ENABLE_WATCHDOG
  vfnInit_Peri_Clk_Gen();       /* Initialize peripheral clock generation for DSPIs */
}
