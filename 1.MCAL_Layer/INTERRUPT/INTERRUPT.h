/***
==================================================================================
* @file     : INTERRUPT.h
* @author   : Rawan Waleed
* @version  : v1.0
* @brief    : Interrupt Service Routine Header File
* @details  : Provides macros and function prototypes for GPIO interrupt handlers
==================================================================================
***/

#ifndef 1_MCAL_LAYER_INTERRUPT_INTERRUPT_H_
#define 1_MCAL_LAYER_INTERRUPT_INTERRUPT_H_

/*** ===================== Include Section Start =========================== ***/
#include <1.MCAL_Layer/MCAL_STD_TYPES.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include <2.ECU_Layer/Ultrasonic/ULTRASONIC.h>
#include <2.ECU_Layer/DC_MOTOR/DC_MOTOR_TYPES.h>
#include <2.ECU_Layer/DC_MOTOR/DC_MOTOR.h>
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void GPIOPortA_Handler(void);
void GPIOPortB_Handler(void);
void GPIOPortC_Handler(void);
void GPIOPortD_Handler(void);
void GPIOPortE_Handler(void);
void GPIOPortF_Handler(void);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* 1_MCAL_LAYER_INTERRUPT_INTERRUPT_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       14Dec24     Created Interrupt Header File
**/
