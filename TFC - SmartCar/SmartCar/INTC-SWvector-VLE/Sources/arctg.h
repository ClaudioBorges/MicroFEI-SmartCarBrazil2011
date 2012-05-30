/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef __ARCTG_H__
#define __ARCTG_H__

/*********************
 * Externs
 *********************/
 extern const unsigned char arctg[];
 
/*********************
 * Defines
 *********************/
#define MULT_CTE		100//81//69
 
#define MAX_INDEX		100		//45 graus das rodas
#define getIndexFromDeriv(x, y)		((x > 0) ? ((MULT_CTE * x) / (y)) : ((MULT_CTE * (-x)) / (y))) //
#define getDeg(x, index)			((x > 0) ? ((index > MAX_INDEX) ? arctg[MAX_INDEX] : arctg[index]) : ((index > MAX_INDEX) ? (-arctg[MAX_INDEX]) : (-arctg[index])))

#endif // __ARCTG_H__
