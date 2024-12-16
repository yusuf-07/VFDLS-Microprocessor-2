/*
 * ADC.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Rawan Waleed
 */

#ifndef MCAL_LAYER_ADC_ADC_H_
#define MCAL_LAYER_ADC_ADC_H_

/*-----------------------Includes-----------------------*/
#include "1.MCAL_Layer/MCAL_STD_TYPES.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*------------------Macros Declarations------------------*/


/*-------------Macros Functions Declarations-------------*/


/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/

void ADC0_Init(void);
uint32 ADC0_ReadSeq3(void);

#endif /* MCAL_LAYER_ADC_ADC_H_ */
