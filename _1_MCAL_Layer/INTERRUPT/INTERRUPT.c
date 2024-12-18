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

/*** ===================== Global Variables Section Start ====================== ***/
extern volatile uint32 pulse_start;
extern volatile uint32 pulse_end;
extern volatile uint8 edge_detected;
extern volatile uint32 measured_distance;
/*** ===================== Global Variables Section End ======================== ***/


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
//    if(GET_BIT(GPIO_PORTB_RIS_REG,ULTRASONIC_ECHO_PIN) == 1)
//    {
//        if (edge_detected == 0)
//        {
//            pulse_start = SYSTICK_CURRENT_REG;             /* Capture rising edge time */
//            GPIO_PORTB_IEV_REG &= ~(1 << ULTRASONIC_ECHO_PIN); /* Switch to Falling Edge */
//            edge_detected = 1;
//        }
//        else
//        {
//            pulse_end = SYSTICK_CURRENT_REG;              /* Capture falling edge time */
//            GPIO_PORTB_IEV_REG |= (1 << ULTRASONIC_ECHO_PIN);  /* Switch to Rising Edge */
//            edge_detected = 0;
//
//            /* Calculate distance in cm */
//            uint32 pulse_width = pulse_start - pulse_end;
//            measured_distance = (pulse_width * 0.034) / 2; /* Speed of sound = 0.034 cm/us */
//        }
//
//        GPIO_PORTB_ICR_REG |= (1 << ULTRASONIC_ECHO_PIN); /* Clear interrupt flag */
//    }
//    else if(GET_BIT(GPIO_PORTB_RIS_REG,0) == 1){             /* check if SW2 on PB0  is pressed*/
//
//        DC_MOTORB_START(DIR_CCW);                            /* Start Motor B counterclockwise*/
//
//        while(GET_BIT(GPIO_PORTB_DATA_REG, 0) == 0);         /* Busy-waiting until the switch is released */
//        DC_MOTORB_STOP();                                    /* Stop Motor B */
//        GPIO_PORTB_ICR_REG |= (1 << 0);                      /* Clear interrupt flag */
//    }
//    else if(GET_BIT(GPIO_PORTB_RIS_REG,1) == 1){             /* check if SW3 on PB1  is pressed*/
//
//        DC_MOTORB_START(DIR_CW);                            /* Start Motor B clockwise*/
//
//        while(GET_BIT(GPIO_PORTB_DATA_REG, 1) == 0);         /* Busy-waiting until the switch is released */
//        DC_MOTORB_STOP();                                    /* Stop Motor B */
//        GPIO_PORTB_ICR_REG |= (1 << 1);                      /* Clear interrupt flag */
//    }
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
    if(GET_BIT(GPIO_PORTF_RIS_REG,4) == 1){                  /* check if SW0 on PF4  is pressed*/

        DC_MOTORA_START(DIR_CCW);                            /* Start Motor A counterclockwise*/

        while(GET_BIT(GPIO_PORTF_DATA_REG, 4) == 0);         /* Busy-waiting until the switch is released */
        DC_MOTORA_STOP();                                    /* Stop Motor A */
        GPIO_PORTF_ICR_REG |= (1 << 4);                      /* Clear interrupt flag */
    }
    else if(GET_BIT(GPIO_PORTF_RIS_REG,0) == 1){             /* check if SW1 on PF0 is pressed*/

        DC_MOTORA_START(DIR_CW);                            /* Start Motor A clockwise*/

        while(GET_BIT(GPIO_PORTF_DATA_REG, 0) == 0);         /* Busy-waiting until the switch is released */
        DC_MOTORA_STOP();                                    /* Stop Motor A */
        GPIO_PORTF_ICR_REG |= (1 << 0);                      /* Clear interrupt flag */
    }
}


/**
*******************************************************
User        Date        Brief
*******************************************************
Rawan       14Dec24     Created Interrupt Source File
Yusuf       16Dec24     Added Ultrasonic to PortB_Handler
**/
