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
#include "Motors.h"

/*
 *		Defines
 */
#define DCMOTOR1_INDEX	0
#define DCMOTOR2_INDEX	1

/*
 *		Typedefs
 */
typedef struct _DCMOTOR_PARAMS
{
	int8_t DCMotorMaxDutyPerc;
	int8_t DCMotorMinDutyPerc;
	int8_t DCMotorIncDutyPerc;
	int8_t DCMotorCurrentDutyPerc;
} DCMOTOR_PARAMS;

/*
 *		Static variables
 */
static struct _DCMOTOR_PARAMS
	DCMotorParams[2] = { {0, 0, 0, 0},
						 {0, 0, 0, 0} };

uint8_t ServoCurrentDegree = 90;

/*
 *		Functions
 */
 
/***** DC MOTORS *****/
void vfnInit_Motors(void)
{
	//vfnInit_Emios_0();
	
	/***** DC MOTORS *****/
	vfnInit_Emios_0_Mcb(
		DCMOTORS_CHANNEL_COUNTER,
		DCMOTORS_PERIOD_IN_INC,
		DCMOTORS_COUNTER_PRESCALER);
	
	// Motor 1 forward
	vfnInit_Emios_0_Opwm(
			DCMOTOR1_CHANNEL,
			DCMOTOR1_PCR_CHANNEL,
			0,
			0,
			DCMOTOR1_DUTY_POL,
			BSL_CHANNEL_B_C_D_E);
	
	// Motor 1 backward
	vfnInit_Emios_0_Opwm(
			DCMOTOR1BACK_CHANNEL,
			DCMOTOR1BACK_PCR_CHANNEL,
			0,
			0,
			DCMOTOR1BACK_DUTY_POL,
			BSL_CHANNEL_B_C_D_E);
	
	// Motor 2 forward
	vfnInit_Emios_0_Opwm(
			DCMOTOR2_CHANNEL,
			DCMOTOR2_PCR_CHANNEL,
			0,
			0,
			DCMOTOR2_DUTY_POL,
			BSL_CHANNEL_B_C_D_E);
	
	// Motor 2 backward
	vfnInit_Emios_0_Opwm(
			DCMOTOR2BACK_CHANNEL,
			DCMOTOR2BACK_PCR_CHANNEL,
			0,
			0,
			DCMOTOR2BACK_DUTY_POL,
			BSL_CHANNEL_B_C_D_E);
	
	vfnSet_DCMotor1_Duty_Perc(0);
	vfnSet_DCMotor2_Duty_Perc(0);
	vfnSet_DCMotor1_Back_Duty_Perc(0);
	vfnSet_DCMotor2_Back_Duty_Perc(0);
	
	//vfnSet_DCMotorParams(DCMOTOR1_INDEX, 50, 0, 1);
	//vfnSet_DCMotorParams(DCMOTOR2_INDEX, 50, 0, 1);
	
	/***** SERVO MOTOR *****/
	vfnInit_Emios_0_Mcb(
		SERVOMOTOR_CHANNEL_COUNTER,
		SERVOMOTOR_PERIOD_IN_INC,
		SERVOMOTOR_COUNTER_PRESCALER);
		
	vfnInit_Emios_0_Opwm(
			SERVOMOTOR_CHANNEL,
			SERVOMOTOR_PCR_CHANNEL,
			0,
			0,
			SERVOMOTOR_DUTY_POL,
			BSL_CHANNEL_B_C_D_E);
	
	vfnSet_ServoMotor_Deg(ServoCurrentDegree);
	
	//vfnSet_ServoMotorParams(110, 70, 1);
}

/***** DC MOTORS *****/

// Motor 1
void vfnSet_DCMotor1_Duty_Perc(uint16_t u16Perc)
{
	vfnSet_Duty_Perc_Opwm(
			DCMOTOR1_CHANNEL,
			u16Perc,
			DCMOTORS_CHANNEL_COUNTER);
}

void vfnSet_DCMotor1_Back_Duty_Perc(uint16_t u16Perc)
{
	vfnSet_Duty_Perc_Opwm(
			DCMOTOR1BACK_CHANNEL,
			u16Perc,
			DCMOTORS_CHANNEL_COUNTER);
}

// Motor 2
void vfnSet_DCMotor2_Duty_Perc(uint16_t u16Perc)
{
	vfnSet_Duty_Perc_Opwm(
			DCMOTOR2_CHANNEL,
			u16Perc,
			DCMOTORS_CHANNEL_COUNTER);
}

void vfnSet_DCMotor2_Back_Duty_Perc(uint16_t u16Perc)
{
	vfnSet_Duty_Perc_Opwm(
			DCMOTOR2BACK_CHANNEL,
			u16Perc,
			DCMOTORS_CHANNEL_COUNTER);
}

/*
void vfnSet_DCMotorParams(uint8_t index,
						  int8_t maxDutyPerc,
						  int8_t minDutyPerc,
						  int8_t incDutyPerc)
{
	DCMotorParams[index].DCMotorMaxDutyPerc = maxDutyPerc;
	DCMotorParams[index].DCMotorMinDutyPerc = minDutyPerc;
	DCMotorParams[index].DCMotorIncDutyPerc = incDutyPerc;
}
*/

void Pit0ISR(void)
{
	uint8_t index;
	
	PIT.CH[0].TFLG.B.TIF = 1;
	
	for (index = 0; index < 2; index++)
	{
		DCMotorParams[index].DCMotorCurrentDutyPerc +=
			DCMotorParams[index].DCMotorIncDutyPerc;
		
		if (DCMotorParams[index].DCMotorCurrentDutyPerc > 
			DCMotorParams[index].DCMotorMaxDutyPerc)
		{
			DCMotorParams[index].DCMotorCurrentDutyPerc =
				DCMotorParams[index].DCMotorMaxDutyPerc;
		}
		else if (DCMotorParams[index].DCMotorCurrentDutyPerc < 
				 DCMotorParams[index].DCMotorMinDutyPerc)
		{
			DCMotorParams[index].DCMotorCurrentDutyPerc =
				DCMotorParams[index].DCMotorMinDutyPerc;
		}
		
		if (index == DCMOTOR1_INDEX)
		{
			if (DCMotorParams[index].DCMotorCurrentDutyPerc >= 0)
			{
				vfnSet_DCMotor1_Duty_Perc((uint8_t)DCMotorParams[index].DCMotorCurrentDutyPerc);
				vfnSet_DCMotor1_Back_Duty_Perc(0);
			}
			else
			{
				vfnSet_DCMotor1_Duty_Perc(0);
				vfnSet_DCMotor1_Back_Duty_Perc((uint8_t)(DCMotorParams[index].DCMotorCurrentDutyPerc*(-1)));
			}
		}
		else
		{
			if (DCMotorParams[index].DCMotorCurrentDutyPerc >= 0)
			{
				vfnSet_DCMotor2_Duty_Perc((uint8_t)DCMotorParams[index].DCMotorCurrentDutyPerc);
				vfnSet_DCMotor2_Back_Duty_Perc(0);
			}
			else
			{
				vfnSet_DCMotor2_Duty_Perc(0);
				vfnSet_DCMotor2_Back_Duty_Perc((uint8_t)(DCMotorParams[index].DCMotorCurrentDutyPerc*(-1)));
			}
		}
	}
}

void Pit1ISR(void)
{
	/*
	PIT.CH[1].TFLG.B.TIF = 1;
	
	vfnSet_DCMotorParams(DCMOTOR1_INDEX, 50, 0, -1);
	vfnSet_DCMotorParams(DCMOTOR2_INDEX, 50, 0, -1);
	*/
}

/***** SERVO MOTOR *****/
void vfnSet_ServoMotor_Deg(uint16_t u16PositionDeg)
{
	vfnSet_Duty_Opwm(
		SERVOMOTOR_CHANNEL,
		(uint16_t)(SERVO_MIN_TIME + (u16PositionDeg * (SERVO_MAX_TIME - SERVO_MIN_TIME) / 180)));
}

/*
void vfnSet_ServoMotorParams(uint8_t maxDegree,
							 uint8_t minDegree,
							 int8_t incDegree)
{
	ServoCurrentDegree += incDegree;
	
	if (ServoCurrentDegree > maxDegree)
	{
		ServoCurrentDegree = maxDegree;
	}
	else if (ServoCurrentDegree < minDegree)
	{
		ServoCurrentDegree = minDegree;
	}
	
	vfnSet_ServoMotor_Deg(ServoCurrentDegree);
}
*/

void Pit2ISR(void)
{
	/*
	PIT.CH[2].TFLG.B.TIF = 1;
	*/
}
