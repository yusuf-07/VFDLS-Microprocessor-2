/*
 * ADC.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#ifndef MCAL_LAYER_ADC_ADC_H_
#define MCAL_LAYER_ADC_ADC_H_

/*-----------------------Includes-----------------------*/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "ADC_TYPES.h"

/*------------------Macros Declarations------------------*/


/*-------------Macros Functions Declarations-------------*/


/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/

void ADC_INIT(void);
void ADC_READ_CHANNEL(adc_channelId_t channel);

#endif /* MCAL_LAYER_ADC_ADC_H_ */
