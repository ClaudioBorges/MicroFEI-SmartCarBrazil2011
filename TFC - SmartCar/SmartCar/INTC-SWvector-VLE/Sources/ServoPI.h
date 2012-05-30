/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __SERVO_PI_H__
#define __SERVO_PI_H__

// PI control:
// SAÍDA = SAÍDA + ((Kp * ERRO) / Tp) + ((Ki * INTEGRAL) / Ti)

//#warning "[TODO] to adjust these constants below."
#define SERVO_KP	1
#define SERVO_TP	1
/*
#define SERVO_KI	0
#define SERVO_TI	1
*/
// note: when these constants are increased, the response becomes to be slower

#define SERVO_MAX_SATURATION	(90+27)
#define SERVO_MIN_SATURATION	(90-27)

#if (SERVO_KP != SERVO_TP)

void vfnInit_ServoPI(uint8_t initPostion);
uint8_t u8Clock_ServoPI(uint8_t inputPosition);

#else // (SERVO_KP != SERVO_TP)

#define vfnInit_ServoPI(initPostion)
#define u8Clock_ServoPI(inputPosition) (inputPosition)

#endif // (SERVO_KP != SERVO_TP)

#endif // __SERVO_PI_H__
