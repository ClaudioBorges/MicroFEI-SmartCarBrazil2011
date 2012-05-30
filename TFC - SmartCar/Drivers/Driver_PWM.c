/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#include "MPC5604B_0M27V_0102.h" /* Use proper include file */
#include "Driver_EMIOS.h"
#include "Driver_MPC5604B.h"

/*************************************************************/
/* Definitions */
#define SERVO_CHANNEL    1
#define MOTOR_CHANNEL    19

#define MIN_SERVO		 480
#define MAX_SERVO		 2480

#define MIN_SERVO_SMART  1080
#define MAX_SERVO_SMART  1880
/*************************************************************/

void vfnSet_Motor(uint16_t u16Perc)
{
		if(u16Perc < 49)
		{
				vfnSet_Duty_Opwm(2,20000);
				vfnSet_Duty_Opwm(10,0);
				vfnSet_Duty_Perc_Opwm(MOTOR_CHANNEL,((50-u16Perc)*2), 16); 
		}
		if(u16Perc > 51)
		{
				vfnSet_Duty_Opwm(2,0);
				vfnSet_Duty_Opwm(10,20000);
				vfnSet_Duty_Perc_Opwm(MOTOR_CHANNEL,((u16Perc-50)*2), 16); 
		}
		if(u16Perc > 30 && u16Perc < 70)
		{
				vfnSet_Duty_Opwm(2,0);
				vfnSet_Duty_Opwm(10,0);
				vfnSet_Duty_Perc_Opwm(MOTOR_CHANNEL,0,16); 
		}

}

void vfnSet_Servo_Range(uint16_t u16Value, uint16_t u16Min, uint16_t u16Max)  /* values between min and max*/
{   
	uint16_t u16Duty;      
	u16Duty = MIN_SERVO_SMART + ((u16Value - u16Min) * (MAX_SERVO_SMART - MIN_SERVO_SMART) / (u16Max - u16Min)); /* 0% of servo is 480. 100% of servo is 2480 */
	vfnSet_Duty_Opwm(SERVO_CHANNEL,u16Duty); 
}

void vfnSet_Servo_Deg(uint16_t u16PositionDeg)  /* values between 0 and 180*/
{   
	uint16_t u16Duty;      
	u16Duty = (uint16_t)(u16PositionDeg * 1111 / 100 + 480); /* 0% of servo is 480. 100% of servo is 2480 */
	vfnSet_Duty_Opwm(SERVO_CHANNEL,u16Duty); 
}

void vfnInit_Pwm(void)
{
	int x=0;
	vfnInit_Emios_0();     				    		/* Sets Emios0 on*/
  	     					
// 	vfnInit_Emios_0_Mcb(8,4); 					/* Set channel 8 as MCB  */	
// 	vfnInit_Emios_0_Opwm(9,EMIOS_0_9,0,2);		/* Set channel 3 as OPWM */ 
//	vfnInit_Emios_0_Opwm(11,EMIOS_0_11,2,4);		/* Set channel 3 as OPWM */ 
//  	
	vfnInit_Emios_0_Mcb(16,4000); 					/* Set channel 16 as MCB  */
	vfnInit_Emios_0_Mcb(8,4); 						/* Set channel 8 as MCB  */	
	vfnInit_Emios_0_Mcb(0,20000); 					/* Set channel 8 as MCB  */		//SI
	vfnInit_Emios_0_Mcb(23,0xFFFFFF);				/* Set channel 23 as MCB  */		//SI
//	vfnInit_Emios_0_Opwm(17,EMIOS_0_17,0,2);		/* Set channel 17 as OPWM */
//	vfnInit_Emios_0_Opwm(18,EMIOS_0_18,10,24);		/* Set channel 18 as OPWM motor*/
	//vfnInit_Emios_0_Opwm(19,EMIOS_0_19,0,1000);		/* Set channel 19 as OPWM motor*/ 	
//  vfnInit_Emios_0_Opwm(11,EMIOS_0_11,2,4);		/* Set channel 3 as OPWM */ 	//ck'
//  vfnInit_Emios_0_Opwm(9,EMIOS_0_9,0,2);			/* Set channel 3 as OPWM */ 		//ck	
//  vfnInit_Emios_0_Opwm(7,EMIOS_0_7,2,4);			/* Set channevl 3 as OPWM */        //SI
  	
  	
  	//vfnInit_Emios_0_Opwm(1,EMIOS_0_1,0,1500);		/* Set channel 1 as OPWM */ 	//servo
  	vfnInit_Emios_0_Opwm(2,EMIOS_0_2,0,20000);		/* Set channel 2 as OPWM */ 	//in
  	//vfnInit_Emios_0_Opwm(10,EMIOS_0_10,0,20000);	/* Set channel 10 as OPWM */ 	//in
  	
  				
}


