/* IntcIsrVectors.c - table of ISRs for INTC in SW vector Mode */
/* Description:  Contains addresses for 310 ISR vectors */
/*			     Table address gets loaded to INTC_IACKR */
/*               Alignment: MPC551x: 2 KB after a 4KB boundary; MPC555x: 64 KB*/
/* April 22, 2004 S. Mihalik */ 
/* March 16, 2006 S. Mihalik - Modified for compile with Diab 5.3 */
/* Jun 29 2006 SM - Used pragma align instead of hard coding address */
/* Jul  5 2007 SM - alignment now done in link file; changes for MPC551x */
/* Aug 30 2007 SM - Added pragma for CodeWarrior */
/* Oct 22 2008 SM - Changed to use PIT1 ISR instead of eMIOS Ch 0 ISR */

#include "typedefs.h"

void interrupt_handler(void);

extern void Pit0ISR(void);
extern void Pit1ISR(void);
extern void Pit2ISR(void);
extern void Pit3ISR(void);
extern void Pit4ISR(void);
extern void Pit5ISR(void);

extern void int_icCompSync(void);
extern void int_icVertPulse(void);
extern void int_icBurstGate(void);

extern void LINFlex_TXI(void);

/* Use next two lines with Diab compile */
/*#pragma section CONST ".intc_sw_isr_vector_table" */		 /* Diab compiler pragma */
/*const uint32_t IntcIsrVectorTable[] = {   */ 

/* Use pragma next two lines with CodeWarrior compile */
#pragma section data_type ".intc_sw_isr_vector_table" ".intc_sw_isr_vector_table" data_mode=far_abs  
uint32_t IntcIsrVectorTable[] = {
    (uint32_t)&interrupt_handler,    /* Vector - 0    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 1    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 2    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 3    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 4    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 5    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 6    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 7    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 8    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 9    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 10    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 11    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 12    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 13    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 14    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 15    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 16    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 17    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 18    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 19    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 20    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 21    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 22    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 23    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 24    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 25    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 26    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 27    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 28    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 29    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 30    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 31    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 32    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 33    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 34    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 35    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 36    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 37    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 38    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 39    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 40    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 41    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 42    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 43    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 44    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 45    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 46    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 47    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 48    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 49    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 50    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 51    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 52    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 53    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 54    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 55    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 56    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 57    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 58    Reserved */
    (uint32_t)&Pit0ISR,    /* Vector - 59    interrupt_handler*/
    (uint32_t)&Pit1ISR,    /* Vector - 60    interrupt_handler*/
    (uint32_t)&Pit2ISR,    /* Vector - 61    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 62    INT_ADC*/
    (uint32_t)&interrupt_handler,    /* Vector - 63    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 64    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 65    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 66    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 67    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 68    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 69    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 70    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 71    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 72    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 73    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 74    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 75    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 76    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 77    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 78    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 79    interrupt_handler*/
    (uint32_t)&LINFlex_TXI,    		 /* Vector - 80    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 81    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 82    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 83    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 84    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 85    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 86    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 87    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 88    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 89    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 90    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 91    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 92    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 93    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 94    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 95    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 96    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 97    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 98    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 99    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 100    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 101    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 102    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 103    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 104    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 105    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 106    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 107    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 108    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 109    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 110    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 111    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 112    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 113    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 114    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 115    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 116    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 117    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 118    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 119    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 120    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 121    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 122    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 123    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 124    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 125    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 126    Reserved */
    (uint32_t)&Pit3ISR,    /* Vector - 127    interrupt_handler*/
    (uint32_t)&Pit4ISR,    /* Vector - 128    interrupt_handler*/
    (uint32_t)&Pit5ISR,    /* Vector - 129    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 130    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 131    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 132    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 133    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 134    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 135    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 136    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 137    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 138    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 139    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 140    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 141    INT_EMIOS*/
    (uint32_t)&interrupt_handler,    /* Vector - 142    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 143    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 144    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 145    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 146    interrupt_handler*/
    (uint32_t)&int_icVertPulse,    /* Vector - 147    interrupt_handler*/
    (uint32_t)&int_icCompSync,     /* Vector - 148    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 149    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 150    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 151    interrupt_handler*/
    (uint32_t)&int_icBurstGate,    /* Vector - 152    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 153    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 154    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 155    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 156    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 157    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 158    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 159    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 160    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 161    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 162    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 163    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 164    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 165    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 166    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 167    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 168    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 169    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 170    interrupt_handler*/
    (uint32_t)&interrupt_handler,    /* Vector - 171    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 172    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 173    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 174    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 175    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 176    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 177    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 178    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 179    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 180    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 181    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 182    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 183    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 184    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 185    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 186    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 187    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 188    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 189    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 190    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 191    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 192    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 193    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 194    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 195    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 196    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 197    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 198    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 199    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 200    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 201    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 202    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 203    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 204    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 205    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 206    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 207    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 208    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 209    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 210    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 211    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 212    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 213    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 214    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 215    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 216    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 217    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 218    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 219    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 220    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 221    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 222    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 223    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 224    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 225    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 226    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 227    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 228    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 229    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 230    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 231    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 232    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 233    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 234    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 235    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 236    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 237    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 238    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 239    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 240    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 241    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 242    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 243    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 244    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 245    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 246    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 247    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 248    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 249    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 250    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 251    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 252    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 253    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 254    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 255    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 256    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 257    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 258    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 259    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 260    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 261    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 262    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 263    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 264    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 265    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 266    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 267    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 268    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 269    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 270    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 271    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 272    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 273    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 274    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 275    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 276    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 277    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 278    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 279    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 280    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 281    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 282    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 283    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 284    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 285    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 286    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 287    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 288    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 289    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 290    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 291    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 292    Reserved */
    (uint32_t)&interrupt_handler,    /* Vector - 293    Reserved */
};

#include "MPC5604B_0M27V_0102.h" /* Use proper include file */
#include "HardwareTRK-MPC5604B.h"

void interrupt_handler(void) {
	// [DEBUG]
	uint32_t j;
    
   	vfnSet_DCMotor1_Duty_Perc(0);
	vfnSet_DCMotor1_Back_Duty_Perc(0);
	vfnSet_DCMotor2_Duty_Perc(0);
	vfnSet_DCMotor2_Back_Duty_Perc(0);
	
	while (1) {
		for (j = 0; j < 0xfffff; j++) {}
		
		LED1 ^= 1;
	}
	// [\DEBUG]
	
	/* Wait forever or for watchdog timeout */
}
