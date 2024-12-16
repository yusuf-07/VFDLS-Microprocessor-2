/***
==================================================================================
* @file     : DC_MOTOR.c
* @author   : Maria George
* @version  : v1.2
* @brief    : DC Motor Driver Source File
* @details  : Implements initialization for DC Motor and checks individual button status
==================================================================================
==================================================================================
***/

/*** ===================== Include Section Start =========================== ***/
#include <_2_ECU_Layer/DC_MOTOR/DC_MOTOR.h>
/*** ===================== Include Section End ============================= ***/

/*** ================ Sub-program Details Section Start ==================== ***/

/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON For MOTOR A
 */
void DC_MOTORA_INIT(void){
    /***
     * Port B Pin 2 for IN1 (FORWARD)
     * Port B Pin 3 for IN2 (REVERSE)
     * Port B Pin 6 for ENA
     ***/
    //Enable clock for PortB and wait for clock to start
    SYSCTL_RCGCGPIO_REG |= (1<<1);
    while((GET_BIT(SYSCTL_PRGPIO_REG,1) == 0));

    GPIO_PORTB_AMSEL_REG &= ~((1<<IN1_PIN) | (1<<IN2_PIN) | (1<<ENA_PIN));       /* Disable Analog on PB2, PB3 and PB6 */
    GPIO_PORTB_PCTL_REG  &= 0xF0FF00FF;                                          /* Clear PMCx bits for PB2, PB3 and PB6 to use it as GPIO pin */
    GPIO_PORTB_DIR_REG   |= ((1<<IN1_PIN) | (1<<IN2_PIN) | (1<<ENA_PIN));        /* Configure PB2, PB3 and PB6 as output pin */
    GPIO_PORTB_AFSEL_REG &= ~((1<<IN1_PIN) | (1<<IN2_PIN) | (1<<ENA_PIN));       /* Disable alternative function on PB2, PB3 and PB6 */
    GPIO_PORTB_DEN_REG   |= ((1<<IN1_PIN) | (1<<IN2_PIN) | (1<<ENA_PIN));        /* Enable Digital I/O on PB2, PB3 and PB6 */
    GPIO_PORTB_DATA_REG  &= ~((1<<IN1_PIN) | (1<<IN2_PIN));       /* Clear bit 2, 3 and 6 in Data register to turn off DC Motor*/

    GPIO_PORTB_DATA_REG |= (1<<ENA_PIN); //To enable the H-Bridge
}

/**
 * @brief Move MOTOR A to the right or left direction
 * @param DCdir TO set direction to right or left
 */
void DC_MOTORA_START(DC_DIR_T DCdir){
    //INPUT1 (PB2)= 1 && INPUT2 (PB3) = 0 -> FPRWARD
    //INPUT1 (PB2) = 0 && INPUT2 (PB3) = 1 -> BACKWARD
    switch(DCdir){
        case DIR_CW :
            GPIO_PORTB_DATA_REG |= (1<<IN1_PIN);    //IN1 = 1 (Forward on)
            GPIO_PORTB_DATA_REG &= ~ (1<<IN2_PIN);  //IN2 = 0 (Reverse off)
            break;
        case DIR_CCW :
            GPIO_PORTB_DATA_REG &= ~ (1<<IN1_PIN);    //IN1 = 0 (Forward off)
            GPIO_PORTB_DATA_REG |= (1<<IN2_PIN);      //IN2 = 1 (Reverse on)
            break;
        default:
            GPIO_PORTB_DATA_REG &= ~ (1<<IN1_PIN);    //IN1 = 0 (Forward off)
            GPIO_PORTB_DATA_REG &= ~ (1<<IN2_PIN);    //IN2 = 0 (Reverse off)
            break;
        }
}

/**
 * @brief Stop MOTOR A
 */
void DC_MOTORA_STOP(void){
    //To stop MOTOR A IN1 = 0, IN2 = 0
    GPIO_PORTB_DATA_REG &= ~ (1<<IN1_PIN);    //IN1 = 0 (Forward off)
    GPIO_PORTB_DATA_REG &= ~ (1<<IN2_PIN);    //IN2 = 0 (Reverse off)
}


/**
 * @brief Initialize the assigned pins to be OUTPUT and turn the motor OFF or ON For MOTOR B
 */
void DC_MOTORB_INIT(void){
    /***
     * Port B Pin 4 for IN3 (FORWARD)
     * Port B Pin 5 for IN4 (REVERSE)
     * Port B Pin 7 for ENB
     ***/
    //Enable clock for PortB and wait for clock to start
    SYSCTL_RCGCGPIO_REG |= (1<<1);
    while((GET_BIT(SYSCTL_PRGPIO_REG,1) == 0));

    GPIO_PORTB_AMSEL_REG &= ~((1<<IN3_PIN) | (1<<IN4_PIN) | (1<<ENB_PIN));       /* Disable Analog on PB4, PB5 and PB7 */
    GPIO_PORTB_PCTL_REG  &= 0x0F00FFFF;                                          /* Clear PMCx bits for PB4, PB5 and PB7 to use it as GPIO pin */
    GPIO_PORTB_DIR_REG   |= ((1<<IN3_PIN) | (1<<IN4_PIN) | (1<<ENB_PIN));        /* Configure PB4, PB5 and PB7 as output pin */
    GPIO_PORTB_AFSEL_REG &= ~((1<<IN3_PIN) | (1<<IN4_PIN) | (1<<ENB_PIN));       /* Disable alternative function on PB4, PB5 and PB7 */
    GPIO_PORTB_DEN_REG   |= ((1<<IN3_PIN) | (1<<IN4_PIN) | (1<<ENB_PIN));        /* Enable Digital I/O on PB4, PB5 and PB7 */
    GPIO_PORTB_DATA_REG  &= ~((1<<IN3_PIN) | (1<<IN4_PIN));       /* Clear bit 4, 5 and 7 in Data register to turn off DC Motor*/

    GPIO_PORTB_DATA_REG |= (1<<ENB_PIN); //To enable the H-Bridge
}

/**
 * @brief Move MOTOR B to the right or left direction
 * @param DCdir TO set direction to right or left
 */
void DC_MOTORB_START(DC_DIR_T DCdir){
    //INPUT3 = 1 && INPUT4 = 0 -> FPRWARD
    //INPUT3 = 0 && INPUT4 = 1 -> BACKWARD
    switch(DCdir){
        case DIR_CW :
            GPIO_PORTB_DATA_REG |= (1<<IN3_PIN);    //IN3 = 1 (Forward on)
            GPIO_PORTB_DATA_REG &= ~ (1<<IN4_PIN);  //IN4 = 0 (Reverse off)
            break;
        case DIR_CCW :
            GPIO_PORTB_DATA_REG &= ~ (1<<IN3_PIN);    //IN3 = 0 (Forward off)
            GPIO_PORTB_DATA_REG |= (1<<IN4_PIN);      //IN4 = 1 (Reverse on)
            break;
        default:
            GPIO_PORTB_DATA_REG &= ~ (1<<IN3_PIN);    //IN3 = 0 (Forward off)
            GPIO_PORTB_DATA_REG &= ~ (1<<IN4_PIN);    //IN4 = 0 (Reverse off)
            break;
        }
}

/**
 * @brief Stop MOTOR B
 */
void DC_MOTORB_STOP(void){
    //To stop MOTOR B IN3 = 0, IN4 = 0
    GPIO_PORTB_DATA_REG &= ~ (1<<IN3_PIN);    //IN3 = 0 (Forward off)
    GPIO_PORTB_DATA_REG &= ~ (1<<IN4_PIN);    //IN4 = 0 (Reverse off)
}

/*** ================ Sub-program Details Section End ====================== ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Maria       07Dec24     Created DC Motor Source File
**/

