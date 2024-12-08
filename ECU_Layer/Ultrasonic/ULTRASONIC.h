/***
==================================================================================
* @file     : ULTRASONIC.h
* @author   : Yusuf Abulfotouh
* @version  : v1.1
* @brief    : Ultrasonic Sensor Driver Header File
* @details  : Provides macros, function prototypes, and configurations for the
*             ultrasonic sensor operations with interrupt-based distance measurement.
==================================================================================
***/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*** ===================== Include Section Start =========================== ***/
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* Ultrasonic Pin Definitions */
#define ULTRASONIC_TRIGGER_PORT   GPIO_PORTB_DATA_REG
#define ULTRASONIC_TRIGGER_PIN    5

#define ULTRASONIC_ECHO_PORT      GPIO_PORTB_DATA_REG
#define ULTRASONIC_ECHO_PIN       6

/* Fault Codes */
#define ULTRASONIC_FAULT_CODE      "P001"
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
**/
