/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

/*
 *		Includes
 */
#include "uart.h"

/*
 *		Variables
 */
char buffTx1[128];
struct UART_FIFO fifoTx1 = 
	{0, 0, 0, sizeof(buffTx1), buffTx1};

volatile char txBusy = 0;

/*
 *		Functions Prototypes
 */
void UARTTransmit(void);

/*
 *		Functions
 */
/***************************************************/
 void initLINFlex_0_UART (void)
 /***************************************************/
 {
 		/* enter INIT mode */
	LINFLEX_0.LINCR1.R = 0x0081; 		/* SLEEP=0, INIT=1 */
	
	/* wait for the INIT mode */
	while (0x1000 != (LINFLEX_0.LINSR.R & 0xF000)) {}
		
	/* configure pads */
	SIU.PCR[18].R = 0x0604;     		/* Configure pad PB2 for AF1 func: LIN0TX */
	SIU.PCR[19].R = 0x0100;     		/* Configure pad PB3 for LIN0RX */	
	
	/* configure for UART mode */
	LINFLEX_0.UARTCR.R = 0x0001; 		/* set the UART bit first to be able to write the other bits */
	LINFLEX_0.UARTCR.R = 0x0033; 		/* 8bit data, no parity, Tx and Rx enabled, UART mode */
								 		/* Transmit buffer size = 1 (TDFL = 0 */
								 		/* Receive buffer size = 1 (RDFL = 0) */
	
	LINFLEX_0.LINIBRR.B.DIV_M = 104; 	/* Mantissa baud rate divider 104 component 38400*/
	LINFLEX_0.LINFBRR.B.DIV_F = 3;		/* Fraction baud rate divider 3 comonent 38400*/

	LINFLEX_0.LINIER.B.DTIE = 1;		// Enable Transmission interrupt
	INTC.PSR[80].B.PRI = 3;			// Interrupt vector priority
		
	/* enter NORMAL mode */
	LINFLEX_0.LINCR1.R = 0x0080; /* INIT=0 */
}

/***************************************************/
void UARTTransmit(void)
/***************************************************/
{
	char byte;
	
	if ( fifoTx1.count >= 4 )
	{
		LINFLEX_0.UARTCR.B.TDFL = (4-1);
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA0 = byte;
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA1 = byte;
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA2 = byte;
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA3 = byte;
	}
	else if ( fifoTx1.count == 3 )
	{
		LINFLEX_0.UARTCR.B.TDFL = (3-1);
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA0 = byte;
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA1 = byte;
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA2 = byte;
	}
	else if ( fifoTx1.count == 2 )
	{
		LINFLEX_0.UARTCR.B.TDFL = (2-1);
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA0 = byte;
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA1 = byte;
	}
	else if ( fifoTx1.count == 1 )
	{
		LINFLEX_0.UARTCR.B.TDFL = (1-1);
		
		fifoDequeue(&fifoTx1, &byte);
		LINFLEX_0.BDRL.B.DATA0 = byte;
	}
}

/***************************************************/
void LINFlex_TXI(void)
/***************************************************/
{
	/*if (LINFLEX_0.LINSR.B.DTF)
		LINFLEX_0.LINSR.B.DTF = 1;*/
	
	if (LINFLEX_0.UARTSR.B.DTF)
		LINFLEX_0.UARTSR.B.DTF = 1;
	
	if ( !fifoTx1.count )
		txBusy = 0;
	else
		UARTTransmit();
}

/***************************************************/
int _UARTWrite(short int *pBuff, unsigned int length)
/***************************************************/
{
	unsigned int i;
	int startTx;
	
	LINFLEX_0.LINIER.B.DTIE = 0;		// Disable Transmission interrupt

	if ( fifoEmpty(&fifoTx1) )
		startTx = 1;
	else
		startTx = 0;

	for ( i = 0; i < length; i++ )
	{
		if ( fifoEnqueue(&fifoTx1, (char)pBuff[i]) )
			break;
	}
	
	if ( startTx )
	{
		while (LINFLEX_0.LINSR.B.LINS == 0b1000) {}
		
		UARTTransmit();
	}
	
	LINFLEX_0.LINIER.B.DTIE = 1;		// Enable Transmission interrupt
	
	return i;
}

/***************************************************/
int UARTWrite(char *pBuff, unsigned int length)
/***************************************************/
{
	unsigned int i;
	int startTx;
	
	LINFLEX_0.LINIER.B.DTIE = 0;		// Disable Transmission interrupt

	if ( fifoEmpty(&fifoTx1) )
		startTx = 1;
	else
		startTx = 0;

	for ( i = 0; i < length; i++ )
	{
		if ( fifoEnqueue(&fifoTx1, pBuff[i]) )
			break;
	}
	
	if ( startTx )
	{
		while (LINFLEX_0.LINSR.B.LINS == 0b1000) {}
		
		UARTTransmit();
	}
	
	LINFLEX_0.LINIER.B.DTIE = 1;		// Enable Transmission interrupt
	
	return i;
}

/***************************************************/
int fifoEnqueue(struct UART_FIFO *pFifo, char data)
/***************************************************/
{
	if ( pFifo->count < pFifo->length )
	{
		pFifo->buff[pFifo->end++] = data;
		
		if ( pFifo->end == pFifo->length )
			pFifo->end = 0;
			
		pFifo->count++;
		
		#ifdef ENABLE_UART_DEBUG
		
		if ( pFifo->count > pFifo->max )
			pFifo->max = pFifo->count;
			
		#endif
		
		return 0;
	}
	
	return -1;
}

/***************************************************/
int fifoDequeue(struct UART_FIFO *pFifo, char *pData)
/***************************************************/
{
	if ( pFifo->count )
	{
		*pData = pFifo->buff[pFifo->start++];
		
		if ( pFifo->start == pFifo->length )
			pFifo->start = 0;
			
		pFifo->count--;
		
		txBusy = 1;
		
		return 0;
	}
	
	return -1;
} 

/***************************************************/
int fifoEmpty(struct UART_FIFO *pFifo)
/***************************************************/
{
	if ( pFifo->count == 0 && !txBusy)
		return 1;
	else
		return 0;
}