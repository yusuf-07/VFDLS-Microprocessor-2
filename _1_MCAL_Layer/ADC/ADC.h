/*
 * ADC.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Rawan Waleed
 */

#ifndef _1_MCAL_LAYER_ADC_ADC_H_
#define _1_MCAL_LAYER_ADC_ADC_H_

/*-----------------------Includes-----------------------*/
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*------------------Macros Declarations------------------*/


/*-------------Macros Functions Declarations-------------*/


/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/

void ADC0_Init(void);
uint32 ADC0_ReadSeq3(void);

#endif /* _1_MCAL_LAYER_ADC_ADC_H_ */
