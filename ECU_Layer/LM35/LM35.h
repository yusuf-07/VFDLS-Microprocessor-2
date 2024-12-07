/*
 * LM35.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#ifndef ECU_LAYER_LM35_LM35_H_
#define ECU_LAYER_LM35_LM35_H_

/*-----------------------Includes-----------------------*/
#include "MCAL_Layer/MCAL_STD_TYPES.h"

/*------------------Macros Declarations------------------*/

/*-------------Macros Functions Declarations-------------*/

/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/
void LM35_INIT(void);
uint8 LM35_GET_TEMP(void);

#endif /* ECU_LAYER_LM35_LM35_H_ */
