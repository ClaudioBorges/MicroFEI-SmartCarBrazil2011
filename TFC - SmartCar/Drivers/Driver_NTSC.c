/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef _DRIVER_NTSC_C_SRC
#define _DRIVER_NTSC_C_SRC
/*******************************************************************************
*** 
*** MODULES USED 
*** 
*******************************************************************************/
#include "MPC5604B_0M27V_0102.h" /* Use proper include file */
//#include "Driver_SAIC.h"
#include "Driver_NTSC.h"

/*******************************************************************************
*** 
*** DEFINITIONS AND MACROS 
*** 
*******************************************************************************/
#define SYSTEM_CLOCK			64000000ul
#define EMIOS_NTSC_PRESCALER	16ul
#define NTSC_COUNTER_PRESCALER	1ul

#define NTSC_FREQ				(SYSTEM_CLOCK / EMIOS_NTSC_PRESCALER / NTSC_COUNTER_PRESCALER)
#define CNT_NTSC_T_uSEC			(NTSC_FREQ / 1000000ul)
#define iCNT_NTSC_T_uSEC		(1000000ul / NTSC_FREQ)

#if CNT_NTSC_T_uSEC >= 1
	#define CONVERT_US_IN_CNT(val)		((val) * CNT_NTSC_T_uSEC)
#else //elif iCNT_T_uSEC >= 1
	#define CONVERT_US_IN_CNT(val)		((val) / iCNT_NTSC_T_uSEC)
#endif


#define COMP_SYNC_HOR_MIN		(CONVERT_US_IN_CNT(58u))
#define COMP_SYNC_HOR_MAX		(CONVERT_US_IN_CNT(68u))

/* Initialize */
#define RISING_EDGE 	1u
#define FALLING_EDGE 	0u

#define NTSC_COMP_SYNC_CHANNEL			14u
#define NTSC_COMP_SYNC_PCR_CHANNEL		84u
#define NTSC_COMP_SYNC_PSMI_CHANNEL		22u
#define NTSC_COMP_SYNC_PSMI_VAL			1u
#define NTSC_COMP_SYNC_EDGE				FALLING_EDGE
#define NTSC_COMP_SYNC_INT_VEC			148u
#define NTSC_COMP_SYNC_INT_PRIOR		4u

#define NTSC_VERT_SYNC_CHANNEL			12u
#define NTSC_VERT_SYNC_PCR_CHANNEL		82u
#define NTSC_VERT_SYNC_PSMI_CHANNEL		20u
#define NTSC_VERT_SYNC_PSMI_VAL			1u
#define NTSC_VERT_SYNC_EDGE				RISING_EDGE
#define NTSC_VERT_SYNC_INT_VEC			147u
#define NTSC_VERT_SYNC_INT_PRIOR		4u

#define NTSC_BURST_GATE_SYNC_CHANNEL	22u
#define NTSC_BURST_GATE_PCR_CHANNEL		85u
#define NTSC_BUSRT_GATE_PSMI_CHANNEL	23u
#define NTSC_BUSRT_SYNC_PSMI_VAL		2u
#define NTSC_BURST_GATE_EDGE			RISING_EDGE
#define NTSC_BURST_GATE_INT_VEC			152u
#define NTSC_BURST_GATE_INT_PRIOR		4u

#define NTSC_ADC_INT_VEC				62u
#define NTSC_ADC_INT_PRIOR				4u
#define NTSC_ADC_CHANNEL				40u
#define NTSC_ADC_CEOCFR 				ADC.CEOCFR[1].B.EOC_CH8

/* Composite Sync */
#define COMP_SYNC_GET()			(EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CADR.B.CADR)
#define COMP_SYNC_OVFL_GET()	(EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CSR.B.OVFL)
#define COMP_SYNC_CLR_FLAG() 	EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CSR.B.OVR 	= 1; \
								EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CSR.B.OVFL 	= 1; \
								EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CSR.B.FLAG 	= 1
#define COMP_SYNC_START()		(void)COMP_SYNC_GET(); 	\
								COMP_SYNC_CLR_FLAG(); 	\
								EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CCR.B.FEN = 1
#define COMP_SYNC_STOP()		EMIOS_0.CH[NTSC_COMP_SYNC_CHANNEL].CCR.B.FEN = 0

#define COMP_SYNC_HOR_CNT			12 		/* See NTSC specification - 4 =  Ajuste manual */
#define MAX_WAIT_IMG_COMP_SYNC		15 		/* See NTSC specification */

/* Burst Gate */
#define BURST_GATE_CLR_FLAG() 	EMIOS_0.CH[NTSC_BURST_GATE_SYNC_CHANNEL].CSR.B.OVR 	= 1; \
								EMIOS_0.CH[NTSC_BURST_GATE_SYNC_CHANNEL].CSR.B.OVFL = 1; \
								EMIOS_0.CH[NTSC_BURST_GATE_SYNC_CHANNEL].CSR.B.FLAG = 1
#define BUSRT_GATE_START()		BURST_GATE_CLR_FLAG(); \
								EMIOS_0.CH[NTSC_BURST_GATE_SYNC_CHANNEL].CCR.B.FEN = 1
#define BURST_GATE_STOP()		EMIOS_0.CH[NTSC_BURST_GATE_SYNC_CHANNEL].CCR.B.FEN = 0

/* Vertical Sync */
#define VERT_PULSE_CLR_FLAG()	EMIOS_0.CH[NTSC_VERT_SYNC_CHANNEL].CSR.B.OVR 	= 1; \
								EMIOS_0.CH[NTSC_VERT_SYNC_CHANNEL].CSR.B.OVFL 	= 1; \
								EMIOS_0.CH[NTSC_VERT_SYNC_CHANNEL].CSR.B.FLAG 	= 1
#define VERT_SYNC_START()		VERT_PULSE_CLR_FLAG(); \
								EMIOS_0.CH[NTSC_VERT_SYNC_CHANNEL].CCR.B.FEN = 1
#define VERT_SYNC_STOP()		EMIOS_0.CH[NTSC_VERT_SYNC_CHANNEL].CCR.B.FEN = 0

/* Data */
#define ADC_START_CONVERT()		(void)ADC.CDR[NTSC_ADC_CHANNEL].B.CDATA; \
								ADC.MCR.B.ABORT = 0; \
								ADC.MCR.B.NSTART = 1 /* Dummy read to clear previous data */ /* Inicia a conversao do AD */
#define ADC_STOP_CONVERT()		ADC.MCR.B.ABORT = 1; \
								ADC.MCR.B.NSTART = 0 /* Para a conversao do AD */

#define NTSC_STOP()				COMP_SYNC_STOP();	\
								BURST_GATE_STOP();	\
								ADC_STOP_CONVERT(); \
								VERT_SYNC_STOP()
											
#define NTSC_INIT()				COMP_SYNC_STOP();	\
								BURST_GATE_STOP();	\
								ADC_STOP_CONVERT(); \
								VERT_SYNC_START()

/* ADC  */
#define NTSC_AD_MAX_VAL				1023u 	/* 10 bits */
#define NTSC_AD_REF					5u		/* 5V */

#define CONVERT_V_TO_AD_VAL(v)		((uint16_t)(((uint32_t)v * NTSC_AD_MAX_VAL) / (NTSC_AD_REF * 1000)))

#define IMG_DELTA_LINE_DETECTION	 CONVERT_V_TO_AD_VAL(400/*450/*380*//*340*//*520*/)

#define IMG_MAX_CENTER_PER_LINE		3
#define IMG_MIN_LINE_PIXELS			40	/* Base in ADC time */
#define IMG_MIN_FRAME_LINES			60	/* Base in NTSC Spec and Filters times */

/*******************************************************************************
*** 
*** TYPEDEFS AND STRUCTURES
*** 
*******************************************************************************/
enum gfStates {
	endFrame,

	waitingVertSync,
	
	waitingIMGCompSync,
	countingCompSyncFrames,
	
	waitingBusrtGate,
	waitingCompSync,
};

enum compSync_States {
	compSync_FirstEdge,
	compSync_AnotherEdge,
};

/*******************************************************************************
*** 
*** PROTOTYPES OF LOCAL FUNCTIONS 
*** 
*******************************************************************************/
void stopNTSC(void);
void resumeNTSC(void);
void initFrameDetectMatrixes(void);
int16_t filterPoint(void);

/*******************************************************************************
*** 
*** EXPORTED VARIABLES 
*** 
*******************************************************************************/
uint16_t 	myColumnMatrix[MAX_NTSC_COLUMNS];
uint16_t 	myCurrentColumn;
int16_t		myCentersMatrix[MAX_NTSC_LINES];
uint16_t	myCurrentLine;

uint16_t	myCentersPoints[IMG_MAX_CENTER_PER_LINE];
uint8_t		myNumCentersPoints;

uint8_t		myWaitingIMGCompSync;

uint8_t		myNTSCError;

#if (END_OF_RACE_DETECTION == 1)
// Determina a distância (dy) máxima que será aceita
// para ser detectado uma linha com 3 faixas pretas
// Caso seja detectado uma linha com 3 faixas pretas
// e a próxima linha com 3 faixas pretas vier após 
// (MAX_3_LINE_VERT_DISTANCE + 1) esta última e todas
// após são ignoradas, deixando armazenado
// todas as faixas anteriores detectadas
#define 	MAX_3_LINE_VERT_DISTANCE		2

// Determina a quantidade máxima de linhas com 3
// faixas pretas serão armazenadas na matriz
// Lembrando que as linhas armazenadas poderão
// estar distanciadas de no máximo MAX_3_LINE_VERT_DISTANCE
#define		MAX_3_CENTERS_SAMPLES	10

// Determina qual o tamanho da matriz my3CentersMatrix
// A matriz armazena os dados da seguinte forma:
// index	O que será armazenado
//	 0		índice da primeira linha capturada da câmera(Posição y)
//	 1		Valor do centro da faixa 1
//	 2		Valor do centro da faixa 2
//	 3		Valor do centro da faixa 3
//	 4		índice da segunda linha capturada da câmera(Posição y)
//	 1		Valor do centro da faixa 1
//	...
// Logo cada linha capturada contém 4 posições na tabela 
#define		MAX_3_CENTERS_SIZE		(MAX_3_CENTERS_SAMPLES * 4)	// (index + 3 black centers) = 4 bytes

int16_t		my3CentersMatrix[MAX_3_CENTERS_SIZE];
int16_t		my3CurrentLine;
int16_t		my3CurrentSample;
int16_t		my3LastIndex;

#if (MAX_3_CENTERS_SIZE < 4)
#error "MAX_3_CENTERS_SIZE deve ser maior ou igual a 4."
#endif // (MAX_3_CENTERS_SIZE < 4)
#endif // (END_OF_RACE_DETECTION == 1)

/*******************************************************************************
*** 
*** GLOBAL VARIABLES    
*** 
*******************************************************************************/
volatile enum gfStates gfState;

volatile uint8_t  	compSyncFrameCount;
volatile uint8_t	compSyncWaitIMG;
volatile uint32_t 	compSync_A;
volatile uint32_t 	compSync_B;
volatile uint32_t 	compSyncPeriod;
volatile enum compSync_States compSyncState;

/*******************************************************************************
*** 
*** EXPORTED FUNCTIONS    
*** 
*******************************************************************************/
void stopNTSC(void)
{
	gfState = endFrame;

	NTSC_STOP();
}

void resumeNTSC(void)
{
	NTSC_STOP();

	gfState			= waitingVertSync;

	NTSC_INIT();
}

void initNTSC(void)
{
	compSync_A 		= 0;
	compSync_B		= 0;
	compSyncPeriod	= 0;

	compSyncState 	= compSync_FirstEdge;
	gfState			= waitingVertSync;
	
	/* Inicializa SAIC */
	INTC.PSR[NTSC_COMP_SYNC_INT_VEC].R 	= NTSC_COMP_SYNC_INT_PRIOR;
	INTC.PSR[NTSC_VERT_SYNC_INT_VEC].R 	= NTSC_VERT_SYNC_INT_PRIOR;
	INTC.PSR[NTSC_BURST_GATE_INT_VEC].R = NTSC_BURST_GATE_INT_PRIOR;
	
	SIU.PSMI[NTSC_COMP_SYNC_PSMI_CHANNEL].R 	= NTSC_COMP_SYNC_PSMI_VAL;
	SIU.PSMI[NTSC_VERT_SYNC_PSMI_CHANNEL].R 	= NTSC_VERT_SYNC_PSMI_VAL;
	SIU.PSMI[NTSC_BUSRT_GATE_PSMI_CHANNEL].R 	= NTSC_BUSRT_SYNC_PSMI_VAL;
	
	vfnInit_Emios_0_Mcb(23, 0xFFFF, 1); /* Set channel 23 as MCB  */	
	
    vfnInit_Emios_0_Saic(NTSC_COMP_SYNC_CHANNEL, 
						 NTSC_COMP_SYNC_PCR_CHANNEL,
						 NTSC_COMP_SYNC_EDGE);
    vfnInit_Emios_0_Saic(NTSC_VERT_SYNC_CHANNEL, 
						 NTSC_VERT_SYNC_PCR_CHANNEL,
						 NTSC_VERT_SYNC_EDGE);
	vfnInit_Emios_0_Saic(NTSC_BURST_GATE_SYNC_CHANNEL, 
						 NTSC_BURST_GATE_PCR_CHANNEL,
						 NTSC_BURST_GATE_EDGE);
	/* ADC initialize */
	INTC.PSR[NTSC_ADC_INT_VEC].R 		= 0; // Do not use ADC interrupt 
	SIU.PCR[NTSC_ADC_PCR].R 			= NTSC_ADC_PCR_VALUE;
	adc_init_fnc();
	
	NTSC_STOP();
}

void initFrameDetectMatrixes(void)
{
	uint16_t i;
	
	for (i = 0; i < MAX_NTSC_COLUMNS; ++i) {
		myColumnMatrix[i] 	= 0;
	}
	
	for (i = 0; i < MAX_NTSC_LINES; ++i) {
		myCentersMatrix	[i] = -1;
	}
}

int16_t getLineCenters(void)
{
	uint16_t i;
		
	uint16_t posFaixaStart;

	register uint16_t columnTmp;
	register uint16_t columnMaxMinTmp;
	
	if (myCurrentColumn < IMG_MIN_LINE_PIXELS)
		return -1;
	
	myNumCentersPoints = 0;
	posFaixaStart = 0;

	columnMaxMinTmp = myColumnMatrix[0];

	for (i = 1; i < myCurrentColumn; ++i) {

		columnTmp = myColumnMatrix[i];

		if (posFaixaStart == 0) {
			// Procurando o ínicio da faixa preta
			if (columnTmp >= columnMaxMinTmp) {
				// Ponto "mais branco" detectado, armazena max
				columnMaxMinTmp = columnTmp;
			}
			else if ((columnMaxMinTmp - columnTmp) >= IMG_DELTA_LINE_DETECTION) {
				// Diferença entre branco e preto detectada, armazena ínicio e min
				posFaixaStart = i;
				columnMaxMinTmp = columnTmp;
			}
		}
		else if (myNumCentersPoints < IMG_MAX_CENTER_PER_LINE) {
			// Procurando o término da faixa preta
			if (columnTmp <= columnMaxMinTmp) {
				// Ponto "mais preto" detectado, armazena min
				columnMaxMinTmp = columnTmp;
			}
			else if ((columnTmp - columnMaxMinTmp) >= IMG_DELTA_LINE_DETECTION) {
				// Diferença entre preto e branco detectada, linha detectada

				myCentersPoints[myNumCentersPoints] = posFaixaStart + (i - 1);
				
				posFaixaStart = 0;
				++myNumCentersPoints;

				columnMaxMinTmp = columnTmp;
			}
		}
	}
	

	for (i = 0; i < myNumCentersPoints; i++) {
		myCentersPoints[i] = (MAX_CENTER_POS * myCentersPoints[i]) / ((myCurrentColumn - 1) * 2);
	}

	#if (END_OF_RACE_DETECTION == 1)
	if (myNumCentersPoints == 3) {
		if (!my3CurrentSample) {
			my3CentersMatrix[0] = myCurrentLine;
			my3CentersMatrix[1] = myCentersPoints[0];
			my3CentersMatrix[2] = myCentersPoints[1];
			my3CentersMatrix[3] = myCentersPoints[2];
			
			my3CurrentLine = 4;
			my3CurrentSample = 1;
			
			my3LastIndex = myCurrentLine;
			
			//return -3;
		}
		else if (myCurrentLine <= (my3LastIndex + MAX_3_LINE_VERT_DISTANCE)) {
			if (my3CurrentSample < MAX_3_CENTERS_SAMPLES) {
				my3CentersMatrix[my3CurrentLine] = myCurrentLine;
				my3CentersMatrix[my3CurrentLine + 1] = myCentersPoints[0];
				my3CentersMatrix[my3CurrentLine + 2] = myCentersPoints[1];
				my3CentersMatrix[my3CurrentLine + 3] = myCentersPoints[2];
				
				my3CurrentLine += 4;
				my3CurrentSample++;
				
				my3LastIndex = myCurrentLine;
				
				//return -3;
			}
		}
	}
	#endif // (END_OF_RACE_DETECTION == 1)

#if I_SUPPORT_POINT_FILTER == 1
	return filterPoint();
#else
	switch (myNumCentersPoints) {
	case 0:
		/* Nenhuma linha detectada, erro */
		return -1;
	
	case 1:
		/*  Linha detectada */
		return myCentersPoints[0];	
		
	default:
		/* Mais de 1 linha detectada retornar negativamente a quantidade */
		return -myNumCentersPoints;
	}
#endif
}

void captureLine(void)
{
	/* Espera pelo estado waitingCompSync - Quando o burstGate ja rodou e o AD deve iniciar */
	myCurrentColumn = 0;

	while (gfState != waitingBusrtGate	&& gfState != endFrame);
	while (gfState != waitingCompSync	&& gfState != endFrame);
	
	#ifdef DEBUG_LINE_READ_PIN
		DEBUG_LINE_READ_PIN = 1;
	#endif
	
	/* Wait for last scan to complete */
	while (1) {
		if (ADC.CDR[NTSC_ADC_CHANNEL].B.VALID == 1) {
			if (myCurrentColumn < MAX_NTSC_COLUMNS) {
				myColumnMatrix[myCurrentColumn] = ADC.CDR[NTSC_ADC_CHANNEL].B.CDATA;
				++myCurrentColumn;
			}
		}
		if (gfState != waitingCompSync) {
			/* Acabou o Frame */
			/* Por segurança descartar a ultima coluna */
			myColumnMatrix[myCurrentColumn] = -1;
			--myCurrentColumn;
			return;				
		}
	}
	
	#ifdef DEBUG_LINE_READ_PIN
		DEBUG_LINE_READ_PIN = 0;
	#endif
}

uint16_t captureFrame(void)
{
	/* Espera sincronismo vertical */
	myCurrentLine = 0;
	#if (END_OF_RACE_DETECTION == 1)
	my3CurrentSample = 0;
	#endif // (END_OF_RACE_DETECTION == 1)
	initFrameDetectMatrixes();
	
	resumeNTSC();
	
	while (gfState != waitingVertSync && gfState != endFrame);

	#ifdef DEBUG_FRAME_READ_PIN
		DEBUG_FRAME_READ_PIN = 0;
	#endif
	
	do {
		/* Inicia captura de imagem até encontrar sincronismo vertical */
		captureLine();
		if (gfState == endFrame)
			break;
		
		if (myCurrentLine < MAX_NTSC_LINES) {
			myCentersMatrix[myCurrentLine] = getLineCenters();
			++myCurrentLine;
		}
	} while (gfState != waitingVertSync);
	
	#ifdef DEBUG_FRAME_READ_PIN
		DEBUG_FRAME_READ_PIN = 0;
	#endif
	
	if (myNTSCError || myCurrentLine < IMG_MIN_FRAME_LINES) {
		initFrameDetectMatrixes();
		return 0;
	}
	
	return myCurrentLine;
}

/*******************************************************************************
*** 
*** LOCAL FUNCTIONS 
*** 
*******************************************************************************/
//#define FILTER_OPTION_1
#define FILTER_OPTION_2

static uint8_t myLast1Point;
static int16_t myCumulativeDelta;

/* IMG get and filter */
int16_t filterPoint(void)
{
	if (myNumCentersPoints == 0)
		return -1;
	else if (myNumCentersPoints == 1)
	{
		if (myCurrentLine == 0)
		{
			myLast1Point = 0;
			myCumulativeDelta = 0;
		}
		else if (myCentersMatrix[myCurrentLine - 1] < 0)
		{
			int16_t deltaPoint;
			
			myLast1Point = myCurrentLine;
			
			deltaPoint = 
				myCentersPoints[myCurrentLine] - myCentersMatrix[myCurrentLine - 1];
				
			if (myCurrentLine == 1)
			{
				myCumulativeDelta = deltaPoint;
			}
			else // if (myCurrentLine >= 2)
			{
				myCumulativeDelta = ((3 * myCumulativeDelta) + deltaPoint) / 4;
			}
		}
		
		return myCentersPoints[0];
	}
	
    if (myCurrentLine >= 2) {
		uint16_t cmp;
		int16_t lastDelta;
		int16_t smallerDelta2;
		int16_t deltaPoint;
		int16_t currDelta2;
		uint8_t i;
		uint8_t smaller;
		
		#if defined(FILTER_OPTION_1)
		
        /* Try to measure up to last 3 points */
        if (myCentersMatrix[myCurrentLine - 1] < 0
            || myCentersMatrix[myCurrentLine - 2] < 0)
            return -myNumCentersPoints;
			
        cmp = myCentersMatrix[myCurrentLine - 1];
        lastDelta = cmp - myCentersMatrix[myCurrentLine - 2];
		
		#elif defined(FILTER_OPTION_2)
		
		if (myLast1Point == 0)
			return -myNumCentersPoints;
			
		#endif
		
        /* Find smaller deviation */
		smaller = 0;
		smallerDelta2 = 32600;
        for (i = 0; i < myNumCentersPoints; ++i) {
            
			#if defined(FILTER_OPTION_1)

			deltaPoint = myCentersPoints[i] - cmp;

			if (deltaPoint > lastDelta)
				currDelta2 = deltaPoint - lastDelta;
			else
				currDelta2 = lastDelta - deltaPoint;

			if (currDelta2 < smallerDelta2) {
				smaller = i;
				smallerDelta2 = currDelta2;
			}

			#elif defined(FILTER_OPTION_2)

			deltaPoint = myCentersPoints[i] - myCentersPoints[myLast1Point];

			if (deltaPoint > myCumulativeDelta)
				currDelta2 = deltaPoint - myCumulativeDelta;
			else
				currDelta2 = myCumulativeDelta - deltaPoint;

			if (currDelta2 < smallerDelta2) {
				smaller = i;
				smallerDelta2 = currDelta2;
			}

			#endif
        }
		
        return myCentersPoints[smaller];
    }
	
    return -myNumCentersPoints;
}

/* LM 1881 */
void int_icCompSync(void)
{
	#ifdef DEBUG_COM_SYNC_INT
		DEBUG_COM_SYNC_INT ^= 1;
	#endif	

	/* Responsavel por verificar os periodos para assim distinguir em qual estado esta 
	   e para a leitura do ADC */
	switch (compSyncState) {
		case compSync_AnotherEdge:
			compSync_B = COMP_SYNC_GET();
			/* Verificar estouro de timer */
			#if 1
				if (compSync_B > compSync_A) {
					compSyncPeriod = compSync_B - compSync_A;
				}
				else {
					compSyncPeriod = compSync_B + (0xFFFF - compSync_A);
				}
			#else
				compSyncPeriod = compSync_B + ((0xFFFF * COMP_SYNC_OVFL_GET()) - compSync_A);
			#endif
			
			/* Atualiza compSync_A */
			compSync_A = compSync_B;
			
			if (compSyncPeriod > COMP_SYNC_HOR_MIN 
				&& compSyncPeriod < COMP_SYNC_HOR_MAX) {
				switch (gfState) {
					case countingCompSyncFrames:
						compSyncFrameCount++;
						if (compSyncFrameCount == COMP_SYNC_HOR_CNT ) 
						{
							BUSRT_GATE_START();
							COMP_SYNC_STOP();
							gfState = waitingBusrtGate;
						}
						break;
					
					case waitingCompSync:
						BUSRT_GATE_START();
						
						ADC_STOP_CONVERT();
						COMP_SYNC_STOP();
						
						gfState = waitingBusrtGate;
						break;
					
					case waitingIMGCompSync:
						compSyncFrameCount = 1;
						
						gfState = countingCompSyncFrames;
						break;
						
					default:
						goto compSync_error;
						break;
				}
			}
			else {
				switch (gfState) {
					case waitingCompSync:
						NTSC_STOP();
					
						gfState = endFrame;
						break;

					case waitingBusrtGate:
					case countingCompSyncFrames:
						/* Impossible condition */
						goto compSync_error;
						break;
					
					case waitingIMGCompSync:
						++myWaitingIMGCompSync;
						if (myWaitingIMGCompSync >= MAX_WAIT_IMG_COMP_SYNC)
							goto compSync_error;
						break;
						
					default:
					case waitingVertSync:
						break;
				}				
			}
			break;
			
		case compSync_FirstEdge:
		default:
			compSyncState 	= compSync_AnotherEdge;
			compSync_A 		= COMP_SYNC_GET();
			break;
	}
	
	COMP_SYNC_CLR_FLAG();
	return;

compSync_error:

	NTSC_STOP();

	myNTSCError		= 1;
	gfState 		= endFrame;
	
	#ifdef DEBUG_COMP_SYNC_ERROR_PIN
		DEBUG_COMP_SYNC_ERROR_PIN ^= 1;
	#endif	
	
	COMP_SYNC_CLR_FLAG();
}

void int_icVertPulse(void)
{
	#ifdef DEBUG_VERT_SYNC_INT
		DEBUG_VERT_SYNC_INT ^= 1;
	#endif
	
	/* Responsavel por verificar quanto esta em sincronismo vertical */
	switch (gfState) {
		case waitingVertSync:
			
			/* Reset NTSC */
			compSync_A 		= 0;
			compSync_B		= 0;
			compSyncPeriod	= 0;

			compSyncState 	= compSync_FirstEdge;
			
			myNTSCError		= 0;

			VERT_SYNC_STOP();
			COMP_SYNC_START();
				
			myWaitingIMGCompSync = 0;
			
			gfState = waitingIMGCompSync;
			break;
		
		default:
			goto vertPulse_error;
			break;
	}
	
	VERT_PULSE_CLR_FLAG();
	return;
	
vertPulse_error:

	NTSC_STOP();

	myNTSCError		= 1;
	gfState 		= endFrame;

	#ifdef DEBUG_VERT_PULSE_ERROR_PIN
		DEBUG_VERT_PULSE_ERROR_PIN ^= 1;
	#endif
	
	VERT_PULSE_CLR_FLAG();
}

void int_icBurstGate(void)
{
	#ifdef DEBUG_BURST_GATE_INT
		DEBUG_BURST_GATE_INT ^= 1;
	#endif

	/* Disparo para a leitura do ADC */
	switch (gfState) {
		case waitingBusrtGate:
			ADC_START_CONVERT();
			COMP_SYNC_START();
			BURST_GATE_STOP();
			
			gfState = waitingCompSync;
			break;
		
		default:
			goto burstGate_error;
			break;
	}
	

	BURST_GATE_CLR_FLAG();
	return;
	
burstGate_error:

	NTSC_STOP();

	myNTSCError		= 1;
	gfState 		= endFrame;
		
	#ifdef DEBUG_BURST_GATE_ERROR_PIN
		DEBUG_BURST_GATE_ERROR_PIN ^= 1;
	#endif
	
	BURST_GATE_CLR_FLAG();
}

/*******************************************************************************
*** 
*** EOF
*** 
*******************************************************************************/
#endif // _DRIVER_NTSC_C_SRC
