/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

/*********************
 * Variables
 *********************/
// index = tg(ang) * 100
const unsigned char arctg[] = {
	0,  1,  1,  2,  2,  3,  4,  4,  5,  5,  6,  6,  7,  7,  8,  9,  9,  10, 10, 11,		/*0  - 19*/
	11, 12, 12, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21,		/*20 - 39*/
	22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 27, 28, 28, 29, 29, 30, 30, 31,		/*40 - 59*/
	31, 31, 32, 32, 33, 33, 33, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 38, 38, 38,		/*60 - 79*/
	39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 44, 44, 45,		/*80 - 99*/
	45 };																				/*100*/
