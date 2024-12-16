/*
 * ADC.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Rawan Waleed
 */

#ifndef 1_MCAL_LAYER_ADC_ADC_H_
#define 1_MCAL_LAYER_ADC_ADC_H_

/*-----------------------Includes-----------------------*/
#include <1.MCAL_Layer/ADC/ADC_TYPES.h>
#include <1.MCAL_Layer/MCAL_STD_TYPES.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*------------------Macros Declarations------------------*/


/*-------------Macros Functions Declarations-------------*/


/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/

void ADC_INIT(void);
void ADC_READ_CHANNEL(adc_channelId_t channel);

#endif /* 1_MCAL_LAYER_ADC_ADC_H_ */