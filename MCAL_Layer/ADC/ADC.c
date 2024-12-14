/*
 * ADC.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Rawan Waleed
 */

#include "ADC.h"

/*** ===================== Local Function Section Start ===================== ***/

/***
* @brief    : Set up
* @param    : None
* @return   : None
***/
//static void GPIO_SetupADCPins(void)
//{
//    SYSCTL_RCGCGPIO_REG  |= 0x01;                 /* Enable clock for GPIO PORTA */
//    while(GET_BIT(SYSCTL_RCGCGPIO_REG,0) == 0);   /* Wait until GPIO PORTA clock is activated and it is ready for access*/
//
//    GPIO_PORTA_AMSEL_REG &= 0xFC;                 /* Disable Analog on PA0 & PA1 */
//    GPIO_PORTA_DIR_REG   &= 0xFE;                 /* Configure PA0 as input pin */
//    GPIO_PORTA_DIR_REG   |= 0x02;                 /* Configure PA1 as output pin */
//    GPIO_PORTA_AFSEL_REG |= 0x03;                 /* Enable alternative function on PA0 & PA1 */
//
//    /* Set PMCx bits for PA0 & PA1 with value 1 to use PA0 as UART0 RX pin and PA1 as UART0 Tx pin */
//    GPIO_PORTA_PCTL_REG  = (GPIO_PORTA_PCTL_REG & 0xFFFFFF00) | 0x00000011;
//
//    GPIO_PORTA_DEN_REG   |= 0x03;                  /* Enable Digital I/O on PA0 & PA1 */
//}

/*** ===================== Local Function Section End ======================= ***/

/*** ===================== Global Function Section Start ===================== ***/

/**
 * @brief
 */
void ADC_INIT(void){
    //GPIO_SetupADCPins();

}

/**
 * @brief
 * @param channel:
 */
void ADC_READ_CHANNEL(adc_channelId_t channel){

}
