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
 *	Settings
 */

//#define ENABLE_UART
#define UART_TRANSMIT_BLACK_CENTERS
//#define UART_TRANSMIT_3_BLACK_CENTERS
//#define UART_TRANSMIT_NUMBER_OF_LINES
#define ENABLE_UART_DELAY
#define UART_DELAY_MS		2

/*
 *	Includes
 */

#include "MPC5604B_0M27V_0102.h"
#include "HardwareTRK-MPC5604B.h"
#include "Setup.h"
#include "INTC.h"
#include "uart.h"
#include "Driver_NTSC.h"
#include "ServoPI.h"
#include "DCMotorsPI.h"
#include "CentralControl.h"

/*
 *	Private definitions
 */

// General control
#define MAX_INV_FRAMES_TO_STOP	(3 * 60) // ~3 seconds
#define MAX_INV_FRAMES_TO_CORR	10

// Cumulative position correction
#define CUM_POS_MUL 1
#define CUM_POS_DIV	10

/*
 *	Private prototypes
 */

void vfnError(void);

/*
 *	Functions
 */

#ifdef ENABLE_UART
/*	1000ms		--		SYSTEM_CLOCK
	timeInMs 	--		IncCount */
#define STMGetInIncFromMs(timeInMs)	((SYSTEM_CLOCK/1000ul)*timeInMs)

void initSTM(void)
{
	STM.CR.B.TEN = 0;	// Global off
	
	STM.CR.B.FRZ = 0;	// Continue in Debug
	STM.CR.B.CPS = 0;	// Prescale (/1)
	//STM.CNT.R = 0x00000000;	// CNT value
	
	STM.CR.B.TEN = 1;	// Global on
}

// [UART]
uint8_t startFrameDelimiter[] = {0x80};
uint8_t endFrameDelimiter[] = {0x80};

uint16_t UARTSend = 0;
#define UART_SEND_FREQUENCY 1
// [\UART]
//uint32_t diff;
#endif // ENABLE_UART

void main (void)
{
	uint8_t servoPos = CENTRAL_SERVO_POSITION;
	uint8_t lastServoPos = CENTRAL_SERVO_POSITION;
	uint8_t cumulativeDir = CENTRAL_SERVO_POSITION;
	int16_t motorLVel = 0;
	int16_t motorRVel = 0;
	int16_t lastMotorLVel = 0;
	int16_t lastMotorRVel = 0;
	uint16_t err = 0;
	uint16_t numberOfLines = 0;
	
	// Clock initialization
	vfnInit_Clock();
	
	// Drivers and peripherals initialization
	vfnInit_Emios_0();
	vfnInit_Motors();
	initNTSC();
	#ifdef ENABLE_UART
	initLINFlex_0_UART();
	#ifdef ENABLE_UART_DELAY
	initSTM();
	#endif // ENABLE_UART_DELAY
	#endif // ENABLE_UART
	initLEDs();
	
	// Software initialization
	vfnInit_ServoPI(CENTRAL_SERVO_POSITION);
	vfnInit_Motor1PI(0);
	vfnInit_Motor2PI(0);
	
	// Initial state
	vfnSet_ServoMotor_Deg(CENTRAL_SERVO_POSITION);
	vfnSet_DCMotor1_Duty_Perc(0);
	vfnSet_DCMotor1_Back_Duty_Perc(0);
	vfnSet_DCMotor2_Duty_Perc(0);
	vfnSet_DCMotor2_Back_Duty_Perc(0);
	
	// Interrupts initialization
	initIrqVectors();	/* Initialize exceptions: only need to load IVPR */
	initINTC();			/* Initialize INTC for software vector mode */
	enableIrq();	   	/* Ensure INTC current prority=0 & enable IRQ */
	
	while (1)
	{
		// [DEBUG]
		//LED3 ^= 1;
		// [\DEBUG]
		
		// Refresh Watch Dog Timer
		ClearWDT();
		
		#ifdef ENABLE_UART
		UARTDisableInts();
		#endif // ENABLE_UART
		
		// Captures a pre-processed frame
		numberOfLines = captureFrame();
		
		#ifdef ENABLE_UART
		UARTEnableInts();
		
		UARTSend++;

		if (IsUartFifoEmpty())
		{
			if (UARTSend >= UART_SEND_FREQUENCY)
			{
				//LED4 ^= 1;
				UARTSend = 0;
				
				UARTWrite((char *)startFrameDelimiter,
						  sizeof(startFrameDelimiter)/sizeof(startFrameDelimiter[0]));
				
				#ifdef UART_TRANSMIT_NUMBER_OF_LINES
				_UARTWrite((short int *)&numberOfLines, 1);
				#endif // UART_TRANSMIT_NUMBER_OF_LINES
				
				#ifdef UART_TRANSMIT_BLACK_CENTERS
				_UARTWrite((short int *)myCentersMatrix, NUMBER_OF_LINES);
				#endif // UART_TRANSMIT_BLACK_CENTERS
				
				#ifdef UART_TRANSMIT_3_BLACK_CENTERS				
				if (my3CurrentSample)
				{
					UARTWrite((char *)startFrameDelimiter,
						  sizeof(startFrameDelimiter)/sizeof(startFrameDelimiter[0]));
						 
					_UARTWrite((short int *)my3CentersMatrix, (my3CurrentSample * 4));
					_UARTWrite((short int *)&my3CurrentSample, 1);
				}
				#endif // UART_TRANSMIT_3_BLACK_CENTERS
				
				/*
				UARTWrite((char *)endFrameDelimiter,
						  sizeof(endFrameDelimiter)/sizeof(endFrameDelimiter[0]));
				*/
			}
		}
		#ifdef ENABLE_UART_DELAY
		else
		{
			STM.CNT.R = 0;
			
			// Delay 5ms to transmit UART frame
			while (STM.CNT.R <= STMGetInIncFromMs(UART_DELAY_MS));
		}
		#endif // ENABLE_UART_DELAY
		#endif // ENABLE_UART

		// Determines output values
		if (!i8Calc_Servo_Position(&servoPos, myCentersMatrix, numberOfLines))
		{
			// Valid servo position
			
			// [DEBUG]
			//LED1 = LED_OFF;
			//LED2 = LED_OFF;
			//LED3 = LED_OFF;
			//LED4 = LED_OFF;
			LED1 = LED_ON;
			// [\DEBUG]
			
			i8Calc_Motors_Full_Velocity(&motorLVel, &motorRVel, servoPos);
			
			err = 0;
		}
		else
		{
			// Invalid servo position
			
			if (err > MAX_INV_FRAMES_TO_STOP)
			{
				// Stop
				
				// [DEBUG]
				//LED3 = LED_ON;
				// [\DEBUG]
				
				servoPos = CENTRAL_SERVO_POSITION;
				
				motorLVel = motorRVel = 0;
			}
			else if (err > MAX_INV_FRAMES_TO_CORR)
			{
				// Tries to catch the line
				
				// [DEBUG]
				//LED2 = LED_ON;
				// [\DEBUG]
				
				if (cumulativeDir > (CENTRAL_SERVO_POSITION + 0))
				{
					servoPos = MAX_SERVO_POSITION;
				}
				else if (cumulativeDir < (CENTRAL_SERVO_POSITION - 0))
				{
					servoPos = MIN_SERVO_POSITION;
				}
				else
				{
					servoPos = CENTRAL_SERVO_POSITION;
					//servoPos = cumulativeDir;
				}
				
				i8Calc_Motors_Low_Velocity(&motorLVel, &motorRVel, servoPos);
				
				err++;
			}
			else
			{
				// Continues with last stored values
				
				// [DEBUG]
				//LED1 = LED_ON;
				LED1 = LED_OFF;
				// [\DEBUG]
				
				servoPos = lastServoPos;
				
				motorLVel = lastMotorLVel;
				motorRVel = lastMotorRVel;
				
				err++;
			}
		}
		
		// Calculate cumulative car direction
		cumulativeDir = 
			(((uint16_t)CUM_POS_MUL * servoPos) + ((CUM_POS_DIV - CUM_POS_MUL) * cumulativeDir)) 
			/ CUM_POS_DIV;
			
		// Store current values
		lastServoPos = servoPos;
		lastMotorLVel = motorLVel;
		lastMotorRVel = motorRVel;
		
		// Servo
		vfnSet_ServoMotor_Deg(u8Clock_ServoPI(servoPos));
		
		#if (END_OF_RACE_DETECTION == 1)
		if (numberOfCurrLap >= 3)
		{
			// DC motors
			vfnSet_DCMotor1_Duty_Perc(u8Clock_Motor1PI(0));
			//vfnSet_DCMotor1_Back_Duty_Perc(0);
			vfnSet_DCMotor2_Duty_Perc(u8Clock_Motor2PI(0));
			//vfnSet_DCMotor2_Back_Duty_Perc(0);
		}
		else
		#endif // (END_OF_RACE_DETECTION == 1)
		{
			// DC motors
			vfnSet_DCMotor1_Duty_Perc(u8Clock_Motor1PI(motorLVel));
			//vfnSet_DCMotor1_Back_Duty_Perc(0);
			vfnSet_DCMotor2_Duty_Perc(u8Clock_Motor2PI(motorRVel));
			//vfnSet_DCMotor2_Back_Duty_Perc(0);
		}
		
		// [DEBUG]
		{
			int16_t carVel;
			
			carVel = motorLVel + motorRVel;
			
			if ( carVel > (((2 * (MAX_MOTOR_VELOCITY - MIN_OUTSIDE_MOTOR_VEL)) / 3) + (2 * MIN_OUTSIDE_MOTOR_VEL)) )
			{
				LED2 = LED_ON;
			}
			else
			{
				LED2 = LED_OFF;
			}
			
			if ( carVel > ((2 * (MAX_MOTOR_VELOCITY - MIN_OUTSIDE_MOTOR_VEL)) / 2) + (2 *MIN_OUTSIDE_MOTOR_VEL) )
			{
				LED3 = LED_ON;
			}
			else
			{
				LED3 = LED_OFF;
			}
			
			if ( carVel >= (2 * MAX_MOTOR_VELOCITY) )
			{
				LED4 = LED_ON;
			}
			else
			{
				LED4 = LED_OFF;
			}
		}
		// [\DEBUG]
	}
}

void vfnError(void)
{
	// [DEBUG]
	uint32_t j;
    
   	vfnSet_DCMotor1_Duty_Perc(0);
	vfnSet_DCMotor1_Back_Duty_Perc(0);
	vfnSet_DCMotor2_Duty_Perc(0);
	vfnSet_DCMotor2_Back_Duty_Perc(0);
	
	while (1)
	{
		for (j = 0; j < 0xfffff; j++) {}
		
		//LED1 ^= 1;
	}
	// [\DEBUG]
}
