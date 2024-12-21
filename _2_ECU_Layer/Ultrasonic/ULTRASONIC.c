/***
==================================================================================
* @file     : ULTRASONIC.c
* @author   : Yusuf Abulfotouh
* @version  : v1.3
* @brief    : Ultrasonic Sensor Driver Source File
* @details  : Implements initialization, SysTick timer, and GPIO interrupt-based
*             distance measurement for the ultrasonic sensor.
==================================================================================
***/

#include <_2_ECU_Layer/Ultrasonic/ULTRASONIC.h>

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
//static void GPIO_SetupUltrasonicPins(void)
//{
//    /* Enable clock for Port B */
//    GPIO_Init(GPIO_PORTB, ULTRASONIC_TRIGGER_PIN, GPIO_DIGITAL, GPIO_OUTPUT, GPIO_AF_DEF); /* Trigger: Digital, Output */
//    GPIO_Init(GPIO_PORTB, ULTRASONIC_ECHO_PIN, GPIO_DIGITAL, GPIO_INPUT, GPIO_AF_DEF);     /* Echo: Digital, Input */
//
//    /* Configure PB6 (Echo) for Edge-Triggered Interrupt */
//    GPIO_PORTB_IS_REG  &= ~(1 << ULTRASONIC_ECHO_PIN);  /* Edge-sensitive */
//    GPIO_PORTB_IBE_REG &= ~(1 << ULTRASONIC_ECHO_PIN);  /* Single edge */
//    GPIO_PORTB_IEV_REG |= (1 << ULTRASONIC_ECHO_PIN);   /* Rising edge initially */
//    GPIO_PORTB_IM_REG  |= (1 << ULTRASONIC_ECHO_PIN);   /* Unmask interrupt */
//    GPIO_PORTB_ICR_REG |= (1 << ULTRASONIC_ECHO_PIN);   /* Clear interrupt flag */
//}
static void GPIO_SetupUltrasonicPins(void)
{
    GPIO_Init(GPIO_PORTC, ULTRASONIC_TRIGGER_PIN, GPIO_DIGITAL, GPIO_OUTPUT, GPIO_AF_DEF);
    GPIO_Init(GPIO_PORTC, ULTRASONIC_ECHO_PIN, GPIO_DIGITAL, GPIO_INPUT, GPIO_AF_DEF);
}

/***
* @brief    : Configures interrupts for the Echo pin.
* @param    : None
* @return   : None
***/
//static void Ultrasonic_EnableInterrupts(void)
//{
//    /* 1. Global Interrupt Enable (I-bit) */
//    Enable_Exceptions();
//
//    /* 2. NVIC Priority Configuration */
//    NVIC_PRI0_REG = (NVIC_PRI0_REG & ~GPIO_PORTB_PRIORITY_MASK) | (GPIO_PORTB_INTERRUPT_PRIORITY << GPIO_PORTB_PRIORITY_BITS_POS);
//
//    /* 3. NVIC Interrupt Enable for GPIO Port B */
//    NVIC_EN0_REG |= (1 << 1); /* Interrupt number 1 for Port B */
//}
/*** ===================== Private Function Section End ======================= ***/

/*** ===================== Public Function Section Start ===================== ***/
/***
* @brief    : Initializes the Ultrasonic Sensor with SysTick timer and GPIO interrupts.
* @param    : None
* @return   : None
***/
void Ultrasonic_Init(void)
{
    GPIO_SetupUltrasonicPins();
//    Ultrasonic_EnableInterrupts();
//
//    /* Configure SysTick Timer */
//    SysTick_Init(SYSTICK_MAX_RELOAD_VALUE);
}

/***
* @brief    : Retrieves the measured distance from the Ultrasonic Sensor.
* @param    : None
* @return   : Distance in centimeters.
***/
uint32 Ultrasonic_GetDistance(void)
{
    /* Send Trigger Pulse */
    //GPIO_PORTB_DATA_REG |= (1 << ULTRASONIC_TRIGGER_PIN);
    GPIO_DigitalWrite(GPIO_PORTC, ULTRASONIC_TRIGGER_PIN, 0);
    SysTick_DelayUs(10); /* Delay 10us Pulse */
    //GPIO_PORTB_DATA_REG &= ~(1 << ULTRASONIC_TRIGGER_PIN);
    GPIO_DigitalWrite(GPIO_PORTC, ULTRASONIC_TRIGGER_PIN, 1);
    SysTick_DelayUs(10);
    GPIO_DigitalWrite(GPIO_PORTC, ULTRASONIC_TRIGGER_PIN, 0);

    /* Wait for distance calculation to complete */
    //while (edge_detected);

    //return measured_distance;
    while (GPIO_DigitalRead(GPIO_PORTC, ULTRASONIC_ECHO_PIN) == 0);
    while (GPIO_DigitalRead(GPIO_PORTC, ULTRASONIC_ECHO_PIN) == 0)
    {
        edge_detected++;
        SysTick_DelayUs(1);
    }
    measured_distance = (edge_detected*340.0)/(2*1000); //to convert to cm
    return measured_distance;

}



void Monitor_DIST(void){
    uint32 measured_Distance = Ultrasonic_GetDistance();
    if (measured_Distance < DISTANCE_THRESHOLD) {
        Log_Fault(DTC_DISTANCE );              // Log_Error(DTC_DISTANCE)in the EEPROM
        UART0_SendString("Error logged: ");
        UART0_SendString(DTC_DISTANCE);
        UART0_SendString("  ");
        UART0_SendString(DIST_ERROR);
        UART0_SendString("#");
    }
}

/*** ===================== Public Function Section End ======================= ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created Ultrasonic Source File
Yusuf       08Dec24     Updated Ultrasonic Driver for Interrupt Compliance
Yusuf       12Dec24     Updated with SysTick and GPIO Interrupts
**/
