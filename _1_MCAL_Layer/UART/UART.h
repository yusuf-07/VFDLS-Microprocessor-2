/***
==================================================================================
* @file     : UART.h
* @author   : Rawan Waleed
* @version  : v1.1
* @brief    : UART Driver Header File
* @details  : Provides macros and function prototypes for UART operations
==================================================================================
***/

#ifndef _1_MCAL_LAYER_UART_UART_H_
#define _1_MCAL_LAYER_UART_UART_H_

/*** ===================== Include Section Start =========================== ***/
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* UART Data Lengths */
#define UART_DATA_5BITS              0X0
#define UART_DATA_6BITS              0X1
#define UART_DATA_7BITS              0X2
#define UART_DATA_8BITS              0X3

/* UART Line Control Register (LCRH) Word Length Bit Position */
#define UART_LCRH_WLEN_BITS_POS      5

/* UART Control Register Masks */
#define UART_CTL_UARTEN_MASK         0x00000001   /* UART Enable */
#define UART_CTL_TXE_MASK           0x00000100   /* Transmit Enable */
#define UART_CTL_RXE_MASK           0x00000200   /* Receive Enable */

/* UART Flag Register Masks */
#define UART_FR_TXFE_MASK            0x00000080   /* Transmit FIFO Empty */
#define UART_FR_RXFE_MASK            0x00000010   /* Receive FIFO Empty */
/*** ====================== Macros Section End ============================= ***/


/*** ================= Functions Declaration Section Start ================= ***/
/* Function to initialize UART0 */
void UART0_Init(void);

/* Function to send a byte of data */
void UART0_SendByte(unsigned char data);

/* Function to send a string of data */
void UART0_SendString(unsigned char *pData);

/* Function to send a specific number of bytes */
void UART0_SendData(unsigned char *pData, unsigned long uSize);

/* Function to receive a byte of data */
unsigned char UART0_ReceiveByte(void);

/* Function to receive a string of data */
void UART0_ReceiveString(unsigned char *pData);

/* Function to receive a specific number of bytes */
void UART0_ReceiveData(unsigned char *pData, unsigned long uSize);

/*** ================= Functions Declaration Section End ==================== ***/

#endif /* _1_MCAL_LAYER_UART_UART_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       07Dec24     Created UART Header File
Rawan       10Dec24     Added functions declarations
**/
