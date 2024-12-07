/*
 * LCD.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#include "LCD.h"
]


/**
 * @brief
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
void LCD_4BITS_INIT(void){
    //Enable clock for PortD and PortE
    SYSCTL_RCGCGPIO_REG |= ((1<<3) | (1<<4));
    while (!(SYSCTL_PRGPIO_REG & ((1<<3) | (1<<4))));

    //Data lines->PD4-PD7
    GPIO_PORTD_AMSEL_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));       /* Disable Analog on PD4, PD5, PD6 and PD7 */
    GPIO_PORTD_PCTL_REG  &= 0x0000FFFF;                                                                 /* Clear PMCx bits for PD4, PD5, PD6 and PD7 to use it as GPIO pin */
    GPIO_PORTD_DIR_REG   |= ((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));        /* Configure PD4, PD5, PD6 and PD7 as output pin */
    GPIO_PORTD_AFSEL_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));       /* Disable alternative function on PD4, PD5, PD6 and PD7 */
    GPIO_PORTD_DEN_REG   |= ((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));        /* Enable Digital I/O on PD4, PD5, PD6 and PD7 */
    GPIO_PORTD_DATA_REG  &= ~(((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3)));     /* Clear bit 4, 5, 6 and 7 in Data register */

    //RS->PE1, R/W->PE2,ENABLE->PE3,
    GPIO_PORTE_AMSEL_REG &= ~((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));         /* Disable Analog on PE1, PE2 and PE3 */
    GPIO_PORTE_PCTL_REG  &= 0xFFFF000F;                                             /* Clear PMCx bits for PE1, PE2 and PE3 to use it as GPIO pin */
    GPIO_PORTE_DIR_REG   |= ((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));          /* Configure PE1, PE2 and PE3 as output pin */
    GPIO_PORTE_AFSEL_REG &= ~((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));         /* Disable alternative function on PE1, PE2 and PE3 */
    GPIO_PORTE_DEN_REG   |= ((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));          /* Enable Digital I/O on PE1, PE2 and PE3 */
    GPIO_PORTE_DATA_REG  &= ~((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));         /* Clear bit 1, 2 and 3 in Data register */

    //LCD 4-bit Initialization sequence
    Delay_MS(50);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    Delay_MS(50);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    Delay_MS(50);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    LCD_4BITS_send_command(LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
    LCD_4BITS_send_command(g)
}

/**
 * @brief
 * @param command
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
void LCD_4BITS_send_command(uint8 command){

}

/**
 * @brief
 * @param data
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
void LCD_4BITS_send_char_data(uint8 data){

}

/**
 * @brief
 * @param data:
 *        row:
 *        column:
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
void LCD_4BITS_send_data_position(uint8 row, uint8 col, uint8 data){

}

/**
 * @brief
 * @param string:
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
Std_ReturnType LCD_4BITS_send_string(uint8 *string){
    Std_ReturnType ret = E_OK;
    if(NULL == string){
        ret = E_NOT_OK;
    }
    return ret;
}

/**
 * @brief
 * @param string
 *        col:
 *        row:
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
Std_ReturnType LCD_4BITS_send_string_position(uint8 *string, uint8 row, uint8 col){
    Std_ReturnType ret = E_OK;
        if(NULL == string){
            ret = E_NOT_OK;
        }
        return ret;
}
