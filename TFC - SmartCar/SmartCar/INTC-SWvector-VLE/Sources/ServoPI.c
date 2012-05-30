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
#include "ServoPI.h"

#if (SERVO_KP != SERVO_TP)

static uint8_t mServoPosition;
//static int16_t mServoIntegral;

void vfnInit_ServoPI(uint8_t initPostion)
{
	mServoPosition = initPostion;
	//mServoIntegral = 0;
}

uint8_t u8Clock_ServoPI(uint8_t inputPosition)
{
	int16_t error;
	int16_t corrP;
	//int16_t corrI;
	
	error = inputPosition - mServoPosition;
	
	//mServoIntegral = mServoIntegral + error; // error integration
	
	corrP = ((SERVO_KP * error) / SERVO_TP);
	//corrI = ((SERVO_KI * mServoIntegral) / SERVO_TI);
	
	if ((corrP /*+ corrI*/))
	{
		mServoPosition = mServoPosition  + corrP /*+ corrI*/;
	}
	else
	{
		mServoPosition = inputPosition;
	}
	
	if (mServoPosition > SERVO_MAX_SATURATION)
	{
		mServoPosition = SERVO_MAX_SATURATION
	}
	else if (mServoPosition < SERVO_MIN_SATURATION)
	{
		mServoPosition = SERVO_MIN_SATURATION;
	}

	return mServoPosition;
}

#endif // (SERVO_KP != SERVO_TP)
