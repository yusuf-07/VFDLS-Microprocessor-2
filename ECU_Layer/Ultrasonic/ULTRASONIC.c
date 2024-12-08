/***
==================================================================================
* @file     : ULTRASONIC.c
* @author   : Yusuf
* @version  : v1.2
* @brief    : Ultrasonic Sensor Driver Source File
* @details  : Implements initialization, interrupt configuration, and distance measurement
==================================================================================
***/

#include "ultrasonic.h"

/*** ===================== Global Variables Section Start ====================== ***/
volatile uint32 pulse_start = 0;
volatile uint32 pulse_end = 0;
volatile uint8 edge_detected = 0;
volatile uint32 measured_distance = 0;
/*** ===================== Global Variables Section End ======================== ***/

/*** ===================== Private Function Section Start ===================== ***/

/***
* @brief    : Configures GPIO pins for Trigger and Echo of the Ultrasonic Sensor.
* @param    : None
* @return   : None
***/
static void GPIO_SetupUltrasonicPins(void)
{
    /* Enable clock for Port B and wait for it to stabilize */
    SYSCTL_RCGCGPIO_REG |= (1 << 1);
    while (!(SYSCTL_PRGPIO_REG & (1 << 1)));

    /* Configure Trigger Pin (PB5) as Output */
    GPIO_PORTB_DIR_REG |= (1 << ULTRASONIC_TRIGGER_PIN);
    GPIO_PORTB_DEN_REG |= (1 << ULTRASONIC_TRIGGER_PIN);

    /* Configure Echo Pin (PB6) as Input */
    GPIO_PORTB_DIR_REG &= ~(1 << ULTRASONIC_ECHO_PIN);
    GPIO_PORTB_DEN_REG |= (1 << ULTRASONIC_ECHO_PIN);

    /* Configure PB6 for Edge-Triggered Interrupt */
    GPIO_PORTB_IS_REG &= ~(1 << ULTRASONIC_ECHO_PIN);   /* Edge-sensitive */
    GPIO_PORTB_IBE_REG &= ~(1 << ULTRASONIC_ECHO_PIN);  /* Single edge */
    GPIO_PORTB_IEV_REG |= (1 << ULTRASONIC_ECHO_PIN);   /* Rising edge initially */
    GPIO_PORTB_IM_REG |= (1 << ULTRASONIC_ECHO_PIN);    /* Unmask interrupt */
    GPIO_PORTB_ICR_REG |= (1 << ULTRASONIC_ECHO_PIN);   /* Clear interrupt flag */
}

/***
* @brief    : Configures interrupts for the Echo pin.
* @param    : None
* @return   : None
***/
static void Ultrasonic_EnableInterrupts(void)
{
    /* 1. Global Interrupt Enable (I-bit) */
    __asm("CPSIE I");

    /* 2. NVIC Interrupt Enable */
    NVIC_EN0_R |= (1 << 1); /* Interrupt number 1 for GPIO Port B */

    /* 3. NVIC Priority */
    NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFFFF1F) | (2 << 5); /* Priority level 2 for GPIO Port B */

    /* 4. Module Interrupt Enable (MIE) */
    GPIO_PORTB_IM_REG |= (1 << ULTRASONIC_ECHO_PIN);

    /* 5. Module Interrupt Flag (MIF) */
    GPIO_PORTB_ICR_REG |= (1 << ULTRASONIC_ECHO_PIN);
}

/***
* @brief    : ISR for Echo Pin to calculate pulse width using edge detection.
* @param    : None
* @return   : None
***/
void GPIOPortB_Handler(void)
{
    if (edge_detected == 0)
    {
        pulse_start = SYSTICK_CURRENT_REG;             /* Capture rising edge time */
        GPIO_PORTB_IEV_REG &= ~(1 << ULTRASONIC_ECHO_PIN); /* Switch to Falling Edge */
        edge_detected = 1;
    }
    else
    {
        pulse_end = SYSTICK_CURRENT_REG;              /* Capture falling edge time */
        GPIO_PORTB_IEV_REG |= (1 << ULTRASONIC_ECHO_PIN);  /* Switch to Rising Edge */
        edge_detected = 0;

        /* Calculate distance in cm */
        uint32 pulse_width = pulse_start - pulse_end;
        measured_distance = (pulse_width * 0.034) / 2; /* Speed of sound = 0.034 cm/us */
    }

    GPIO_PORTB_ICR_REG |= (1 << ULTRASONIC_ECHO_PIN); /* Clear interrupt flag */
}

/*** ===================== Private Function Section End ======================= ***/

/*** ===================== Public Function Section Start ===================== ***/

/***
* @brief    : Initializes the Ultrasonic Sensor with interrupt-based edge detection.
* @param    : None
* @return   : None
***/
void Ultrasonic_Init(void)
{
    GPIO_SetupUltrasonicPins();
    Ultrasonic_EnableInterrupts();

    /* Configure SysTick Timer */
    SysTick_Init(SYSTICK_MAX_RELOAD_VALUE);
}

/***
* @brief    : Retrieves the measured distance from the Ultrasonic Sensor.
* @param    : None
* @return   : Distance in centimeters.
***/
uint32 Ultrasonic_GetDistance(void)
{
    /* Send Trigger Pulse */
    GPIO_PORTB_DATA_REG |= (1 << ULTRASONIC_TRIGGER_PIN);
    SysTick_DelayUs(10); /* 10us Pulse */
    GPIO_PORTB_DATA_REG &= ~(1 << ULTRASONIC_TRIGGER_PIN);

    /* Wait for distance calculation to complete */
    while (edge_detected);

    return measured_distance;
}

/*** ===================== Public Function Section End ======================= ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created Ultrasonic Source file
Yusuf       08Dec24     Updated Ultrasonic Driver for Interrupt Compliance
**/
