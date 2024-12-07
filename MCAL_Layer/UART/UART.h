/*
 * UART.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Rawan Waleed
 */

#ifndef MCAL_LAYER_UART_UART_H_
#define MCAL_LAYER_UART_UART_H_

/-----------------------Includes-----------------------/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/------------------Macros Declarations------------------/
#define UART_DATA_5BITS              0X0
#define UART_DATA_6BITS              0X1
#define UART_DATA_7BITS              0X2
#define UART_DATA_8BITS              0X3
#define UART_LCRH_WLEN_BITS_POS      5
#define UART_CTL_UARTEN_MASK         0x00000001
#define UART_CTRL_TXE_MASK           0x00000100
#define UART_CTRL_RXE_MASK           0x00000200
#define UART_FR_TXFE_MASK            0x00000080
#define UART_FR_RXFE_MASK            0x00000010

/-------------Macros Functions Declarations-------------/


/-----------------Data Type Declarations-----------------/

/-----------------Functions Declarations-----------------/



#endif /* MCAL_LAYER_UART_UART_H_ */
