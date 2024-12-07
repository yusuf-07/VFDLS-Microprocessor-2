/***
==================================================================================
* @file     : UART.c
* @author   : Rawan Waleed
* @version  : v1.0
* @brief    : UART Driver Source File
* @details  : Implements UART initialization, data transmission, and reception
==================================================================================
***/

#include "UART.h"

/*** ===================== Private Function Section Start ===================== ***/

/***
* @brief    : Set up the Tx and Rx pins in the GPIO register for UART0
* @param    : None
* @return   : None
***/
static void GPIO_SetupUART0Pins(void)
{
    /* Enable clock for PORTA and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x01;
    while(GET_BIT(SYSCTL_PRGPIO_REG, 0) == 0);

    GPIO_PORTA_AMSEL_REG &= 0xFC;      /* Disable Analog on PA0 and PA1 */
    GPIO_PORTA_DIR_REG   &= 0xFE;      /* Configure PA0 as input pin */
    GPIO_PORTA_DIR_REG   |= 0x02;      /* Configure PA1 as output pin */
    GPIO_PORTA_AFSEL_REG |= 0x03;      /* Enable alternative function on PA0 and PA1 */
    GPIO_PORTA_DEN_REG   |= 0x03;      /* Enable Digital I/O on PA0 and PA1 */

    GPIO_PORTA_PCTL_REG  = (GPIO_PORTA_PCTL_REG & 0xFFFFFF00) | 0x00000011;   /* Configure PA0 and PA1 as UART using mode 1 */
}

/*** ===================== Private Function Section End ======================= ***/

/*** ===================== Public Function Section Start ===================== ***/

/***
* @brief    : Initializes UART0 for communication
* @param    : None
* @return   : None
***/
void UART0_Init(void)
{
    GPIO_SetupUART0Pins();             /* Configure GPIO pins for UART0 */

    /* Enable clock for UART0 and wait for it to be ready */
    SYSCTL_RCGCUART_REG |= 0x01;
    while(!(SYSCTL_PRUART_REG & 0x01));

    UART0_CTL_REG = 0;                /* Disable UART0 during configuration */
    UART0_CC_REG = 0;                 /* Configure UART0 clock source */

    /* Configure baud rate */
    UART0_IBRD_REG = 104;            /* Set integer part of baud rate divisor */
    UART0_FBRD_REG = 11;             /* Set fractional part of baud rate divisor */

    UART0_LCRH_REG = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS);  /* Set word length to 8 bits */
    UART0_CTL_REG = UART_CTL_UARTEN_MASK | UART_CTRL_TXE_MASK | UART_CTRL_RXE_MASK;  /* Enable UART0 Tx and Rx */
}

/***
* @brief    : Sends a byte of data over UART0
* @param    : data - The byte to be sent
* @return   : None
***/
void UART0_SendByte(unsigned char data)
{
    while(UART0_FR_REG & UART_FR_TXFE_MASK);  /* Wait until the TX FIFO is not full */
    UART0_DR_REG = data;                      /* Write the byte to the Data Register */
}

/***
* @brief    : Receives a byte of data from UART0
* @param    : None
* @return   : The received byte
***/
unsigned char UART0_ReceiveByte(void)
{
    while(UART0_FR_REG & UART_FR_RXFE_MASK);  /* Wait until the RX FIFO is not empty */
    return UART0_DR_REG;                      /* Read the byte from the Data Register */
}

/*** ===================== Public Function Section End ======================= ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       07Dec24     Created UART Source File
**/
