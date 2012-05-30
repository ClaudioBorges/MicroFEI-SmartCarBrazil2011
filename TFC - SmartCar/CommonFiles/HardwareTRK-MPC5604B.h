/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __HARDWARE_TRK_MPC5604B_H__
#define __HARDWARE_TRK_MPC5604B_H__

/******************** LEDs ********************/
#define OBE_LED1	SIU.PCR[68].B.OBE
#define LED1		SIU.GPDO[68].B.PDO

#define OBE_LED2	SIU.PCR[69].B.OBE
#define LED2		SIU.GPDO[69].B.PDO

#define OBE_LED3	SIU.PCR[70].B.OBE
#define LED3		SIU.GPDO[70].B.PDO

#define OBE_LED4	SIU.PCR[71].B.OBE
#define LED4		SIU.GPDO[71].B.PDO

//#warning "LED_ON/LED_OFF must be adjusted."
#define LED_ON		0
#define LED_OFF		1

/***************** Switches *******************/
#define IBE_S1		SIU.PCR[64].B.IBE
#define S1			SIU.GPDI[64].B.PDI

#define IBE_S2		SIU.PCR[65].B.IBE
#define S2			SIU.GPDI[65].B.PDI

#define IBE_S3		SIU.PCR[66].B.IBE
#define S3			SIU.GPDI[66].B.PDI

#define IBE_S4		SIU.PCR[67].B.IBE
#define S4			SIU.GPDI[67].B.PDI

//#warning "SWITCH_ON/SWITCH_OFF must be adjusted."
#define SWITCH_ON	0
#define SWITCH_OFF	1

#define AnySwitchIsPressed()				\
	(S1 == SWITCH_ON || S2 == SWITCH_ON	||	\
	 S3 == SWITCH_ON || S4 == SWITCH_ON)

#define initLEDs()		\
{						\
	OBE_LED1 = 1;		\
	OBE_LED2 = 1;		\
	OBE_LED3 = 1;		\
	OBE_LED4 = 1;		\
						\
	LED1 = LED_OFF;		\
	LED2 = LED_OFF;		\
	LED3 = LED_OFF;		\
	LED4 = LED_OFF;		\
}

#endif // __HARDWARE_TRK_MPC5604B_H__