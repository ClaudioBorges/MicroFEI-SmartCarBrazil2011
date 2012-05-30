/**
 * MicroFEI Team - SmartCar Brazil 2011
 * Centro Universitário da FEI - http://www.fei.edu.br/
 *
 *  Cesar Osaka     - cesar.osaka@gmail.com
 *  Claudio Borges  - claudio.borges.jr@gmail.com
 *  Munir Mattes    - munir.sp@gmail.com  
 * 
 */

#ifndef _UART_H_
#define _UART_H_

/*
 *		Includes
 */
#include "MPC5604B_0M27V_0102.h"

/*
 *		Typedefs/Structs
 */
struct UART_FIFO
{
	unsigned int start;
	unsigned int end;
	unsigned int count;
	unsigned int length;
	char *buff;
};

extern struct UART_FIFO fifoTx1;

/*
 *		Defines
 */
#define UARTDisableInts()	LINFLEX_0.LINIER.B.DTIE = 0 //Disable Transmission interrupt
#define UARTEnableInts()	LINFLEX_0.LINIER.B.DTIE = 1 //Enable Transmission interrupt

/*
 *		Functions Prototypes
 */
void initLINFlex_0_UART (void);
int _UARTWrite(short int *pBuff, unsigned int length);
int UARTWrite(char *pBuff, unsigned int length);
int fifoEnqueue(struct UART_FIFO *pFifo, char data);
int fifoDequeue(struct UART_FIFO *pFifo, char *pData);
int fifoEmpty(struct UART_FIFO *pFifo);

#define IsUartFifoEmpty()	(fifoEmpty(&fifoTx1))

#endif // _UART_H_