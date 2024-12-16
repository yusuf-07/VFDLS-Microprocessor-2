/*
 * LM35.h
 *
 *  Created on: Dec 16, 2024
 *      Author: Rawan Waleed
 */

#ifndef _2_ECU_LAYER_LM35_LM35_H_
#define _2_ECU_LAYER_LM35_LM35_H_

/*-----------------------Includes-----------------------*/
#include <_1_MCAL_Layer/ADC/ADC.h>
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include <_1_MCAL_Layer/UART/UART.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*------------------Macros Declarations------------------*/
#define ENGINE_TEMP_THRESHOLD      90                         /* Engine temperature threshold */
#define DTC_ENGINE_TEMP            "P002"                     /* Diagnostic code for ENGINE_HIGH_TEMPERATURE */
#define TEMP_ERROR                 "ENGINE_HIGH_TEMPERATURE"  /* Error description that the engine temperature > 90 degree C*/

/*-------------Macros Functions Declarations-------------*/

/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/
uint32 LM35_GET_TEMP(void);
void Monitor_TEMP(void);

#endif /* _2_ECU_LAYER_LM35_LM35_H_ */
