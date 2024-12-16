/***
==================================================================================
* @file     : GPIO.h
* @author   : Yusuf Abulfotouh
* @version  : v1.0
* @brief    : GPIO Driver Header File
* @details  : Provides macros, data types, and function prototypes for GPIO operations
==================================================================================
***/

#ifndef GPIO_H_
#define GPIO_H_

/*** ===================== Include Section Start =========================== ***/
#include "1.MCAL_Layer/MCAL_STD_TYPES.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Enum Section Start =========================== ***/
typedef enum {
    GPIO_PORTA,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE,
    GPIO_PORTF
} GPIO_Port_t;

typedef enum {
    GPIO_DIGITAL,
    GPIO_ANALOG
} GPIO_Type_t;

typedef enum {
    GPIO_INPUT,
    GPIO_OUTPUT
} GPIO_Direction_t;

typedef enum {
    GPIO_NO_PULL,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} GPIO_PullType_t;

typedef enum {
    LOW,
    HIGH
} GPIO_Logic_t;
/*** ====================== Enum Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void GPIO_Init(GPIO_Port_t port, uint8 pin, GPIO_Type_t type, GPIO_Direction_t direction, uint8 alt_func);
void GPIO_PullConfig(GPIO_Port_t port, uint8 pin, GPIO_PullType_t pull);
void GPIO_DigitalWrite(GPIO_Port_t port, uint8 pin, GPIO_Logic_t logic);
uint8 GPIO_DigitalRead(GPIO_Port_t port, uint8 pin);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* GPIO_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created GPIO Header File
Yusuf       16Dec24     Updated GPIO Header File
**/
