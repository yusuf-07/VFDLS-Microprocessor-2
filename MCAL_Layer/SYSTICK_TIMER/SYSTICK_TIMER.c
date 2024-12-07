/***
==================================================================================
* @file     : SYSTICK_TIMER.c
* @author   : Yusuf Abulfotouh
* @version  :
* @brief    : SysTick Timer Driver Source File
* @details  : Implements SysTick initialization and delay functions
==================================================================================
***/

/*** ===================== Include Section Start =========================== ***/
#include "SYSTICK_TIMER.h"
/*** ===================== Include Section End ============================= ***/


/*** ================ Sub-program Details Section Start ==================== ***/

/***
* @brief    : Initialize the SysTick Timer
* @param    : reload_value - The reload value for the timer
* @return   : None
***/
void SysTick_Init(uint32_t reload_value)
{
    SYSTICK_CTRL_REG = SYSTICK_DISABLE;                /* Disable SysTick Timer */
    SYSTICK_RELOAD_REG = reload_value & SYSTICK_MAX_RELOAD_VALUE; /* Set Reload Value */
    SYSTICK_CURRENT_REG = 0;                           /* Clear Current Value */
    SYSTICK_CTRL_REG = SYSTICK_ENABLE | SYSTICK_CLK_SRC_SYSTEM; /* Enable SysTick */
}

/***
* @brief    : Create a delay using SysTick Timer
* @param    : delay_in_ms - Delay duration in milliseconds
* @return   : None
***/
void SysTick_DelayMs(uint32_t delay_in_ms)
{
    uint32_t ticks = delay_in_ms * 16000; /* Assuming 16 MHz clock */
    SysTick_Init(ticks);

    while(!(SYSTICK_CTRL_REG & (1 << 16))) /* Wait for COUNT flag */
    {
        /* Busy wait */
    }
}

/*** ================ Sub-program Details Section End ====================== ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       07Dec24     Created SysTick Source File
**/
