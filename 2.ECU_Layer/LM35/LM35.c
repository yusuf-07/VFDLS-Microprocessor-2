/*
 * LM35.c
 *
 *  Created on: Dec 16, 2024
 *      Author: Rawan Waleed
 */
#include "2.ECU_Layer/LM35/LM35.h"


/**
 * @brief
 * @return
 */
uint32 LM35_GET_TEMP(void){
    uint32 ADC_Value = ADC0_ReadSeq3();             /* Read the value from the ADC */
    /* 10mV  --> 1 degree celcius*/
    /* Vout of LM35 = 10mV/oC = 0.01 V/oC*/
    /* oC = Vout * 100 */
    /* resolution = range / precision*/
    /* range of ADC is 3.3v-0v = 3.3v */
    /* ADC is 12 bit so precision is 2^12 = 4096 */
    /* convert ADC output to voltage then converting this voltage to degrees celcius */
    /* temp in degree celcius= (((ADC_Value *3.3)/4096)*100) */
    uint32 temperature = (ADC_Value  * 330) / 4096;
    return temperature;
}

void Monitor_TEMP(void){
    uint32 engineTemperature = LM35_GET_TEMP();
    if (engineTemperature > ENGINE_TEMP_THRESHOLD) {
       /*TO_DO*/  // Log_Error(DTC_ENGINE_TEMP);  //we could just display until implementing the log_error function
        UART0_SendString("Error logged: ");
        UART0_SendString(DTC_ENGINE_TEMP);
        UART0_SendString("  ");
        UART0_SendString(TEMP_ERROR);
        UART0_SendString("#");
    }
}
