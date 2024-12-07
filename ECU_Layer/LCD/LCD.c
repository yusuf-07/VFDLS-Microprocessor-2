/*
 * LCD.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#include "LCD.h"

static void LCD_4BITS_SET_CURSOR(uint8 row, uint8 column);

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
    SysTick_DelayMs(_delay_sys_50ms);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    SysTick_DelayMs(_delay_sys_50ms);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    SysTick_DelayMs(_delay_sys_50ms);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    LCD_4BITS_send_command(LCD_CLEAR);
    LCD_4BITS_send_command(LCD_CURSOR_HOME);
    LCD_4BITS_send_command(LCD_INCREMENT_SHIFT_OFF);
    LCD_4BITS_send_command(LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    //0x80-<row1, col 1
    LCD_4BITS_send_command(LCD_DDRAM_START);

}

/**
 * @brief
 * @param command
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
void LCD_4BITS_send_command(uint8 command){
    /*To send command:
     * 1. R/W Pin = 0 PE2
     * 2. RS pin = 0 PE1
     * 3. Send command through data lines PD4->PD7
     * 4. Send enable signal on E pin
     */
    GPIO_PORTE_DATA_REG &= ~(1<<RW_PIN); //RW = 0 TO WRITE
    GPIO_PORTE_DATA_REG &= ~(1<<RS_PIN); //RS = 0 FOR INSTRUCTION

    //LOW NIBBLE(4-7) and HIGH NIBBLE(0-3)
    GPIO_PORTD_DATA_REG = (GPIO_PORTD_DATA_REG & 0x0F) | (command >> 4); //send the 4 bits high into low and make sure to clear lower 4 bit firstly

    //we must send enable signal after each send command (Falling Edge)
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    SysTick_DelayMs( _delay_sys_2ms);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);

    GPIO_PORTD_DATA_REG = ((GPIO_PORTD_DATA_REG & 0x0F) | (command & 0x0F)); //send the 4 bits low and make sure to clear lower 4 bit firstly, (command & 0x0F) to make sure I am sending the lower bits only correctly

    //we must send enable signal after each send command (Falling Edge)
     GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
     SysTick_DelayMs( _delay_sys_2ms);
     GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);
}

/**
 * @brief
 * @param data
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
void LCD_4BITS_send_char_data(uint8 data){
    /*To write data:
     * 1. R/W Pin = 0
     * 2. RS pin = 1
     * 3. Send data through data lines
     * 4. Send enable signal on E pin
     */

    GPIO_PORTE_DATA_REG &= ~(1<<RW_PIN); //RW = 0 TO WRITE
    GPIO_PORTE_DATA_REG |= (1<<RS_PIN); //RS = 1 FOR INSTRUCTION

    //LOW NIBBLE(4-7) and HIGH NIBBLE(0-3)
    GPIO_PORTD_DATA_REG = (GPIO_PORTD_DATA_REG & 0x0F) | (data >> 4); //send the 4 bits high into low and make sure to clear lower 4 bit firstly

    //we must send enable signal after each send command (Falling Edge)
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    SysTick_DelayMs( _delay_sys_2ms);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);

    GPIO_PORTD_DATA_REG = ((GPIO_PORTD_DATA_REG & 0x0F) | (data & 0x0F)); //send the 4 bits low and make sure to clear lower 4 bit firstly, (command & 0x0F) to make sure I am sending the lower bits only correctly

    //we must send enable signal after each send command (Falling Edge)
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    SysTick_DelayMs( _delay_sys_2ms);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);
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

/**
 * @brief
 * @param col:
 *        row:
 */
static void LCD_4BITS_SET_CURSOR(uint8 row, uint8 column){
    column--;
    switch(row){
    case ROW1:
        LCD_4BITS_send_command((LCD_DDRAM_START + ROW1_START_ADD) + column);
        break;
    case ROW2:
        LCD_4BITS_send_command((LCD_DDRAM_START + ROW2_START_ADD) + column);
        break;
    default:
        row = 0;
        column = 0;
        break;
    }
}
