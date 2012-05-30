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
/*
 *		Includes
 */
 #include "MPC5604B_M27V.h"

/*
 *		Extern Variables
 */
extern IVOR4Handler();
extern uint32_t __IVPR_VALUE; /* Interrupt Vector Prefix vaue from link file*/
extern const vuint32_t IntcIsrVectorTable[];

/*
 *		Functions
 */
asm void initIrqVectors(void) {
  lis	   r3, __IVPR_VALUE@h   /* IVPR value is passed from link file */
  ori      r3, r3, __IVPR_VALUE@l 
  mtivpr   r3									 
}

void initINTC(void) {	
  INTC.MCR.B.HVEN = 0;       /* Single core: initialize for SW vector mode */
  INTC.MCR.B.VTES = 0;       /* Single core: Use default vector table 4B offsets */
  INTC.IACKR.R = (uint32_t) &IntcIsrVectorTable[0];    /* MPC555x: INTC ISR table base */
}

void enableIrq(void) {
  INTC.CPR.B.PRI = 0;          /* Single Core: Lower INTC's current priority */
  asm(" wrteei 1");	    	   /* Enable external interrupts */
}