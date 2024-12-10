/***
==================================================================================
* @file     : UART.c
* @author   : Rawan Waleed
* @version  : v1.1
* @brief    : UART Driver Source File
* @details  : Implements UART initialization, data transmission, and reception
==================================================================================
***/

#include "UART.h"

/*** ===================== Local Function Section Start ===================== ***/

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

/*** ===================== Local Function Section End ======================= ***/

/*** ===================== Global Function Section Start ===================== ***/

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
* @brief    : Sends a string of data over UART0
* @param    : pData - Pointer to the null-terminated string to be sent
* @return   : None
***/
void UART0_SendString(unsigned char *pData)
{
    unsigned long uCounter = 0;

    /*Transmit the whole string*/
    while(pData[uCounter] != '\0'){                /*loop until the null terminator*/
        while(UART0_FR_REG & UART_FR_TXFE_MASK);   /* Wait until the TX FIFO is not full */
        UART0_DR_REG = pData[uCounter];            /* send the current character */
        uCounter++;                                /*Move to the next character*/
    }
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

/***
* @brief    : Receives a string of data over UART0 until a newline character is encountered
* @param    : pData - Pointer to the buffer where the received string will be stored
* @return   : None
***/
void UART0_ReceiveString(unsigned char *pData)
{
    unsigned long uCounter = 0;

    while(pData[uCounter] != '\n'){               /*receive the entire string until terminates by a new line  (\n)*/
    pData[uCounter] = UART0_ReceiveByte();        /* Wait until the RX FIFO is not empty and read the received character*/
    uCounter++;                                   /* Move to the next character */
    }

    pData[uCounter] = '\0';                       /*the string is then null terminated*/
}

/*** ===================== Global Function Section End ======================= ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       07Dec24     Created UART Source File
Rawan       10Dec24     Updated UART driver to send and receives strings
**/
