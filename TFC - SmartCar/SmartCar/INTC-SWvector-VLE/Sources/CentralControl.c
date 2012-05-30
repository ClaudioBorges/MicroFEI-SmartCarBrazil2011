/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#include "MPC5604B_0M27V_0102.h"
#include "arctg.h"
#include "CentralControl.h"

static uint8_t processBlackCenters(int16_t *pBlackCenters, uint16_t linesRead);

#if (END_OF_RACE_DETECTION == 1)
// Determina a quantidade mínima de linhas com 3 faixas
// pretas para poder detectar início/fim de volta
// Caso a quantidade de linhas for inferior à esse valor
// o início/fim de volta não é detectado para essa amostra
#define MIN_SAMPLES_TO_DETECT_END		2

/*
	~0x18           ~0x37           ~0x55
	  |---------------|---------------|
					 ---
					 ---
	-----            ---            -----
	-----            ---            -----	
	-----            ---            -----	
	-----            ---            -----
					 ---
					 ---
					 ---
*/

// Determina o limite de deslocamento de cada faixa
// em relação aos seus reais centros
#define ERR					8

// Determina os limites máximos e mínimos que cada
// faixa poderá estar situada para ser detectado
// fim de volta
#define CENTER_LEFT_MIN		(CENTRAL_POSITION - 28 - ERR)
#define CENTER_LEFT_MAX		(CENTRAL_POSITION - 28 + ERR)

#define CENTER_MIDDLE_MIN	(CENTRAL_POSITION - ERR)
#define CENTER_MIDDLE_MAX	(CENTRAL_POSITION + ERR)

#define CENTER_RIGHT_MIN	(CENTRAL_POSITION + 28 - ERR)
#define CENTER_RIGHT_MAX	(CENTRAL_POSITION + 28 + ERR)

// Contagem feita para deixar que as 3 faixas pretas
// detectadas saiam da tela antes de detectar novo
// início/fim de volta
#define DELAY_AFTER_DETECT_LAP			200

// Contagem feita para incrementar o contador de voltas
// Usado para quando o contador atingir este valor fazer
// com que os motores parem o mais rápido possível
#define DELAY_TO_DETECT_LAP				15

#if 1
#define TurnOnDetectEndLed()	LED1 = LED_ON
#define TurnOffDetectEndLed()	LED1 = LED_OFF
#else
#define TurnOnDetectEndLed()
#define TurnOffDetectEndLed()
#endif

int8_t numberOfCurrLap = 0;
static uint16_t waitingCount = 0;
#endif // (END_OF_RACE_DETECTION == 1)

int8_t i8Calc_Servo_Position(
	uint8_t *pServoPos, 
	int16_t *pLineImage,
	uint16_t linesRead)
{
	uint8_t servoPos;

	// Run algorithms to calculate the servo position from frame
	servoPos = processBlackCenters(pLineImage, linesRead);

	if (servoPos == 0)
	{
		// Invalid frame
		
		return -1;
	}

	// Valid Frame

	*pServoPos = servoPos;
	
	return 0;
}

int8_t i8Calc_Motors_Full_Velocity(
	int16_t *pMotorLVel, 
	int16_t *pMotorRVel, 
	uint8_t servoPos)
{
	int16_t motorLVel;
	int16_t motorRVel;
	int16_t outsideVel;
	int16_t insideVel;
	int16_t diff;
	
	if (servoPos > CENTRAL_SERVO_POSITION)
	{
		diff = servoPos - CENTRAL_SERVO_POSITION;
	}
	else
	{
		diff = CENTRAL_SERVO_POSITION - servoPos;
	}
	
	outsideVel = 
		(uint16_t)MAX_MOTOR_VELOCITY 
		- ((diff * (MAX_MOTOR_VELOCITY - MIN_OUTSIDE_MOTOR_VEL)) 
			/ (MAX_SERVO_POSITION - CENTRAL_SERVO_POSITION));
			
	insideVel = 
		(uint16_t)MAX_MOTOR_VELOCITY 
		- ((diff * (MAX_MOTOR_VELOCITY - MIN_INSIDE_MOTOR_VEL)) 
			/ (MAX_SERVO_POSITION - CENTRAL_SERVO_POSITION));
			
	/*
	if (outsideVel > MAX_MOTOR_SATURATION)
	{
		outsideVel = MAX_MOTOR_SATURATION;
	}
	else if (outsideVel < MIN_OUTSIDE_MOTOR_SAT)
	{
		outsideVel = MIN_OUTSIDE_MOTOR_SAT;
	}
	
	if (insideVel > MAX_MOTOR_SATURATION)
	{
		insideVel = MAX_MOTOR_SATURATION;
	}
	else if (insideVel < MIN_INSIDE_MOTOR_SAT)
	{
		insideVel = MIN_INSIDE_MOTOR_SAT;
	}
	*/
	
	if (servoPos > CENTRAL_SERVO_POSITION)
	{
		motorLVel = outsideVel;
		motorRVel = insideVel;
	}
	else if (servoPos < CENTRAL_SERVO_POSITION)
	{
		motorLVel = insideVel;
		motorRVel = outsideVel;
	}
	else // if (servoPos == CENTRAL_SERVO_POSITION)
	{
		motorLVel = outsideVel;
		motorRVel = outsideVel;
	}
	
	*pMotorLVel = motorLVel;
	*pMotorRVel = motorRVel;
	
	return 0;
}

int8_t i8Calc_Motors_Low_Velocity(
		int16_t *pMotorLVel,
		int16_t *pMotorRVel,
		uint8_t servoPos)
{
	uint8_t motorLVel;
	uint8_t motorRVel;

	if (servoPos > CENTRAL_SERVO_POSITION)
	{
		motorLVel = MIN_OUTSIDE_MOTOR_VEL;
		motorRVel = MIN_INSIDE_MOTOR_VEL;
	}
	else if (servoPos < CENTRAL_SERVO_POSITION)
	{
		motorLVel = MIN_INSIDE_MOTOR_VEL;
		motorRVel = MIN_OUTSIDE_MOTOR_VEL;
	}
	else // if (servoPos == CENTRAL_SERVO_POSITION)
	{
		motorLVel = MIN_OUTSIDE_MOTOR_VEL;
		motorRVel = MIN_OUTSIDE_MOTOR_VEL;
	}

	*pMotorLVel = motorLVel;
	*pMotorRVel = motorRVel;

	return 0;
}

// Position algorithm

/*
// [ALGOR]
static int8_t avgDegree;
static int8_t derDegree;
static int8_t myPositionDegree;
// [\ALGOR]
*/

static uint8_t processBlackCenters(int16_t *pBlackCenters, uint16_t linesRead)
{
	uint8_t index;
	uint8_t lastValidIndex;
	int16_t lastValidValue;
	int16_t currCenterValue;
	
	// [Average]
	int32_t avgSum;
	int32_t avgNumLines;
	int32_t average;
	// [\Average]
	
	// [Derivative]
	int32_t derSumX;
	int32_t derSumY;
	// [\Derivative]
	
	#if (END_OF_RACE_DETECTION == 1)
	if (!waitingCount)
	{
		if (my3CurrentSample >= MIN_SAMPLES_TO_DETECT_END)
		{
			uint8_t sampleIndex;
			uint8_t index;
			
			for (sampleIndex = 0, index = 0; sampleIndex < (MIN_SAMPLES_TO_DETECT_END - 1); sampleIndex++, index += 4)
			{
				// Valida faixa da esquerda
				currCenterValue = my3CentersMatrix[index + 1];
				if (currCenterValue < CENTER_LEFT_MIN || currCenterValue > CENTER_LEFT_MAX)
					break;
					
				// Valida faixa do meio
				currCenterValue = my3CentersMatrix[index + 2];
				if (currCenterValue < CENTER_MIDDLE_MIN || currCenterValue > CENTER_MIDDLE_MAX)
					break;
					
				// Valida faixa da direita
				currCenterValue = my3CentersMatrix[index + 3];
				if (currCenterValue < CENTER_RIGHT_MIN || currCenterValue > CENTER_RIGHT_MAX)
					break;
			}
			
			if (sampleIndex == (MIN_SAMPLES_TO_DETECT_END - 1))
			{
				// Validou as condições, fim de volta detectado
				waitingCount = 1;
				TurnOnDetectEndLed();
			}
		}
	}
	else
	{
		// Contador está rolando
		if (waitingCount < 0xffff)
		{
			waitingCount++;
		}
		
		if (waitingCount == DELAY_TO_DETECT_LAP)
		{
			numberOfCurrLap++;
		}
		else if (waitingCount >= DELAY_AFTER_DETECT_LAP)
		{
			// Contador estourou, estou apto a detectar novo ínicio/fim da volta
			waitingCount = 0;
			TurnOffDetectEndLed();
			
			#if 1
			// [DEBUG]
			// Apenas para o carrinho continuar rodando após o delay
			if (numberOfCurrLap >= 3)
			{
				numberOfCurrLap = 1;
			}
			// [\DEBUG]
			#endif // 1
		}
	}
	#endif // (END_OF_RACE_DETECTION == 1)
	
	// Check minimum valid lines
	if (linesRead < MIN_LINES_TO_CALC_DEGREE)
	{
		return 0;
	}
	
	lastValidIndex = 0xff;
	
	// [Derivative]
	derSumX = 0;
	derSumY = 0;
	// [\Derivative]
	
	// [Average]
	avgSum = 0;
	avgNumLines = 0;
	//[\Average]
	
	for (index = 0; index < NUMBER_OF_LINES; index++)
	{
		currCenterValue = pBlackCenters[index];
		
		if (currCenterValue > 0)
		{
			if (lastValidIndex != 0xff)
			{
				int16_t dx;
				int16_t dy;
				int16_t maxAccepted;
				
				dx = (currCenterValue - lastValidValue);
				dy = (index - lastValidIndex);
				
				maxAccepted = (dy * MAX_ACCEPTED_DERIVATIVE);
				
				if (dx <= maxAccepted && dx >= (-maxAccepted))
				{
					// Valid line detected
					
					lastValidIndex = index;
					lastValidValue = currCenterValue;
					
					// [Average]
					#if (GAIN_AVERAGE != 0)
					avgSum += currCenterValue;
					#endif // (GAIN_AVERAGE != 0)
					avgNumLines++;
					// [\Average]
					
					// [Derivative]
					derSumX += dx;
					derSumY += dy;
					// [\Derivative]
				}
			}
			else
			{
				// First valid line detected
				
				lastValidIndex = index;
				lastValidValue = currCenterValue;
				
				// [Average]
				#if (GAIN_AVERAGE != 0)
				avgSum += currCenterValue;
				#endif // (GAIN_AVERAGE != 0)
				avgNumLines++;
				// [\Average]
			}
		}
		else
		{
			if (lastValidIndex != 0xff)
			{
				uint8_t invalidCount;
				
				invalidCount = index - lastValidIndex;
				
				if (invalidCount > MAX_LINES_GAP)
					break;
					
				/*
				if ((invalidCount > MAX_LINES_GAP_ON_BORDER)
						&& ((lastValidValue < BORDER) || (lastValidValue > (MAX_POSITION - BORDER))))
					break;
				*/
			}
		}
	}
	
	// Check minimum valid lines
	if (avgNumLines >= MIN_LINES_TO_CALC_DEGREE)
	{
		// [CUIDADO]
		// Quando a verificação (avgNumLines >= MIN_LINES_TO_CALC_DEGREE) está presente
		// e MIN_LINES_TO_CALC_DEGREE é maior do que 2, não é necessário verificar se
		// os denominadores são diferentes de 0, então se ela for removida é necessário
		// verificar os denominadores!!!
		// Quando avgNumLines >= 2 ==>> lastValidIndex >= 1 e derSumY >= 1
		// [\CUIDADO]
		
		int8_t avgDegree;
		int8_t derDegree;
		int8_t myPositionDegree;

		#if (GAIN_MY_POSITION != 0)
		myPositionDegree = getDeg(
			(int8_t)(lastValidValue - CENTRAL_POSITION),
			getIndexFromDeriv((int8_t)(lastValidValue - CENTRAL_POSITION), lastValidIndex));
		#endif // (GAIN_MY_POSITION != 0)
		
		#if (GAIN_AVERAGE != 0)
		average = (avgSum/avgNumLines);
		
		avgDegree = getDeg(
			(int8_t)(average - CENTRAL_POSITION),
			getIndexFromDeriv((int8_t)(average - CENTRAL_POSITION), avgNumLines));
		#endif // (GAIN_AVERAGE != 0)
		
		#if (GAIN_DERIVATIVE != 0)
		derDegree = getDeg(
			derSumX,
			getIndexFromDeriv(derSumX, derSumY));
		#endif // (GAIN_DERIVATIVE != 0)
		
		{
			int16_t finalDegree;
			
			finalDegree = (((
				#if (GAIN_AVERAGE != 0)
				(GAIN_AVERAGE * avgDegree) +
				#endif // (GAIN_AVERAGE != 0)
				
				#if (GAIN_DERIVATIVE != 0)
				(GAIN_DERIVATIVE * derDegree) +
				#else // (GAIN_DERIVATIVE != 0)
				0 +
				#endif (GAIN_DERIVATIVE != 0)
				
				#if (GAIN_MY_POSITION != 0)
				(GAIN_MY_POSITION * myPositionDegree)
				#else // (GAIN_MY_POSITION != 0)
				0
				#endif // (GAIN_MY_POSITION != 0)
				) / (GAIN_AVERAGE + GAIN_DERIVATIVE + GAIN_MY_POSITION))
				#if (GAIN_FINAL != ATT_FINAL)
				* GAIN_FINAL) / ATT_FINAL;
				#else // (GAIN_FINAL != ATT_FINAL)
				);
				#endif // (GAIN_FINAL != ATT_FINAL)
				
			//finalDegree = (finalDegree * (MAX_SERVO_POSITION - CENTRAL_SERVO_POSITION)) / MAX_WHEEL_DEGREE;
			finalDegree = (CENTRAL_SERVO_POSITION - finalDegree);
			
			// Saturation
			if (finalDegree > MAX_SERVO_POSITION)
			{
				finalDegree = MAX_SERVO_POSITION;
			}
			else if (finalDegree < MIN_SERVO_POSITION)
			{
				finalDegree = MIN_SERVO_POSITION;
			}
			
			return (uint8_t)finalDegree;
		}
	}
	else
	{
		return 0;
	}
}
