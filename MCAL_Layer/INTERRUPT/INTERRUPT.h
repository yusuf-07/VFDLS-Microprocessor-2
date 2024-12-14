/*
 * INTERRUPT.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#ifndef MCAL_LAYER_INTERRUPT_INTERRUPT_H_
#define MCAL_LAYER_INTERRUPT_INTERRUPT_H_

/*-----------------------Includes-----------------------*/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "ECU_Layer/Ultrasonic/ULTRASONIC.h"
#include "ECU_Layer/DC_MOTOR/DC_MOTOR_TYPES.h"
#include "ECU_Layer/DC_MOTOR/DC_MOTOR.h"

/*------------------Macros Declarations------------------*/

/*-------------Macros Functions Declarations-------------*/


/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/
void GPIOPortA_Handler(void);
void GPIOPortB_Handler(void);
void GPIOPortC_Handler(void);
void GPIOPortD_Handler(void);
void GPIOPortE_Handler(void);
void GPIOPortF_Handler(void);


#endif /* MCAL_LAYER_INTERRUPT_INTERRUPT_H_ */
