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
#include "Driver_EMIOS.h"

/*
 *		Functions
 */
void vfnInit_Emios_0(void)
{
	EMIOS_0.MCR.B.GPRE = (EMIOS_0_PRESCALER - 1);
  	EMIOS_0.MCR.B.GPREN = 1;  							/* Enable eMIOS clock */
  	EMIOS_0.MCR.B.GTBE = 1;   							/* Enable global time base */
  	EMIOS_0.MCR.B.FRZ = 1;    							/* Enable stopping channels when in debug mode */
}

void vfnInit_Emios_0_Mcb(uint8_t u8Channel,
						 uint16_t u16Period,
						 uint8_t prescaler)
{
  	EMIOS_0.CH[u8Channel].CADR.R      = u16Period;	    /* Period will be u16Period clocks (usec) */
  	EMIOS_0.CH[u8Channel].CCR.B.MODE  = 0x50; 			/* Set as Modulus Up Counter Buffered (MCB) */
  	EMIOS_0.CH[u8Channel].CCR.B.BSL   = 0x1;			/* Use counter bus B,C,D,or E */
 	EMIOS_0.CH[u8Channel].CCR.B.UCPRE = (prescaler - 1);
  	EMIOS_0.CH[u8Channel].CCR.B.UCPEN = 1;    			/* Enable prescaler*/
  	EMIOS_0.CH[u8Channel].CCR.B.FREN  = 1; 				/* Freeze channel counting when in debug mode */
}

void vfnInit_Emios_0_Opwm(uint8_t u8Channel,
						  uint8_t u8PcrVal,
						  uint16_t u16A,
						  uint16_t u16B,
						  uint8_t dutyPol,
						  uint8_t busSelect)
{								
  	EMIOS_0.CH[u8Channel].CADR.R = u16A;        		/* Leading edge when channel counter bus=0 */
  	EMIOS_0.CH[u8Channel].CBDR.R = u16B;        		/* Trailing edge when channel's counter bus=4 */
  	EMIOS_0.CH[u8Channel].CCR.B.BSL = busSelect;
  	EMIOS_0.CH[u8Channel].CCR.B.EDPOL = dutyPol;		/* Polarity-leading edge sets output/trailing clears */
  	EMIOS_0.CH[u8Channel].CCR.B.MODE = 0x60; 			/* Mode is OPWM Buffered */
  	SIU.PCR[u8PcrVal].R = 0x0600;           			/* MPC56xxB: Assign EMIOS_0 ch u8PcrVal to pad */
  	SIU.GPDO[u8PcrVal].B.PDO = (~dutyPol);
}


void vfnSet_Duty_Opwm(uint8_t u8Channel,
					  uint16_t u16Duty)
{
	EMIOS_0.CH[u8Channel].CBDR.R = u16Duty;     		/* Trailing edge when channel counter bus = u16Duty */
}

void vfnSet_Duty_Perc_Opwm(uint8_t u8Channel,
						   uint16_t u16DutyPerc,
						   uint16_t u16McbChannel)
{
	uint16_t u16Period;
	u16Period = (uint16_t)(EMIOS_0.CH[u16McbChannel].CADR.R + 1);	/* Takes the period from the channel used as MCB */
	vfnSet_Duty_Opwm(u8Channel, (uint16_t)(u16DutyPerc * u16Period / 100));
}

void vfnInit_Emios_0_Ipwm(uint8_t u8Channel, uint8_t u8PcrVal,uint8_t u8Pol)
{
  EMIOS_0.CH[u8Channel].CCR.B.BSL = 0x1;				/* Use counter bus B,C,D,or E */
  EMIOS_0.CH[u8Channel].CCR.B.EDPOL = u8Pol;			/* Polarity-leading edge sets output/trailing clears*/
  EMIOS_0.CH[u8Channel].CCR.B.EDSEL = 1;				/* Both edges triggering*/
  EMIOS_0.CH[u8Channel].CCR.B.FCK = 1;	    			/* Input filter bit clock reference is the system clock*/
  EMIOS_0.CH[u8Channel].CCR.B.IF = 1;				    /* Input filter bit of 2 clock cycles*/ 
  EMIOS_0.CH[u8Channel].CCR.B.MODE = 0b0000100; 		/* Mode is IPWM Input Pulse Width Measurement */
  EMIOS_0.CH[u8Channel].CCR.B.FREN = 1;	    			/* Freeze channel counting when in debug mode */
  EMIOS_0.CH[u8Channel].CCR.B.DMA = 0;	  				/* Flag/overrun assigned to interrupt request instead of CTU*/
  EMIOS_0.CH[u8Channel].CCR.B.FEN = 0;	    			/* Enables Unified Channel FLAG bit to generate an interrupt signal*/
  SIU.PCR[u8PcrVal].B.PA = 3;            			    /* Selects eMIOS path as alternative mode 3 for input signal */
  SIU.PCR[u8PcrVal].B.IBE = 1;          				/* Input buffer of the pad is enabled */
}  
  
void vfnInit_Emios_0_Saic(uint8_t u8Channel, uint8_t u8PcrVal, uint8_t u8Pol)
{
	//EMIOS_0.CH[u8Channel].CCR.B.UCPEN 	= 1;
	//EMIOS_0.CH[u8Channel].CCR.B.UCPRE 	= 1;
	
	EMIOS_0.CH[u8Channel].CCR.B.BSL 	= 0; 		/* Use counter bus A which is eMIOS Ch 23 */
	EMIOS_0.CH[u8Channel].CCR.B.EDPOL 	= u8Pol; 	/* Edge Select- Single edge trigger (count) */
	EMIOS_0.CH[u8Channel].CCR.B.EDSEL 	= 0; 		/* Edge Select- Single edge trigger (count) */
	EMIOS_0.CH[u8Channel].CCR.B.FCK 	= 1; 		/* Input filter will use main clock */
	EMIOS_0.CH[u8Channel].CCR.B.IF 		= 0b1000; 	/* Input filger uses 2 clock periods */
	
	EMIOS_0.CH[u8Channel].CCR.B.FEN 	= 1; /* Enable Interrupt */
	
	EMIOS_0.CH[u8Channel].CCR.B.MODE 	= 2; /* Mode is PEC, continuous */

	/* NOTE: write to CADR after MODE is set */
	SIU.PCR[u8PcrVal].B.PA = 3; /* Initialize pad for eMIOS channel */
	SIU.PCR[u8PcrVal].B.IBE = 1; /* Initialize pad for input */
}

int32_t i32Get_Pulse_Width(uint8_t u8Channel)
{
	int32_t i32PulseWidth;
	if(EMIOS_0.CH[u8Channel].CSR.B.FLAG==1)
	{		
		i32PulseWidth = EMIOS_0.CH[u8Channel].CADR.R - EMIOS_0.CH[u8Channel].CBDR.R;	/*Pulse width by subtracting the value in B1 from A2*/
		EMIOS_0.CH[u8Channel].CSR.B.FLAG = 1;											/*Clear Flag*/
	  	return i32PulseWidth;
	}
}

//	if(EMIOS_0.GFR.B.F1==1){
//	pepe=EMIOS_0.CH[1].CADR.B.CADR - EMIOS_0.CH[1].CBDR.B.CBDR;	/*pulse width by subtracting the value in B1 from A2*/
//	EMIOS_0.GFR.B.F1=1;											/*Clear Flag*/	
//	EMIOS_0.CH[0].CCNTR.B.CCNTR=0;								/*Restart counter*/
//	}/*Wait for Flag activation*/


uint16_t u16Read_Saic(uint8_t u8Channel,uint16_t u16MinVal,uint16_t u16MaxVal)
{
	uint16_t u16Saic;
	if (EMIOS_0.CH[u8Channel].CSR.B.FLAG == 1) /* If flag at end of window */
	{
		u16Saic = EMIOS_0.CH[u8Channel].CADR.R; /* Read Captured input*/
		EMIOS_0.CH[u8Channel].CSR.B.FLAG = 1; /* Clear flag */
		
		if((u16Saic<u16MaxVal) & (u16Saic>u16MinVal))
		{
			return u16Saic; 	
		}
		else
		{
			return 0;
		}
		
	}
	else
	{
		return 0;
	}
}
/*uint16_t u16Read_Saic_clk(uint8_t u8Channel,uint16_t u16MaxVal)
{
	EMIOS_0.CH[u8Channel].CCR.B.EDSEL = 1; 
	uint16_t u16Saic;
	if (EMIOS_0.CH[u8Channel].CSR.B.FLAG == 1) 
	{
		u16Saic = EMIOS_0.CH[u8Channel].CADR.R; 
		EMIOS_0.CH[u8Channel].CSR.B.FLAG = 1; 
		
		if(u16Saic>u16MaxVal)
		{
			return u16Saic; 	
		}
		else
		{
			return 0;
		}
		
	}
	else
	{
		return 0;
	}
}*/