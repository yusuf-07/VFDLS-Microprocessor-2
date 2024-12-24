/*
 * Flex_Sensor.c
 *
 *  Created on: 24 Dec 2024
 *      Author: yabul
 */

#include <_2_ECU_Layer/Flex_Sensor/Flex_Sensor.h>
#define   R_DIV        32000
#define   VCC          5.0
#define FLAT_RESISTANCE 25000.0  // Resistance when flat
#define BEND_RESISTANCE 100000.0 // Resistance at 90 degrees

uint32 Get_Pressure(void) {
    uint32 ADC_Value = ADC1_ReadSeq3(); // Read the value from the ADC
    /* The voltage range for the ADC is 0V to 3.3V */
    /* ADC is 12-bit, so the resolution is 2^12 = 4096 */
    /* Vout = (ADC_Value / 4096) * 3.3 */
    //uint32 angle = (ADC_Value * 5) / 4095;
    uint32 angle = ADC_Value - 100;
    uint32 pressure;


//    long long pressure;
//    // Calculate bend angle
//    long long angle = (uint32)((Rflex - FLAT_RESISTANCE) * (90.0f / (BEND_RESISTANCE - FLAT_RESISTANCE)));

    if (angle < 1) {
        pressure = 10;
        // Clamp the angle to valid range
    }
    else if (angle > 1 && angle < 90)
    {
        pressure = angle - 20;
    }
    else if (angle > 90) {
        pressure = 32;
    }

    return pressure;
}



void Monitor_Pressure(void){
    uint32 tirePressure = Get_Pressure();
    if (tirePressure < TIRE_PRESSURE_THRESHOLD) {
        Log_Fault(DTC_TIRE_PRESSURE);              // Log_Error(DTC_TIRE_PRESSURE)in the EEPROM
        UART0_SendString("Error logged: ");
        UART0_SendString(DTC_TIRE_PRESSURE);
        UART0_SendString("  ");
        UART0_SendString(PRESSURE_ERROR);
        UART0_SendString("#");
    }
}

void Display_Pressure(void)
{
    long pressure = Get_Pressure();  // Get the pressure reading

    // Print the pressure to the UART terminal
    UART0_SendString("Tire Pressure: ");
    UART0_SendByte((pressure / 10) + '0');   // Tens digit
    UART0_SendByte((pressure % 10) + '0');   // Ones digit
    UART0_SendString(" psi\n");              // Append units
}

