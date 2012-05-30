/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#include "MPC5604B_M27V.h"
#include "DCMotorsPI.h"

#if (MOTOR_KP != MOTOR_TP)

static int16_t mMotor1Velocity;
//static int16_t mMotor1Integral;
static int16_t mMotor2Velocity;
//static int16_t mMotor2Integral;

void vfnInit_Motor1PI(int16_t initVelocity)
{
	mMotor1Velocity = initVelocity;
	//mMotor1Integral = 0;
}

int16_t u8Clock_Motor1PI(int16_t inputVelocity)
{
	int16_t error;
	int16_t corrP;
	//int16_t corrI;
	
	error = inputVelocity - mMotor1Velocity;
	
	//mMotor1Integral = mMotor1Integral + error; // error integration
	
	corrP = ((MOTOR_KP * error) / MOTOR_TP);
	//corrI = ((MOTOR_KI * mMotor1Integral) / MOTOR_TI);
	
	if ((corrP /*+ corrI*/))
	{
		mMotor1Velocity = mMotor1Velocity  + corrP /*+ corrI*/;
	}
	else
	{
		mMotor1Velocity = inputVelocity;
	}
	
	if (mMotor1Velocity > MOTOR_MAX_SATURATION)
	{
		mMotor1Velocity = MOTOR_MAX_SATURATION;
	}
	else if (mMotor1Velocity < MOTOR_MIN_SATURATION)
	{
		mMotor1Velocity = MOTOR_MIN_SATURATION;
	}

	return mMotor1Velocity;
}

void vfnInit_Motor2PI(int16_t initVelocity)
{
	mMotor2Velocity = initVelocity;
	//mMotor2Integral = 0;
}

int16_t u8Clock_Motor2PI(int16_t inputVelocity)
{
	int16_t error;
	int16_t corrP;
	//int16_t corrI;
	
	error = inputVelocity - mMotor2Velocity;
	
	//mMotor2Integral = mMotor2Integral + error; // error integration
	
	corrP = ((MOTOR_KP * error) / MOTOR_TP);
	//corrI = ((MOTOR_KI * mMotor2Integral) / MOTOR_TI);
	
	if ((corrP /*+ corrI*/))
	{
		mMotor2Velocity = mMotor2Velocity  + corrP /*+ corrI*/;
	}
	else
	{
		mMotor2Velocity = inputVelocity;
	}
	
	if (mMotor2Velocity > MOTOR_MAX_SATURATION)
	{
		mMotor2Velocity = MOTOR_MAX_SATURATION;
	}
	else if (mMotor2Velocity < MOTOR_MIN_SATURATION)
	{
		mMotor2Velocity = MOTOR_MIN_SATURATION;
	}

	return mMotor2Velocity;
}

#endif // (MOTOR_KP != MOTOR_TP)
