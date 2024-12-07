/***
==================================================================================
* @file     : UART.h
* @author   : Rawan Waleed
* @version  : v1.0
* @brief    : UART Driver Header File
* @details  : Provides macros and function prototypes for UART operations
==================================================================================
***/

#ifndef MCAL_LAYER_UART_UART_H_
#define MCAL_LAYER_UART_UART_H_

/*** ===================== Include Section Start =========================== ***/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
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
#define UART_CTRL_TXE_MASK           0x00000100   /* Transmit Enable */
#define UART_CTRL_RXE_MASK           0x00000200   /* Receive Enable */

/* UART Flag Register Masks */
#define UART_FR_TXFE_MASK            0x00000080   /* Transmit FIFO Empty */
#define UART_FR_RXFE_MASK            0x00000010   /* Receive FIFO Empty */
/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
/* No global variables required for this header file */
/*** ================= Global Declaration Section End ====================== ***/

/*** ================= Functions Declaration Section Start ================= ***/
/* Function to initialize UART0 */
void UART0_Init(void);

/* Function to send a byte of data */
void UART0_SendByte(unsigned char data);

/* Function to receive a byte of data */
unsigned char UART0_ReceiveByte(void);
/*** ================= Functions Declaration Section End ==================== ***/

#endif /* MCAL_LAYER_UART_UART_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       07Dec24     Created UART Header File
**/
