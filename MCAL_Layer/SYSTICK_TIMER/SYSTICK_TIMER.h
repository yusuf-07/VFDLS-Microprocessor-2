/***
==================================================================================
* @file     : SYSTICK_TIMER.h
* @author   : Yusuf Abulfotouh
* @version  : v1.0
* @brief    : SysTick Timer Driver Header File
* @details  : Provides macros and function prototypes for SysTick Timer operations
==================================================================================
***/

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*** ===================== Include Section Start =========================== ***/
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* SysTick Configuration Macros */
#define SYSTICK_DISABLE            0
#define SYSTICK_ENABLE             0x01
#define SYSTICK_CLK_SRC_SYSTEM     0x04
#define SYSTICK_INT_DISABLE        0x00
#define SYSTICK_MAX_RELOAD_VALUE   0xFFFFFF
/*** ====================== Macros Section End ============================= ***/


/*** ================= Global Declaration Section Start ==================== ***/
void SysTick_Init(uint32_t reload_value);
void SysTick_DelayMs(uint32_t delay_in_ms);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* SYSTICK_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       07Dec24     Created SysTick Header File
**/
