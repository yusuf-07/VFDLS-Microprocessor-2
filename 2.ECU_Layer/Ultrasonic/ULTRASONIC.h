/***
==================================================================================
* @file     : ULTRASONIC.h
* @author   : Yusuf Abulfotouh
* @version  : v1.3
* @brief    : Ultrasonic Sensor Driver Header File
* @details  : Provides macros, function prototypes, and configurations for the
*             ultrasonic sensor operations using SysTick Timer and GPIO interrupts.
==================================================================================
***/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*** ===================== Include Section Start =========================== ***/
#include <1.MCAL_Layer/INTERRUPT/INTERRUPT.h>
#include <1.MCAL_Layer/MCAL_STD_TYPES.h>
#include <1.MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* Ultrasonic Pin Definitions */
#define ULTRASONIC_TRIGGER_PORT   GPIO_PORTB_DATA_REG
#define ULTRASONIC_TRIGGER_PIN    5

#define ULTRASONIC_ECHO_PORT      GPIO_PORTB_DATA_REG
#define ULTRASONIC_ECHO_PIN       6

/* Interrupt Configuration for Port B */
#define GPIO_PORTB_PRIORITY_MASK          0x0000E000
#define GPIO_PORTB_PRIORITY_BITS_POS      13
#define GPIO_PORTB_INTERRUPT_PRIORITY     2

/* Enable Exceptions Macro */
#define Enable_Exceptions()    __asm(" CPSIE I ")
/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void Ultrasonic_Init(void);
uint32 Ultrasonic_GetDistance(void);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* ULTRASONIC_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created Ultrasonic Driver Header File
Yusuf       09Dec24     Updated with SysTick and GPIO Interrupts
**/
