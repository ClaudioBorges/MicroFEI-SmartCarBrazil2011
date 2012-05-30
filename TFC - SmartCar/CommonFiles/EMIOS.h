/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __EMIOS_H__
#define __EMIOS_H__

/*
 *		Defines
 */
#include "Setup.h"

/*
 *		Defines
 */
// Clock
#define EMIOS_0_PRESCALER	16ul	/* Divide 64 MHz sysclk by 15+1 = 16 for 4MHz eMIOS clk*/
#define EMIOS_0_CLOCK		(SYSTEM_CLOCK/EMIOS_0_PRESCALER)

#define BSL_CHANNEL_A		0x0
#define BSL_CHANNEL_B_C_D_E	0x1

// Channels
#define EMIOS_0_0		0  /*PA0*/
#define EMIOS_0_1		1  /*PA1*/
#define EMIOS_0_2		2  /*PA2*/
#define EMIOS_0_3		3  /*PA3*/
#define EMIOS_0_3_B		27 /*PB11*/
#define EMIOS_0_4		4  /*PA4*/
#define EMIOS_0_4_B		28 /*PB12*/
#define EMIOS_0_5		5  /*PA5*/
#define EMIOS_0_5_B		29 /*PB13*/
#define EMIOS_0_6		6  /*PA6*/
#define EMIOS_0_6_B		30 /*PB14*/
#define EMIOS_0_7		7  /*PA7*/
#define EMIOS_0_7_B		31 /*PB15*/

#define EMIOS_0_8		8  /*PA8*/
#define EMIOS_0_9		9  /*PA9*/
#define EMIOS_0_10		10 /*PA10*/
#define EMIOS_0_10_B	80 /*PF0*/
#define EMIOS_0_11		11 /*PA11*/
#define EMIOS_0_11_B	81 /*PF1*/
#define EMIOS_0_12		44 /*PC12*/
#define EMIOS_0_12_B	82 /*PF2*/
#define EMIOS_0_13		45 /*PC13*/
#define EMIOS_0_13_B	83 /*PF3*/
#define EMIOS_0_14		46 /*PC14*/
#define EMIOS_0_14_B	84 /*PF4*/
#define EMIOS_0_15		47 /*PC15*/

#define EMIOS_0_16		64 /*PE0*/
#define EMIOS_0_17		65 /*PE1*/
#define EMIOS_0_18		66 /*PE2*/
#define EMIOS_0_19		67 /*PE3*/
#define EMIOS_0_20		68 /*PE4*/
#define EMIOS_0_21		69 /*PE5*/
#define EMIOS_0_22		70 /*PE6*/
#define EMIOS_0_22_B	85 /*PF5*/
#define EMIOS_0_23		71 /*PE7*/
#define EMIOS_0_23_B	86 /*PF6*/
#define EMIOS_0_24		106 /*PG10*/
#define EMIOS_0_25		107 /*PG11*/
#define EMIOS_0_26		108 /*PG12*/
#define EMIOS_0_27		109 /*PG13*/

/*
 *		Function Prototypes
 */
void vfnInit_Emios_0(void);
void vfnInit_Emios_0_Mcb(uint8_t u8Channel,
						 uint16_t u16Period,
						 uint8_t prescaler);
void vfnInit_Emios_0_Opwm(uint8_t u8Channel,
						  uint8_t u8PcrVal,
						  uint16_t u16A,
						  uint16_t u16B,
						  uint8_t dutyPol,
						  uint8_t busSelect);
void vfnSet_Duty_Opwm(uint8_t u8Channel,
					  uint16_t u16Duty);
void vfnSet_Duty_Perc_Opwm(uint8_t u8Channel,
						   uint16_t u16DutyPerc,
						   uint16_t u16McbChannel);

#endif // __EMIOS_H__