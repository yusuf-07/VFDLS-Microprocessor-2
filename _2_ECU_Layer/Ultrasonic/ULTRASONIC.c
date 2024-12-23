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
volatile uint8 measured_time = 0;
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
//
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
    // Enable the clock for Port D
    SYSCTL_RCGCGPIO_REG |= (1 << 4); // Set bit 4 of SYSCTL_RCGCGPIO_REG to enable GPIO Port D clock
    while ((SYSCTL_PRGPIO_REG & 0x05) == 0); // Wait for GPIO Port D to be ready

    // Disable analog functionality on Port D pins
    GPIO_PORTE_AMSEL_REG = 0x00; // Disable analog mode on all pins of Port D

    // Set Port D pin control register to 0 for default function
    GPIO_PORTE_PCTL_REG = 0xFF00FFFF; // Set PCTL to 0 for default GPIO functionality on all pins

    // Configure Ultrasonic Trigger pin as digital output
    GPIO_Init(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, GPIO_DIGITAL, GPIO_OUTPUT, GPIO_AF_DEF);

    // Configure Ultrasonic Echo pin as digital input
    GPIO_Init(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, GPIO_DIGITAL, GPIO_INPUT, GPIO_AF_DEF);
}


/***
* @brief    : Sends a trigger pulse to the Ultrasonic Sensor.
* @param    : None
* @return   : None
***/
void Ultrasonic_Trigger(void)
{
    GPIO_DigitalWrite(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOW);
    SysTick_DelayUs(10);
    GPIO_DigitalWrite(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, HIGH);
    SysTick_DelayUs(10);
    GPIO_DigitalWrite(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOW);
}

/***
* @brief    : Retrieves the measured distance from the Ultrasonic Sensor.
* @param    : None
* @return   : Distance in centimeters.
***/
uint32 Ultrasonic_GetDistance(void)
{
    unsigned long measured_distance = 0;
    unsigned long measured_time = 0;
    Ultrasonic_Trigger();

    /* Wait for distance calculation to complete */
    //while (edge_detected);

    //return measured_distance;
    while (GPIO_DigitalRead(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) == 0);
    while (GPIO_DigitalRead(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) != 0)
    {
        measured_time++;
        SysTick_DelayUs(10);
    }
    measured_distance = (measured_time * 340.0)/(2*1000); //to convert to cm
    return measured_distance;

}



void Monitor_DIST(void)
{
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
