/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __SETUP_H__
#define __SETUP_H__

/*
 *		Defines
 */
#define SYSTEM_CLOCK	64000000ul
#define ENABLE_WATCHDOG
#define WATCHDOG_CLOCK	128000ul

/*	1000ms		--		SYSTEM_CLOCK
	timeInMs 	--		IncCount */
#define SWTGetInIncFromMs(timeInMs)	((WATCHDOG_CLOCK/1000ul)*timeInMs)

/*
 *		Function Prototypes
 */
void vfnDisable_Watchdog(void);
void vfnInit_Peri_Clk_Gen(void);
void vfnInit_Modes_And_Clock(void);
void vfnInit_Clock(void);

#ifdef ENABLE_WATCHDOG
void ClearWDT(void);
#else // ENABLE_WATCHDOG
#define ClearWDT()
#endif // ENABLE_WATCHDOG

#endif // __SETUP_H__