/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#include "MPC5604B_0M27V_0102.h" /* Use proper include file */
#include "Driver_EMIOS.h"
#include "Driver_MPC5604B.h"

volatile uint32_t uICValue;

void INT_IC(void)
{
	if (EMIOS_0.GFR.B.F0) 
	{
	
		uICValue = EMIOS_0.CH[3].CADR.B.CADR;
		
		EMIOS_0.CH[3].CADR.B.CADR = 0;

		
		EMIOS_0.CH[3].CSR.B.OVR 	= 1;
		EMIOS_0.CH[3].CSR.B.OVFL 	= 1;
		EMIOS_0.CH[3].CSR.B.FLAG 	= 1;	
	}
}


void vfnInit_Saic(void)
{
	INTC.PSR[142].R = 0x04; // REMOVER DAQUI!!!!
	
	vfnInit_Emios_0_Mcb(23, 0xFFFFFF); /* Set channel 23 as MCB  */	
	
    vfnInit_Emios_0_Saic(NTSC_COMP_SYNC_CHANNEL, 
						 NTSC_COMP_SYNC_PCR_CHANNEL,
						 NTSC_COMP_SYNC_EDGE);
    vfnInit_Emios_0_Saic(NTSC_VERT_SYNC_CHANNEL, 
						 NTSC_VERT_SYNC_PCR_CHANNEL,
						 NTSC_VERT_SYNC_EDGE);
	vfnInit_Emios_0_Saic(NTSC_BURST_GATE_SYNC_CHANNEL, 
						 NTSC_BURST_GATE_PCR_CHANNEL,
						 NTSC_BURST_GATE_EDGE);
}

