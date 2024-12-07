/***
==================================================================================
* @file     : SYSTICK_TIMER.c
* @author   : Yusuf Abulfotouh
* @version  :
* @brief    : SysTick Timer Driver Source File
* @details  : Implements SysTick initialization, millisecond, and microsecond delay functions
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
void SysTick_Init(uint32 reload_value)
{
    SYSTICK_CTRL_REG = SYSTICK_DISABLE;                /* Disable SysTick Timer */
    SYSTICK_RELOAD_REG = reload_value;                 /* Set Reload Value */
    SYSTICK_CURRENT_REG = 0;                           /* Clear Current Value */
    SYSTICK_CTRL_REG = SYSTICK_ENABLE | SYSTICK_CLK_SRC_SYSTEM; /* Enable SysTick */
}

/***
* @brief    : Create a delay using SysTick Timer in milliseconds
* @param    : delay_in_ms - Delay duration in milliseconds
* @return   : None
***/
void SysTick_DelayMs(uint32 delay_in_ms)
{
    uint32 ticks = ((delay_in_ms * 16000) - 1); /* Assuming 16 MHz clock */
    SysTick_Init(ticks);

    while(!(SYSTICK_CTRL_REG & (1 << 16))) /* Wait for COUNT flag */
    {
        /* Busy wait */
    }
}

/***
* @brief    : Create a delay using SysTick Timer in microseconds
* @param    : delay_in_us - Delay duration in microseconds
* @return   : None
***/
void SysTick_DelayUs(uint32 delay_in_us)
{
    uint32 ticks = ((delay_in_us * 16) - 1); /* Assuming 16 MHz clock */
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
Yusuf       07Dec24     Added Microsecond Delay Function
**/
