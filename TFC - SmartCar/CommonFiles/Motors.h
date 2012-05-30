/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __MOTORS_H__
#define __MOTORS_H__

/*
 *		Includes
 */
#include "Driver_EMIOS.h"

/*
 *		Defines
 */
/***** DC MOTORS *****/
// PIT configuration
#define DCMOTORS_REFRESH_TIME_IN_MS		10
#define DCMOTORS_STOP_TIME_IN_MS		4000

#define SERVO_REFRESH_TIME_IN_MS		40

// Source clock configuration
#define DCMOTORS_CHANNEL_COUNTER		0
#define DCMOTORS_COUNTER_PRESCALER		4ul	/* Set channel prescaler divide by 4 (to 1Mhz) */

#define DCMOTORS_CLOCK					(EMIOS_0_CLOCK/DCMOTORS_COUNTER_PRESCALER)

/* 	1/(1Hz)				--		DCMOTORS_CLOCK
	1/(freqInHz)		--		DCMotorsInc */
#define DCMotorsGetInIncFromFreqInHz(freqInHz)		\
			(DCMOTORS_CLOCK/freqInHz)
#define DCMOTORS_PERIOD_IN_INC			DCMotorsGetInIncFromFreqInHz(250)

// Channels Configuration
// Motor 1 ==>> Right
#define DCMOTOR1_CHANNEL			2
#define DCMOTOR1BACK_CHANNEL		4
#define DCMOTOR1_PCR_CHANNEL		EMIOS_0_2
#define DCMOTOR1BACK_PCR_CHANNEL	EMIOS_0_4

// Motor 2 ==>> Left
#define DCMOTOR2_CHANNEL			3
#define DCMOTOR2BACK_CHANNEL		5
#define DCMOTOR2_PCR_CHANNEL		EMIOS_0_3
#define DCMOTOR2BACK_PCR_CHANNEL	EMIOS_0_5

// Polarity Configuration
#define DCMOTOR1_DUTY_POL			0
#define DCMOTOR1BACK_DUTY_POL		0

#define DCMOTOR2_DUTY_POL			0
#define DCMOTOR2BACK_DUTY_POL		0

/***** SERVO MOTOR *****/
// Degree > 90 ==>> Right
// Degree < 90 ==>> Left

// Source clock configuration
#define SERVOMOTOR_CHANNEL_COUNTER		8
#define SERVOMOTOR_COUNTER_PRESCALER	4ul	/* Set channel prescaler divide by 4 (to 1Mhz) */

#define SERVOMOTOR_CLOCK				(EMIOS_0_CLOCK/SERVOMOTOR_COUNTER_PRESCALER)

/* 	1/(1Hz)				--		SERVOMOTOR_CLOCK
	1/(freqInHz)		--		ServoMotorInc */
#define ServoMotorGetInIncFromFreqInHz(freqInHz)		\
			(SERVOMOTOR_CLOCK/freqInHz)
#define SERVOMOTOR_PERIOD_IN_INC			ServoMotorGetInIncFromFreqInHz(50)

// Channels Configuration
#define SERVOMOTOR_CHANNEL			11
#define SERVOMOTOR_PCR_CHANNEL		EMIOS_0_11_B

// Polarity Configuration
#define SERVOMOTOR_DUTY_POL			0

// Degrees
/*	1s			--		SERVOMOTOR_CLOCK
	0,0005s		-- 		SERVO_MIN_TIME */
#define SERVO_MIN_TIME	((SERVOMOTOR_CLOCK/2000ul)) // 0 Degree - 0,5ms

/*	1s			--		SERVOMOTOR_CLOCK
	0,0025s		-- 		SERVO_MAX_TIME */
#define SERVO_MAX_TIME	((SERVOMOTOR_CLOCK/400ul))	// 180 Degree - 2,5ms

/*
 *		Function Prototypes
 */
void vfnInit_Motors(void);

void vfnSet_DCMotor1_Duty_Perc(uint16_t u16Perc);
void vfnSet_DCMotor1_Back_Duty_Perc(uint16_t u16Perc);
void vfnSet_DCMotor2_Duty_Perc(uint16_t u16Perc);
void vfnSet_DCMotor2_Back_Duty_Perc(uint16_t u16Perc);

/*
void vfnSet_DCMotorParams(uint8_t index,
						  int8_t maxDutyPerc,
						  int8_t minDutyPerc,
						  int8_t incDutyPerc);
*/

void vfnSet_ServoMotor_Deg(uint16_t u16PositionDeg);
/*
void vfnSet_ServoMotorParams(uint8_t maxDegree,
							 uint8_t minDegree,
							 int8_t incDegree);
*/
#endif // __MOTORS_H__
