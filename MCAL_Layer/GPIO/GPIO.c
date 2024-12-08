/***
==================================================================================
* @file     : GPIO.c
* @author   : Yusuf
* @version  : v1.0
* @brief    : GPIO Driver Source File
* @details  : Implements initialization, logic setting, and reading for GPIO pins
==================================================================================
***/

#include "gpio.h"

/*** ===================== Private Variables Section Start ================= ***/
static volatile unsigned long * const DEN[6]   = {&GPIO_PORTA_DEN_REG,
                                                  &GPIO_PORTB_DEN_REG,
                                                  &GPIO_PORTC_DEN_REG,
                                                  &GPIO_PORTD_DEN_REG,
                                                  &GPIO_PORTE_DEN_REG,
                                                  &GPIO_PORTF_DEN_REG};

static volatile unsigned long * const AMSEL[6] = {&GPIO_PORTA_AMSEL_REG,
                                                  &GPIO_PORTB_AMSEL_REG,
                                                  &GPIO_PORTC_AMSEL_REG,
                                                  &GPIO_PORTD_AMSEL_REG,
                                                  &GPIO_PORTE_AMSEL_REG,
                                                  &GPIO_PORTF_AMSEL_REG};

static volatile unsigned long * const AFSEL[6] = {&GPIO_PORTA_AFSEL_REG,
                                                  &GPIO_PORTB_AFSEL_REG,
                                                  &GPIO_PORTC_AFSEL_REG,
                                                  &GPIO_PORTD_AFSEL_REG,
                                                  &GPIO_PORTE_AFSEL_REG,
                                                  &GPIO_PORTF_AFSEL_REG};

static volatile unsigned long * const PCTL[6]  = {&GPIO_PORTA_PCTL_REG,
                                                  &GPIO_PORTB_PCTL_REG,
                                                  &GPIO_PORTC_PCTL_REG,
                                                  &GPIO_PORTD_PCTL_REG,
                                                  &GPIO_PORTE_PCTL_REG,
                                                  &GPIO_PORTF_PCTL_REG};

static volatile unsigned long * const DIR[6]   = {&GPIO_PORTA_DIR_REG,
                                                  &GPIO_PORTB_DIR_REG,
                                                  &GPIO_PORTC_DIR_REG,
                                                  &GPIO_PORTD_DIR_REG,
                                                  &GPIO_PORTE_DIR_REG,
                                                  &GPIO_PORTF_DIR_REG};

static volatile unsigned long * const PUR[6]   = {&GPIO_PORTA_PUR_REG,
                                                  &GPIO_PORTB_PUR_REG,
                                                  &GPIO_PORTC_PUR_REG,
                                                  &GPIO_PORTD_PUR_REG,
                                                  &GPIO_PORTE_PUR_REG,
                                                  &GPIO_PORTF_PUR_REG};

static volatile unsigned long * const PDR[6]   = {&GPIO_PORTA_PDR_REG,
                                                  &GPIO_PORTB_PDR_REG,
                                                  &GPIO_PORTC_PDR_REG,
                                                  &GPIO_PORTD_PDR_REG,
                                                  &GPIO_PORTE_PDR_REG,
                                                  &GPIO_PORTF_PDR_REG};

static volatile unsigned long * const DATA[6]  = {&GPIO_PORTA_DATA_REG,
                                                  &GPIO_PORTB_DATA_REG,
                                                  &GPIO_PORTC_DATA_REG,
                                                  &GPIO_PORTD_DATA_REG,
                                                  &GPIO_PORTE_DATA_REG,
                                                  &GPIO_PORTF_DATA_REG};
/*** ===================== Private Variables Section End =================== ***/

/*** ===================== Public Function Section Start ================== ***/

/***
* @brief    : Initializes a GPIO pin with the specified direction
* @param    : port - GPIO port (e.g., GPIO_PORTA)
* @param    : pin - Pin number (0-7)
* @param    : direction - Direction (GPIO_INPUT, GPIO_OUTPUT, etc.)
* @return   : None
***/
void GPIO_InitPin(GPIO_Port_t port, uint8 pin, GPIO_Direction_t direction)
{
    SYSCTL_RCGCGPIO_REG |= (1 << port);      /* Enable clock for the selected port */
    while (!((SYSCTL_PRGPIO_REG >> port) & 1));

    SET_BIT(*DEN[port], pin);                /* Enable Digital Function */
    CLEAR_BIT(*AMSEL[port], pin);            /* Disable Analog Function */
    CLEAR_BIT(*AFSEL[port], pin);            /* Disable Alternate Function */
    CLEAR_BIT(*PCTL[port], pin);             /* Clear PCTL for GPIO */

    switch (direction)
    {
        case GPIO_INPUT:
            CLEAR_BIT(*DIR[port], pin);      /* Set pin as input */
            break;

        case GPIO_OUTPUT:
            SET_BIT(*DIR[port], pin);        /* Set pin as output */
            break;

        case GPIO_INPUT_PULLUP:
            CLEAR_BIT(*DIR[port], pin);      /* Set pin as input */
            SET_BIT(*PUR[port], pin);        /* Enable pull-up resistor */
            break;

        case GPIO_INPUT_PULLDOWN:
            CLEAR_BIT(*DIR[port], pin);      /* Set pin as input */
            SET_BIT(*PDR[port], pin);        /* Enable pull-down resistor */
            break;

        default:
            break;
    }
}

/***
* @brief    : Sets the logic level of a GPIO pin
* @param    : port - GPIO port
* @param    : pin - Pin number
* @param    : logic - Logic level (GPIO_HIGH, GPIO_LOW)
* @return   : None
***/
void GPIO_SetPinLogic(GPIO_Port_t port, uint8 pin, GPIO_Logic_t logic)
{
    if (logic == GPIO_HIGH)
    {
        SET_BIT(*DATA[port], pin);
    }
    else
    {
        CLEAR_BIT(*DATA[port], pin);
    }
}

/***
* @brief    : Reads the logic level of a GPIO pin
* @param    : port - GPIO port
* @param    : pin - Pin number
* @return   : Logic level (GPIO_HIGH, GPIO_LOW)
***/
uint8 GPIO_GetPinLogic(GPIO_Port_t port, uint8 pin)
{
    return GET_BIT(*DATA[port], pin);
}

/*** ===================== Public Function Section End ==================== ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created GPIO Source File
**/
