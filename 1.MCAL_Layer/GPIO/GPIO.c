/***
==================================================================================
* @file     : GPIO.c
* @author   : Yusuf Abulfotouh
* @version  : v1.0
* @brief    : GPIO Driver Source File
* @details  : Implements initialization, pull configuration, logic setting, and reading
==================================================================================
***/

#include <1.MCAL_Layer/GPIO/GPIO.h>

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
* @brief    : Initializes a GPIO pin with specific settings
* @param    : port - GPIO port (e.g., GPIO_PORTA)
* @param    : pin - Pin number (0-7)
* @param    : type - GPIO type (GPIO_DIGITAL, GPIO_ANALOG)
* @param    : direction - Direction (GPIO_INPUT, GPIO_OUTPUT)
* @param    : alt_func - Alternative function select number (0 for no alt function)
* @return   : None
***/
void GPIO_Init(GPIO_Port_t port, uint8 pin, GPIO_Type_t type, GPIO_Direction_t direction, uint8 alt_func)
{
    /* Enable clock for the selected port and wait for stabilization */
    SYSCTL_RCGCGPIO_REG |= (1 << port);
    while (!((SYSCTL_PRGPIO_REG >> port) & 1));

    if (type == GPIO_DIGITAL)
    {
        SET_BIT(*DEN[port], pin);      /* Enable Digital Function */
        CLEAR_BIT(*AMSEL[port], pin);  /* Disable Analog Function */
    }
    else
    {
        CLEAR_BIT(*DEN[port], pin);    /* Disable Digital Function */
        SET_BIT(*AMSEL[port], pin);    /* Enable Analog Function */
    }

    if (alt_func != 0)
    {
        SET_BIT(*AFSEL[port], pin);   /* Enable Alternate Function */
        *PCTL[port] = (*PCTL[port] & ~(0xF << (pin * 4))) | (alt_func << (pin * 4)); /* Configure Alt Function */
    }
    else
    {
        CLEAR_BIT(*AFSEL[port], pin); /* Disable Alternate Function */
    }

    if (direction == GPIO_INPUT)
    {
        CLEAR_BIT(*DIR[port], pin);   /* Set pin as input */
    }
    else if (direction == GPIO_OUTPUT)
    {
        SET_BIT(*DIR[port], pin);     /* Set pin as output */
    }
}

/***
* @brief    : Configures pull-up or pull-down for a GPIO pin
* @param    : port - GPIO port
* @param    : pin - Pin number
* @param    : pull - Pull type (GPIO_PULL_UP, GPIO_PULL_DOWN, GPIO_NO_PULL)
* @return   : None
***/
void GPIO_PullConfig(GPIO_Port_t port, uint8 pin, GPIO_PullType_t pull)
{
    if (pull == GPIO_PULL_UP)
    {
        SET_BIT(*PUR[port], pin);
        CLEAR_BIT(*PDR[port], pin);
    }
    else if (pull == GPIO_PULL_DOWN)
    {
        SET_BIT(*PDR[port], pin);
        CLEAR_BIT(*PUR[port], pin);
    }
    else
    {
        CLEAR_BIT(*PUR[port], pin);
        CLEAR_BIT(*PDR[port], pin);
    }
}

/***
* @brief    : Sets the logic level of a GPIO pin
* @param    : port - GPIO port
* @param    : pin - Pin number
* @param    : logic - Logic level (HIGH, LOW)
* @return   : None
***/
void GPIO_DigitalWrite(GPIO_Port_t port, uint8 pin, GPIO_Logic_t logic)
{
    if (logic == HIGH)
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
uint8 GPIO_DigitalRead(GPIO_Port_t port, uint8 pin)
{
    return GET_BIT(*DATA[port], pin);
}

/*** ===================== Public Function Section End ==================== ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       08Dec24     Created GPIO Source File
Yusuf       16Dec24     Finished GPIO Driver Updates
**/
