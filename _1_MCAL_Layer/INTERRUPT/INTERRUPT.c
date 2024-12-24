/***
==================================================================================
* @file     : INTERRUPT.c
* @author   : Rawan
* @version  : v1.0
* @brief    : Interrupt Service Routine Source File
* @details  : Implements GPIO interrupt handlers for various ports
==================================================================================
***/

#include <_1_MCAL_Layer/INTERRUPT/INTERRUPT.h>
#include <_2_ECU_Layer/LCD/LCD.h>
static volatile uint8 motorA_state;  // 0: Stop, 1: Start CCW, 2: Start CW
static volatile uint8 motorB_state;  // 0: Stop, 1: Start CCW, 2: Start CW
static volatile uint8 motor_active;
static volatile uint8 motorA_flag;
static volatile uint8 motorB_flag;
/*** ===================== Public Function Section Start ===================== ***/
/***
* @brief    : GPIO Interrupt Handler for Port A
* @param    : None
* @return   : None
***/
void GPIOPortA_Handler(void)
{
    while(1)
    {
        /* Placeholder for Port A ISR logic */
    }
}

/***
* @brief    : GPIO Interrupt Handler for Port B
* @param    : None
* @return   : None
***/

void GPIOPortB_Handler(void)
{
    if (GET_BIT(GPIO_PORTB_RIS_REG, 0) == 1) { /* Check if SW2 on PB0 is pressed */
        DC_MOTORB_START(DIR_CCW);             /* Start Motor B counterclockwise */
        //motorA_state = 1;
        LCD_4BITS_send_string_position("W2-Close", 2, 9);
        /* Wait for button release */
        while (GET_BIT(GPIO_PORTB_DATA_REG, 0) == 0);

        DC_MOTORB_STOP();                     /* Stop Motor B */

        GPIO_PORTB_ICR_REG |= (1 << 0);       /* Clear interrupt flag */
    }

    if (GET_BIT(GPIO_PORTB_RIS_REG, 1) == 1) { /* Check if SW3 on PB1 is pressed */
        DC_MOTORB_START(DIR_CW);              /* Start Motor B clockwise */
        //motorA_state = 2;
        LCD_4BITS_send_string_position("W2-Open", 2, 9);

        /* Wait for button release */
        while (GET_BIT(GPIO_PORTB_DATA_REG, 1) == 0);

        DC_MOTORB_STOP();                     /* Stop Motor B */
        GPIO_PORTB_ICR_REG |= (1 << 1);       /* Clear interrupt flag */
    }
}

/***
* @brief    : GPIO Interrupt Handler for Port C
* @param    : None
* @return   : None
***/
void GPIOPortC_Handler(void)
{
    while(1)
    {
        /* Placeholder for Port C ISR logic */
    }
}

/***
* @brief    : GPIO Interrupt Handler for Port D
* @param    : None
* @return   : None
***/
void GPIOPortD_Handler(void)
{
    while(1)
    {
        /* Placeholder for Port D ISR logic */
    }
}

/***
* @brief    : GPIO Interrupt Handler for Port E
* @param    : None
* @return   : None
***/
void GPIOPortE_Handler(void)
{
    while(1)
    {
        /* Placeholder for Port E ISR logic */
    }
}

/***
* @brief    : GPIO Interrupt Handler for Port F
* @param    : None
* @return   : None
***/
void GPIOPortF_Handler(void)
{
    if (GET_BIT(GPIO_PORTF_RIS_REG, 4) == 1) { /* Check if SW0 on PF4 is pressed */
        DC_MOTORA_START(DIR_CCW);             /* Start Motor A counterclockwise */
        // Display motor statuses
        LCD_4BITS_send_string_position("W1-Close", 1, 9);

        /* Wait for button release */
        while (GET_BIT(GPIO_PORTF_DATA_REG, 4) == 0);

        DC_MOTORA_STOP();                     /* Stop Motor A */
        GPIO_PORTF_ICR_REG |= (1 << 4);       /* Clear interrupt flag */
    }

    if (GET_BIT(GPIO_PORTF_RIS_REG, 0) == 1) { /* Check if SW1 on PF0 is pressed */
        DC_MOTORA_START(DIR_CW);              /* Start Motor A clockwise */
        LCD_4BITS_send_string_position("W1-Open", 1, 9);

        /* Wait for button release */
        while (GET_BIT(GPIO_PORTF_DATA_REG, 0) == 0);

        DC_MOTORA_STOP();                     /* Stop Motor A */
        GPIO_PORTF_ICR_REG |= (1 << 0);       /* Clear interrupt flag */
    }
}

/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       14Dec24     Created Interrupt Source File
Yusuf       16Dec24     Added Ultrasonic to PortB_Handler
**/
