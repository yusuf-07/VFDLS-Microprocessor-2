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
#include <_1_MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
/*** ===================== Include Section End ============================= ***/

/*** ================ Sub-program Details Section Start ==================== ***/

/***
* @brief    : Initialize the SysTick Timer
* @param    : reload_value - The reload value for the timer
* @return   : None
***/
void SysTick_Init(void)
{
    SYSTICK_CTRL_REG = SYSTICK_DISABLE;                /* Disable SysTick Timer */
    SYSTICK_RELOAD_REG = SYSTICK_MAX_RELOAD_VALUE;                 /* Set Reload Value */
    SYSTICK_CURRENT_REG = 0;                           /* Clear Current Value */
    SYSTICK_CTRL_REG = SYSTICK_ENABLE | SYSTICK_CLK_SRC_SYSTEM; /* Enable SysTick */
}

/***
* @brief    : Create a delay using SysTick Timer in milliseconds
* @param    : delay_in_ms - Delay duration in milliseconds
* @return   : None
***/
void SysTick_Delay(uint32 _delay_)
{
    SYSTICK_RELOAD_REG = ((_delay_) - 1); /* Assuming 16 MHz clock */
    SYSTICK_CURRENT_REG = 0;
    while ((SYSTICK_CTRL_REG & SYSTICK_CTRL_COUNT) == 0);
}

/***
* @brief    : Create a delay using SysTick Timer in microseconds
* @param    : delay_in_us - Delay duration in microseconds
* @return   : None
***/
void SysTick_DelayUs(uint32 delay_in_us)
{
    unsigned long i;                      // Declare the loop variable at the top
        for (i = 0; i < delay_in_us; i++)
        {
            SysTick_Delay(8);          // 10us delay at 16 MHz clock
        }
}
void SysTick_DelayMs(uint32 delay_in_ms)
{
    uint32 i; // Loop variable
    for (i = 0; i < delay_in_ms; i++)
    {
        SysTick_Delay(8000); // Delay 1 ms by calling SysTick_Delay(1000) for 1 µs delay
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
