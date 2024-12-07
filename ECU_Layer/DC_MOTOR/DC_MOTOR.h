/*
 * DC_MOTOR.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#ifndef ECU_LAYER_DC_MOTOR_DC_MOTOR_H_
#define ECU_LAYER_DC_MOTOR_DC_MOTOR_H_

/*-----------------------Includes-----------------------*/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "DC_MOTOR_TYPES.h"

/*------------------Macros Declarations------------------*/

/*-------------Macros Functions Declarations-------------*/

/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/
void DC_MOTOR_INIT(void);
void DC_MOTOR_START(DC_MOTOR_T DCtype, DC_DIR_T DCdir);
void DC_MOTOR_STOP(DC_MOTOR_T DCtype);

#endif /* ECU_LAYER_DC_MOTOR_DC_MOTOR_H_ */
