/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

/* Function Prototypes */
/** Sets the Servo motor */
void vfnSet_Servo_Deg(uint16_t u16PositionDeg);
vfnSet_Servo_Range(uint16_t u16Value, uint16_t u16Min, uint16_t u16Max);
/** Set the motor  */
void vfnSet_Motor(uint16_t u16Perc);

/** Initialization of the PWM and MCB module */
void vfnInit_Pwm(void);
