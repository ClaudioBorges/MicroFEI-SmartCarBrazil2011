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