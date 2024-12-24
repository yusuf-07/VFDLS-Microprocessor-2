/*
 * ADC.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Rawan Waleed
 */

#include <_1_MCAL_Layer/ADC/ADC.h>

/*** ===================== Local Function Section Start ===================== ***/

void GPIO_SetupPE2AnalogPin(void)
{
    SYSCTL_RCGCGPIO_REG  |= (1<<4);               /* Enable clock for GPIO PORTE */
    while(GET_BIT(SYSCTL_PRGPIO_REG,4) == 0);     /* Wait until GPIO PORTE clock is activated and it is ready for access*/

    GPIO_PORTE_DIR_REG   &= ~(1<<2);              /* Configure PE2 as input pin */
    GPIO_PORTE_AMSEL_REG |= (1<<2);               /* Enable Analog at PE2 */
    GPIO_PORTE_AFSEL_REG |= (1<<2);               /* Enable alternative function at PE2 */
    GPIO_PORTE_PCTL_REG  &= 0xFFFFF0FF;           /* Set PMCx bits for PE2 with value 0 to use as analog pin */
    GPIO_PORTE_DEN_REG   &= ~(1<<2);              /* Disable Digital at PE2 */
}
/*** ===================== Local Function Section End ======================= ***/

/*** ===================== Global Function Section Start ===================== ***/

/**
 * @brief
 */

void ADC0_Init(void)
{
    GPIO_SetupPE2AnalogPin();                      /* Initialize PE0 as Ain3 */

    SYSCTL_RCGCADC_REG |= (1<<0);                  /* Enable clock for ADC0 */
    while(GET_BIT(SYSCTL_PRADC_REG,0) == 0);       /* Wait until ADC0 clock is activated and it is ready for access*/
    SYSCTL_RCGCADC_REG &= ~0x00000300;               /* Set the Sample Rate for ADC0 to 125K Samples per second by clearing bit 8 and 9 */

    ADC0_SSPRI_REG   = 0x0123;                     /* Set priority for all four Sequencers and Sequencer 3 is the highest priority */
    ADC0_ACTSS_REG  &= ~(1<<3);                    /* Disable Sample Sequencer 3 */
    ADC0_EMUX_REG   &= ~0xF000;                    /* Sequencer 3 is triggered by software */
    ADC0_SSMUX3_REG &= ~0x000F;                    /* Clear MUX0 field */
    ADC0_SSMUX3_REG |= 1;                          /* Set channel number read by Sequencer 3 to Ain1 (PE2) */
    ADC0_SSCTL3_REG |= (1<<1) | (1<<2);            /* Set IE0 and END0 bits */
    ADC0_ACTSS_REG  |= (1<<3);                     /* Enable Sample Sequencer 3 */
}
/**
 * @brief
 * @param channel:
 */

uint32 ADC0_ReadSeq3(void)
{
    uint32 result;
    ADC0_PSSI_REG |= (1<<3);                  /* Initiate SS3 to start the conversion by Sequencer 3 */
    while(GET_BIT(ADC0_RIS_REG,3) == 0){};    /* Wait for conversion in Sequencer 3 to be completed by polling the INR3 bit */
    result = ADC0_SSFIFO3_REG & 0xFFF;        /* Read result from Sequencer 3 FIFO register  */
    ADC0_ISC_REG |= (1<<3);                   /* Clear INR3 flag bit in ADC0_RIS_REG by setting IN3 but in ADC0_ISC_REG */
    return result;
}
/*
 * ADC.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Yusuf Abulfotouh
 */

/*** ===================== Local Function Section Start ===================== ***/

/**
 * @brief Configures PD2 as an analog input pin.
 */
void GPIO_SetupPD2AnalogPin(void)
{
    SYSCTL_RCGCGPIO_REG  |= (1 << 3);              /* Enable clock for GPIO PORTD */
    while (GET_BIT(SYSCTL_PRGPIO_REG, 3) == 0);    /* Wait until GPIO PORTD clock is activated and ready for access */

    GPIO_PORTD_LOCK_REG  = 0x4C4F434B;             /* Unlock PORTD to enable changes on PD2 */
    GPIO_PORTD_CR_REG   |= (1 << 2);               /* Commit changes on PD2 */
    GPIO_PORTD_DIR_REG  &= ~(1 << 2);              /* Configure PD2 as input pin */
    GPIO_PORTD_AMSEL_REG |= (1 << 2);              /* Enable Analog at PD2 */
    GPIO_PORTD_AFSEL_REG |= (1 << 2);              /* Enable alternate function at PD2 */
    GPIO_PORTD_PCTL_REG  &= 0xFFFFF0FF;            /* Set PMCx bits for PD2 with value 0 to use as analog pin */
    GPIO_PORTD_DEN_REG   &= ~(1 << 2);             /* Disable Digital at PD2 */
}

/*** ===================== Local Function Section End ======================= ***/

/*** ===================== Global Function Section Start ===================== ***/

/**
 * @brief Initializes ADC0 with Sequencer 3 to read from ADC Channel 5 (PD2).
 * @param channel: ADC channel to initialize (should be ADC_CHANNEL5).
 */
void ADC1_Init(adc_channelId_t channel)
{
    GPIO_SetupPD2AnalogPin();                      /* Initialize PD2 as analog input */

    SYSCTL_RCGCADC_REG |= (1 << 0);                /* Enable clock for ADC0 */
    while (GET_BIT(SYSCTL_PRADC_REG, 0) == 0);     /* Wait until ADC0 clock is activated and ready for access */
    SYSCTL_RCGCADC_REG &= ~0x00000300;             /* Set the Sample Rate for ADC0 to 125K Samples per second by clearing bits 8 and 9 */

    ADC0_SSPRI_REG   = 0x0123;                     /* Set priority for all four Sequencers, Sequencer 3 is the highest priority */
    ADC0_ACTSS_REG  &= ~(1 << 3);                  /* Disable Sample Sequencer 3 */
    ADC0_EMUX_REG   &= ~0xF000;                    /* Sequencer 3 is triggered by software */
    ADC0_SSMUX3_REG &= ~0x000F;                    /* Clear MUX0 field */
    ADC0_SSMUX3_REG |= channel;                    /* Set channel number read by Sequencer 3 (e.g., ADC_CHANNEL5 for PD2) */
    ADC0_SSCTL3_REG |= (1 << 1) | (1 << 2);        /* Set IE0 and END0 bits */
    ADC0_ACTSS_REG  |= (1 << 3);                   /* Enable Sample Sequencer 3 */
}

/**
 * @brief Reads the ADC value from Sequencer 3.
 * @return Result of the ADC conversion.
 */
uint32 ADC1_ReadSeq3(void)
{
    uint32 result;
    ADC0_PSSI_REG |= (1 << 3);                 /* Initiate SS3 to start the conversion by Sequencer 3 */
    while (GET_BIT(ADC0_RIS_REG, 3) == 0);     /* Wait for conversion in Sequencer 3 to be completed by polling the INR3 bit */
    result = ADC0_SSFIFO3_REG & 0xFFF;         /* Read result from Sequencer 3 FIFO register */
    ADC0_ISC_REG |= (1 << 3);                  /* Clear INR3 flag bit in ADC0_RIS_REG by setting IN3 bit in ADC0_ISC_REG */
    return result;
}


/**
 * @brief Reads the ADC value from Sequencer 3.
 * @return Result of the ADC conversion.
 */



