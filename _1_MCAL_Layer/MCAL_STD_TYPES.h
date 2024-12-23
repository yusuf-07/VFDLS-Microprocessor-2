/*
 * MCAL_STD_TYPES.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#ifndef _1_MCAL_LAYER_MCAL_STD_TYPES_H_
#define _1_MCAL_LAYER_MCAL_STD_TYPES_H_
/*-----------------------Includes-----------------------*/
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"

/*------------------Macros Declarations------------------*/
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define CONFIG_ENABLE   0x01
#define CONFIG_DISABLE  0x00

/*-------------Macros Functions Declarations-------------*/

/*-----------------Data Type Declarations-----------------*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

/*AUTOSAR STD TYPES P.17*/
typedef uint8 Std_ReturnType;
#define E_OK      (Std_ReturnType)0x01
#define E_NOT_OK  (Std_ReturnType)0x00

/*-----------------Functions Declarations-----------------*/

#endif /* _1_MCAL_LAYER_MCAL_STD_TYPES_H_ */
