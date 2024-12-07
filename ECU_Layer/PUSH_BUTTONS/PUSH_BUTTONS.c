/***
==================================================================================
* @file     : PUSH_BUTTONS.c
* @author   : Rawan
* @version  : v1.2
* @brief    : Push Buttons Driver Source File
* @details  : Implements initialization for push buttons and checks individual button status
==================================================================================
***/

/*** ===================== Include Section Start =========================== ***/
#include "PUSH_BUTTONS.h"
/*** ===================== Include Section End ============================= ***/

/*** ================ Sub-program Details Section Start ==================== ***/

/***
* @brief    : Initializes push buttons SW1 and SW2 on PORTF (PF0, PF4) and PORTB (PB0, PB1)
* @param    : None
* @return   : None
***/
void PUSH_BUTTONS_INIT(void)
{
    /* Enable clock for PORTF and PORTB and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= ((1<<5)|(1<<1));
    while((GET_BIT(SYSCTL_PRGPIO_REG,5) == 0) && (GET_BIT(SYSCTL_PRGPIO_REG,1) == 0));

    /* Unlocking the commit register to access PF0 */
    GPIO_PORTF_LOCK_REG = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG  |= (1<<0);        /* Enable changes on PF0 */

    /* Initializing SW1 on PF4 and SW2 on PF0 */
    GPIO_PORTF_AMSEL_REG &= ~((1<<4)|(1<<0));      /* Disable Analog on PF4 and PF0 */
    GPIO_PORTF_PCTL_REG  &= 0xFFF0FFF0;            /* Clear PMCx bits for PF4 & PF0 to use them as GPIO pins */
    GPIO_PORTF_DIR_REG   &= ~((1<<4)|(1<<0));      /* Configure PF4 & PF0 as input pins */
    GPIO_PORTF_AFSEL_REG &= ~((1<<4)|(1<<0));      /* Disable alternate function on PF4 & PF0 */
    GPIO_PORTF_PUR_REG   |= ((1<<4)|(1<<0));       /* Enable pull-up on PF4 & PF0 */
    GPIO_PORTF_DEN_REG   |= ((1<<4)|(1<<0));       /* Enable Digital I/O on PF4 & PF0 */

    /* Initializing SW1 on PB0 and SW2 on PB1 */
    GPIO_PORTB_AMSEL_REG &= ~((1<<1)|(1<<0));      /* Disable Analog on PB1 and PB0 */
    GPIO_PORTB_PCTL_REG  &= 0xFFFFFF00;            /* Clear PMCx bits for PB0 & PB1 to use them as GPIO pins */
    GPIO_PORTB_DIR_REG   &= ~((1<<1)|(1<<0));      /* Configure PB1 & PB0 as input pins */
    GPIO_PORTB_AFSEL_REG &= ~((1<<1)|(1<<0));      /* Disable alternate function on PB1 & PB0 */
    GPIO_PORTB_PUR_REG   |= ((1<<1)|(1<<0));       /* Enable pull-up on PB1 & PB0 */
    GPIO_PORTB_DEN_REG   |= ((1<<1)|(1<<0));       /* Enable Digital I/O on PB1 & PB0 */
}

/***
* @brief    : Read the state of the specified push button
* @param    : button - Button identifier (PB_SW0, PB_SW1, PB_SW2, PB_SW3)
* @return   : PB_PRESSED (0x00) or PB_RELEASED (0x01)
***/
uint8 PUSH_BUTTON_STATUS(uint8 button)
{
    switch (button)
    {
        case PB_SW0:
            if (GET_BIT(GPIO_PORTF_DATA_REG, 4) == 0)   /* PF4 (SW1) is pressed */
                return PB_PRESSED;
            break;

        case PB_SW1:
            if (GET_BIT(GPIO_PORTF_DATA_REG, 0) == 0)   /* PF0 (SW2) is pressed */
                return PB_PRESSED;
            break;

        case PB_SW2:
            if (GET_BIT(GPIO_PORTB_DATA_REG, 0) == 0)   /* PB0 is pressed */
                return PB_PRESSED;
            break;

        case PB_SW3:
            if (GET_BIT(GPIO_PORTB_DATA_REG, 1) == 0)   /* PB1 is pressed */
                return PB_PRESSED;
            break;

        default:
            return PB_RELEASED;  /* In case of invalid button ID */
    }
    return PB_RELEASED;  /* Default return when no button is pressed */
}

/*** ================ Sub-program Details Section End ====================== ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       07Dec24     Created Push Buttons Source File
Yusuf       07Dec24     Created Push Button Status Function
**/
