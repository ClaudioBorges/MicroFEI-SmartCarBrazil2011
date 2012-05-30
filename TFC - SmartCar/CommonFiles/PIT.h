/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __PIT_H__
#define __PIT_H__

/*
 *		Defines
 */
#include "Setup.h"

/*
 *		Defines
 */
/*	1000ms		--		SYSTEM_CLOCK
	timeInMs 	--		IncCount */
#define PITGetInIncFromMs(timeInMs)	((SYSTEM_CLOCK/1000ul)*timeInMs)

/*
 *		Function Prototypes
 */
 void initPIT(void);
 void initPITCh(
	uint8_t channel,
	uint32_t cntValue,
	uint8_t vectorNum,
	uint8_t intPrior);

#endif // __PIT_H__