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
#include "PIT.h"

#include "HardwareTRK-MPC5604B.h"

//#include "Motors.h"

/*
 *		Functions
 */
void initPIT(void)
{
	PIT.PITMCR.B.MDIS = 1;	// Global off

	PIT.PITMCR.B.FRZ = 1;		// Freeze in Debug = 1 / Continue in Debug = 0

	//initPITCh(0, PITGetInIncFromMs(DCMOTORS_REFRESH_TIME_IN_MS), 59, 1);
	//initPITCh(1, PITGetInIncFromMs(DCMOTORS_STOP_TIME_IN_MS), 60, 1);
	//initPITCh(2, PITGetInIncFromMs(SERVO_REFRESH_TIME_IN_MS), 61, 1);
	//initPITCh(3, PITGetInIncFromMs(250), 127, 1);
	//initPITCh(4, PITGetInIncFromMs(125), 128, 1);
	initPITCh(5, PITGetInIncFromMs(1500), 129, 10);

	PIT.PITMCR.B.MDIS = 0;	// Global on
}

 void initPITCh(
	uint8_t channel,
	uint32_t cntValue,
	uint8_t vectorNum,
	uint8_t intPrior)
{
	PIT.CH[channel].TCTRL.B.TEN = 0;	// Disable channel
	
	PIT.CH[channel].TFLG.B.TIF = 1;		//w1c - Clear IF
	INTC.PSR[vectorNum].B.PRI = intPrior;	// Interrupt vector priority
	PIT.CH[channel].TCTRL.B.TIE = 1;	// Enable interrupt
	
	PIT.CH[channel].LDVAL.B.TSV = cntValue;
	
	PIT.CH[channel].TCTRL.B.TEN = 1;	// Enable channel
}

/*
void Pit0ISR(void)
{
	PIT.CH[0].TFLG.B.TIF = 1;
	
	//LED1 ^= 1;
}

void Pit1ISR(void)
{
	PIT.CH[1].TFLG.B.TIF = 1;
	
	//LED2 ^= 1;
}

void Pit2ISR(void)
{
	PIT.CH[2].TFLG.B.TIF = 1;
	
	//LED3 ^= 1;
	LED1 ^= 1;
}
*/

void Pit3ISR(void)
{
	PIT.CH[3].TFLG.B.TIF = 1;
	
	//LED4 ^= 1;
	//LED2 ^= 1;
}

void Pit4ISR(void)
{
	PIT.CH[4].TFLG.B.TIF = 1;
	
	//LED3 ^= 1;
}


void Pit5ISR(void)
{
	PIT.CH[5].TFLG.B.TIF = 1;
	
	//LED4 ^= 1;
}
