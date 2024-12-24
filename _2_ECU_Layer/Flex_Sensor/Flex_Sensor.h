/*
 * Flex_Sensor.h
 *
 *  Created on: 24 Dec 2024
 *      Author: yabul
 */

#ifndef _2_ECU_LAYER_FLEX_SENSOR_H_
#define _2_ECU_LAYER_FLEX_SENSOR_H_
#include <_1_MCAL_Layer/ADC/ADC.h>
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include <_1_MCAL_Layer/UART/UART.h>
#include <_1_MCAL_Layer/EEPROM/EEPROM.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

#define TIRE_PRESSURE_THRESHOLD         10                         /* Engine temperature threshold */
#define DTC_TIRE_PRESSURE                 "P007"                     /* Diagnostic code for ENGINE_HIGH_TEMPERATURE */
#define PRESSURE_ERROR                    "ENGINE_LOW_PRESSURE"  /* Error description that the engine temperature > 90 degree C*/

uint32 Get_Pressure(void);
void Monitor_Pressure(void);
void Display_Pressure(void);



#endif /* 2_ECU_LAYER_FLEX_SENSOR_FLEX_SENSOR_H_ */
