/*
 * ADC.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Rawan Waleed
 */

#include <_1_MCAL_Layer/ADC/ADC.h>

/*** ===================== Local Function Section Start ===================== ***/

void GPIO_SetupPE0AnalogPin(void)
{
    SYSCTL_RCGCGPIO_REG  |= (1<<4);               /* Enable clock for GPIO PORTE */
    while(GET_BIT(SYSCTL_PRGPIO_REG,4) == 0);     /* Wait until GPIO PORTE clock is activated and it is ready for access*/

    GPIO_PORTA_DIR_REG   &= ~(1<<0);              /* Configure PE0 as input pin */
    GPIO_PORTA_AMSEL_REG |= (1<<0);               /* Enable Analog at PE0 */
    GPIO_PORTA_AFSEL_REG |= (1<<0);               /* Enable alternative function at PE0 */
    GPIO_PORTA_PCTL_REG  &= 0xFFFFFFF0;           /* Set PMCx bits for PE0 with value 0 to use as analog pin */
    GPIO_PORTA_DEN_REG   &= ~(1<<0);              /* Disable Digital at PE0 */
}
/*** ===================== Local Function Section End ======================= ***/

/*** ===================== Global Function Section Start ===================== ***/

/**
 * @brief
 */

void ADC0_Init(void)
{
    GPIO_SetupPE0AnalogPin();                      /* Initialize PE0 as Ain3 */

    SYSCTL_RCGCADC_REG |= (1<<0);                  /* Enable clock for ADC0 */
    while(GET_BIT(SYSCTL_PRADC_REG,0) == 0);       /* Wait until ADC0 clock is activated and it is ready for access*/
    SYSCTL_RCGCADC_REG &= ~0x00000300;               /* Set the Sample Rate for ADC0 to 125K Samples per second by clearing bit 8 and 9 */

    ADC0_SSPRI_REG   = 0x0123;                     /* Set priority for all four Sequencers and Sequencer 3 is the highest priority */
    ADC0_ACTSS_REG  &= ~(1<<3);                    /* Disable Sample Sequencer 3 */
    ADC0_EMUX_REG   &= ~0xF000;                    /* Sequencer 3 is triggered by software */
    ADC0_SSMUX3_REG &= ~0x000F;                    /* Clear MUX0 field */
    ADC0_SSMUX3_REG |= 3;                          /* Set channel number read by Sequencer 3 to Ain3 (PE0) */
    ADC0_SSCTL3_REG |= (1<<1) | (1<<2);            /* Set IE0 and END0 bits */
    ADC0_ACTSS_REG  |= (1<<3);                     /* Enable Sample Sequencer 3 */
}
/**
 * @brief
 * @param channel:
 */

uint32 ADC0_ReadSeq3(void)
{
    uint32 result = 0;
    ADC0_PSSI_REG |= (1<<3);                  /* Initiate SS3 to start the conversion by Sequencer 3 */
    while(GET_BIT(ADC0_RIS_REG,3) == 0){};    /* Wait for conversion in Sequencer 3 to be completed by polling the INR3 bit */
    result = ADC0_SSFIFO3_REG & 0xFFF;        /* Read result from Sequencer 3 FIFO register  */
    ADC0_ISC_REG |= (1<<3);                   /* Clear INR3 flag bit in ADC0_RIS_REG by setting IN3 but in ADC0_ISC_REG */
    return result;
}

