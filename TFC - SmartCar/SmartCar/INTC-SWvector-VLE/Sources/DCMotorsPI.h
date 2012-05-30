/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __DC_MOTORS_PI_H__
#define __DC_MOTORS_PI_H__

// PI control:
// SAÍDA = SAÍDA + ((Kp * ERRO) / Tp) + ((Ki * INTEGRAL) / Ti)

//#warning "[TODO] to adjust these constants below."
#define MOTOR_KP	1
#define MOTOR_TP	1
/*
#define MOTOR_KI	0
#define MOTOR_TI	1
*/
// note: when these constants are increased, the response becomes to be slower

#define MOTOR_MAX_SATURATION	100
#define MOTOR_MIN_SATURATION	0

#if (MOTOR_KP != MOTOR_TP)

void vfnInit_Motor1PI(int16_t initVelocity);
int16_t u8Clock_Motor1PI(int16_t inputVelocity);
void vfnInit_Motor2PI(int16_t initVelocity);
int16_t u8Clock_Motor2PI(int16_t inputVelocity);

#else // (MOTOR_KP != MOTOR_TP)

#define vfnInit_Motor1PI(initVelocity)
#define u8Clock_Motor1PI(inputVelocity) (inputVelocity)
#define vfnInit_Motor2PI(initVelocity)
#define u8Clock_Motor2PI(inputVelocity) (inputVelocity)

#endif // (MOTOR_KP != MOTOR_TP)

#endif // __DC_MOTORS_PI_H__
