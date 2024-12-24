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
#include <_1_MCAL_Layer/GPIO/GPIO.h>
#include <_1_MCAL_Layer/INTERRUPT/INTERRUPT.h>
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include <_1_MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
#include <_1_MCAL_Layer/UART/UART.h>
#include <_1_MCAL_Layer/EEPROM/EEPROM.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* Ultrasonic Pin Definitions */
#define ULTRASONIC_TRIGGER_PORT   GPIO_PORTE
#define ULTRASONIC_TRIGGER_PIN    4

#define ULTRASONIC_ECHO_PORT      GPIO_PORTE
#define ULTRASONIC_ECHO_PIN       5

/* Interrupt Configuration for Port B */
#define GPIO_PORTC_PRIORITY_MASK          0x0000E000
#define GPIO_PORTC_PRIORITY_BITS_POS      13
#define GPIO_PORTC_INTERRUPT_PRIORITY     2

/* Macros used foe error logging */
#define DISTANCE_THRESHOLD          1                         /* Distance threshold */
#define DTC_DISTANCE               "P001"                     /* Diagnostic code for ACCIDENT_MIGHT_HAPPEN */
#define DIST_ERROR                 "ACCIDENT_MIGHT_HAPPEN"   /* Error description that the Distance < 10cm*/


/* Enable Exceptions Macro */
#define Enable_Exceptions()    __asm(" CPSIE I ")
/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void Ultrasonic_Init(void);
void Ultrasonic_Trigger(void);
uint32 Ultrasonic_GetDistance(void);
void Monitor_DIST(void);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* ULTRASONIC_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created Ultrasonic Driver Header File
Yusuf       09Dec24     Updated with SysTick and GPIO Interrupts
**/
