/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __INTC_H__
#define __INTC_H__

/*
 *		Function Prototypes
 */
asm void initIrqVectors(void);
void initINTC(void);
void enableIrq(void);

#endif // __INTC_H__