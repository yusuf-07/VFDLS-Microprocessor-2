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
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* SysTick Configuration Macros */
#define SYSTICK_DISABLE            0
#define SYSTICK_ENABLE             0x00000001
#define SYSTICK_CLK_SRC_SYSTEM     0x00000004
#define SYSTICK_CTRL_COUNT         0x00010000
#define SYSTICK_INT_DISABLE        0x00
#define SYSTICK_MAX_RELOAD_VALUE   ((0xFFFFFF))

#define NVIC_ST_CTRL_COUNT      0x00010000
#define NVIC_ST_CTRL_CLK_SRC    0x00000004
#define NVIC_ST_CTRL_ENABLE     0x00000001
#define NVIC_ST_RELOAD_M        0x00FFFFFF

#define _delay_sys_1us             (1/1000)
#define _delay_sys_1ms             1
#define _delay_sys_2ms             2
#define _delay_sys_5ms             5
#define _delay_sys_50ms            50
#define _delay_sys_500ms           500
#define _delay_sys_1s              1000
/*** ====================== Macros Section End ============================= ***/


/*** ================= Global Declaration Section Start ==================== ***/
void SysTick_Init(void);
void SysTick_DelayMs(uint32 delay_in_ms);
void SysTick_DelayUs(uint32 delay_in_us);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* SYSTICK_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       07Dec24     Created SysTick Header File
**/
