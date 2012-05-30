/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef _DRIVER_NTSC_HEADER
#define _DRIVER_NTSC_HEADER

// Para desativar comente o define
#include "HardwareTRK-MPC5604B.h"

#define IMG_TOP_FIRST			0
#if IMG_TOP_FIRST == 0
	#define I_SUPPORT_POINT_FILTER	0//1
#else
	#define I_SUPPORT_POINT_FILTER	0
#endif

// Determina se o ínicio/fim de volta será detectado
// END_OF_RACE_DETECTION == 1 ==>> ínicio/fim de volta será detectado
// END_OF_RACE_DETECTION == 0 ==>> ínicio/fim de volta não será detectado
#define	END_OF_RACE_DETECTION	0//1

//#define DEBUG_FRAME_READ_PIN		LED3
//#define DEBUG_LINE_READ_PIN			LED3
//#define DEBUG_COMP_SYNC_ERROR_PIN 	LED4	
//#define DEBUG_VERT_PULSE_ERROR_PIN 	LED4	
//#define DEBUG_BURST_GATE_ERROR_PIN 	LED4

/* PF[4] */
#define NTSC_COMP_SYNC_PCR			84
#define NTSC_COMP_SYNC_PCR_VALUE	0x0601

/* PF[2] */
#define NTSC_VERT_SYNC_PCR			82
#define NTSC_VERT_SYNC_PCR_VALUE	0x0601

/* PF[5] */
#define NTSC_BURST_GATE_PCR			85
#define NTSC_BURST_GATE_PCR_VALUE	0x0601

/* PF[8] */
#define NTSC_ADC_PCR				80
#define NTSC_ADC_PCR_VALUE			0x2000

#define MAX_NTSC_COLUMNS			60		/* Based on ADC time */
#define MAX_NTSC_LINES				120		/* Base on NTSC Spec and ADC time */

#define MAX_CENTER_POS		100
#define CENTER_POS			50
#define MIN_CENTER_POS		0

extern int16_t myCentersMatrix[];

#if (END_OF_RACE_DETECTION == 1)
extern int16_t my3CentersMatrix[];
extern int16_t my3CurrentSample;
#endif // (END_OF_RACE_DETECTION == 1)

void initNTSC(void);
uint16_t captureFrame(void);

#if I_SUPPORT_NTSC_SYNC_ONE_FRAME == 0
	void stopNTSC(void);
	void resumeNTSC(void);
#endif

#endif // _DRIVER_NTSC_HEADER
