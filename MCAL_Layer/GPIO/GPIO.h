/***
==================================================================================
* @file     : GPIO.h
* @author   : Yusuf
* @version  : v1.0
* @brief    : GPIO Driver Header File
* @details  : Provides macros, data types, and function prototypes for GPIO operations
==================================================================================
***/

#ifndef GPIO_H_
#define GPIO_H_

/*** ===================== Include Section Start =========================== ***/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
typedef enum {
    GPIO_PORTA,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTF
} GPIO_Port_t;

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT,
    GPIO_INPUT_PULLUP,
    GPIO_INPUT_PULLDOWN
} GPIO_Direction_t;

typedef enum {
    GPIO_LOW,
    GPIO_HIGH
} GPIO_Logic_t;
/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void GPIO_InitPin(GPIO_Port_t port, uint8 pin, GPIO_Direction_t direction);
void GPIO_SetPinLogic(GPIO_Port_t port, uint8 pin, GPIO_Logic_t logic);
uint8 GPIO_GetPinLogic(GPIO_Port_t port, uint8 pin);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* GPIO_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created GPIO Header File
**/
