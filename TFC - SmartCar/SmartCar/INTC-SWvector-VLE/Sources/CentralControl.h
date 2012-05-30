/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __CENTRAL_CONTROL_H__
#define __CENTRAL_CONTROL_H__

#include "Driver_NTSC.h"

// Servo position [degrees]
#define CENTRAL_SERVO_POSITION	90
#define MAX_SERVO_POSITION		(CENTRAL_SERVO_POSITION + 27) // 117
#define MIN_SERVO_POSITION		(CENTRAL_SERVO_POSITION - 27) // 63

//#define MAX_WHEEL_DEGREE		45

// DC motor velocity [percent]
/*
#define MAX_MOTOR_VELOCITY		80
	//#define MAX_MOTOR_SATURATION	80
#define MIN_OUTSIDE_MOTOR_VEL	45
	//#define MIN_OUTSIDE_MOTOR_SAT	60
#define MIN_INSIDE_MOTOR_VEL	((MIN_OUTSIDE_MOTOR_VEL * 3) / 4)
	//#define MIN_INSIDE_MOTOR_SAT	((MIN_OUTSIDE_MOTOR_SAT * 3) / 4)
*/

// Rápido
#define MAX_MOTOR_VELOCITY		62//70 //-- Testado com 90 (ok)
#define MIN_OUTSIDE_MOTOR_VEL	55//54 //-- Testado com 64 (ok)
#define MIN_INSIDE_MOTOR_VEL	((MIN_OUTSIDE_MOTOR_VEL * 2) / 3)
//#define MIN_INSIDE_MOTOR_VEL	((MIN_OUTSIDE_MOTOR_VEL * 3) / 4)
//#define MIN_INSIDE_MOTOR_VEL	((MIN_OUTSIDE_MOTOR_VEL * 1) / 2)

/*
// Conservador
#define MAX_MOTOR_VELOCITY		72
#define MIN_OUTSIDE_MOTOR_VEL	48
#define MIN_INSIDE_MOTOR_VEL	((MIN_OUTSIDE_MOTOR_VEL * 1) / 2)
*/


// Line image
#define NUMBER_OF_LINES		MAX_NTSC_LINES
#define CENTRAL_POSITION	40//CENTER_POS
#define MAX_POSITION		MAX_CENTER_POS

// Position algorithm
#define MAX_ACCEPTED_DERIVATIVE		6
#define MIN_LINES_TO_CALC_DEGREE	3
#define MAX_LINES_GAP				20
#define MAX_LINES_GAP_ON_BORDER		2
//#define BORDER						14

#if (MIN_LINES_TO_CALC_DEGREE < 2)
#error "MIN_LINES_TO_CALC_DEGREE deve ser maior ou igual a 2."
#endif // (MIN_LINES_TO_CALC_DEGREE < 2)

#if (END_OF_RACE_DETECTION == 1)
extern int8_t numberOfCurrLap;
#endif // (END_OF_RACE_DETECTION == 1)

#define GAIN_AVERAGE		0
#define GAIN_DERIVATIVE		0
#define GAIN_MY_POSITION	1

#define GAIN_FINAL			1//9
#define ATT_FINAL			1//6

int8_t i8Calc_Servo_Position(
	uint8_t *pServoPos,		// output
	int16_t *pLineImage,	// input
	uint16_t linesRead);	// input

int8_t i8Calc_Motors_Full_Velocity(
	int16_t *pMotorLVel, 	// output
	int16_t *pMotorRVel, 	// output
	uint8_t servoPos);		// input

int8_t i8Calc_Motors_Low_Velocity(
	int16_t *pMotorLVel, 	// output
	int16_t *pMotorRVel, 	// output
	uint8_t servoPos);		// input

#endif // __CENTRAL_CONTROL_H__
