/*
 * LCD.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#include "LCD.h"

static void LCD_4BITS_SET_CURSOR(uint8 row, uint8 column);

/**
 * @brief To initialize the LCD
 */
void LCD_4BITS_INIT(void){
    //Enable clock for PortD and PortE
    SYSCTL_RCGCGPIO_REG |= ((1<<3) | (1<<4));
    while (!(SYSCTL_PRGPIO_REG & ((1<<3) | (1<<4))));

    //Data lines->PD3-PD6
    GPIO_PORTD_AMSEL_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));       /* Disable Analog on PD3, PD4, PD5 and PD6 */
    GPIO_PORTD_PCTL_REG  &= 0x0000FFFF;                                                                 /* Clear PMCx bits for PD3, PD4, PD5 and PD6 to use it as GPIO pin */
    GPIO_PORTD_DIR_REG   |= ((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));        /* Configure PD3, PD4, PD5 and PD6 as output pin */
    GPIO_PORTD_AFSEL_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));       /* Disable alternative function on PD3, PD4, PD5 and PD6 */
    GPIO_PORTD_DEN_REG   |= ((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));        /* Enable Digital I/O on PD3, PD5, PD5 and PD6 */
    GPIO_PORTD_DATA_REG  &= ~(((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3)));     /* Clear bit 3, 4, 5 and 6 in Data register */

    //RS->PE1, R/W->PE2,ENABLE->PE3,
    GPIO_PORTE_AMSEL_REG &= ~((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));         /* Disable Analog on PE1, PE2 and PE3 */
    GPIO_PORTE_PCTL_REG  &= 0xFFFF000F;                                             /* Clear PMCx bits for PE1, PE2 and PE3 to use it as GPIO pin */
    GPIO_PORTE_DIR_REG   |= ((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));          /* Configure PE1, PE2 and PE3 as output pin */
    GPIO_PORTE_AFSEL_REG &= ~((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));         /* Disable alternative function on PE1, PE2 and PE3 */
    GPIO_PORTE_DEN_REG   |= ((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));          /* Enable Digital I/O on PE1, PE2 and PE3 */
    GPIO_PORTE_DATA_REG  &= ~((1<<RS_PIN) | (1<<RW_PIN) | (1<<ENABLE_PIN));         /* Clear bit 1, 2 and 3 in Data register */

    //LCD 4-bit Initialization sequence
    SysTick_DelayMs(20);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    SysTick_DelayMs(5);
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    SysTick_DelayUs(150);
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
 * @brief To send command to LCD
 *   To send command:
     * 1. R/W Pin = 0 PE2
     * 2. RS pin = 0 PE1
     * 3. Send command through data lines PD4->PD7
     * 4. Send enable signal on E pin
 * @param command: The command neededd to be sent
 */
void LCD_4BITS_send_command(uint8 command){

    GPIO_PORTE_DATA_REG &= ~(1<<RW_PIN); //RW = 0 TO WRITE
    GPIO_PORTE_DATA_REG &= ~(1<<RS_PIN); //RS = 0 FOR INSTRUCTION

    //LOW NIBBLE(4-7) and HIGH NIBBLE(0-3)
    GPIO_PORTD_DATA_REG = (GPIO_PORTD_DATA_REG & 0x0F) | (command >> 4); //the command must be shifted by 4 to get high nibble 4 bits high into low and make sure to clear lower nibble 4 bit firstly

    //we must send enable signal after each send command (Falling Edge)
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    SysTick_DelayMs(2);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);

    GPIO_PORTD_DATA_REG = ((GPIO_PORTD_DATA_REG & 0x0F) | (command & 0x0F)); //send the 4 bits low and make sure to clear lower 4 bit firstly, (command & 0x0F) to make sure I am sending the lower bits only correctly

    //we must send enable signal after each send command (Falling Edge)
     GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
     SysTick_DelayMs(2);
     GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);
}

/**
 * @brief: To send data to LCD only 1 character
 *   To write data:
     * 1. R/W Pin = 0
     * 2. RS pin = 1
     * 3. Send data through data lines
     * 4. Send enable signal on E pin
 * @param data: Data needed to be sent to LCD (character)
 */
void LCD_4BITS_send_char_data(uint8 data){

    GPIO_PORTE_DATA_REG &= ~(1<<RW_PIN); //RW = 0 TO WRITE
    GPIO_PORTE_DATA_REG |= (1<<RS_PIN); //RS = 1 FOR INSTRUCTION

    //LOW NIBBLE(4-7) and HIGH NIBBLE(0-3)
    GPIO_PORTD_DATA_REG = (GPIO_PORTD_DATA_REG & 0x0F) | (data >> 4); //send the 4 bits high into low and make sure to clear lower 4 bit firstly

    //we must send enable signal after each send command (Falling Edge)
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    SysTick_DelayMs( 2);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);

    GPIO_PORTD_DATA_REG = ((GPIO_PORTD_DATA_REG & 0x0F) | (data & 0x0F)); //send the 4 bits low and make sure to clear lower 4 bit firstly, (command & 0x0F) to make sure I am sending the lower bits only correctly

    //we must send enable signal after each send command (Falling Edge)
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    SysTick_DelayMs( 2);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);
}

/**
 * @brief: To send character data to LCD but in specific posistion
 * @param data: character needed to be sent
 *        row:The row number where character is printed
 *        col: The column where the character is printed
 */
void LCD_4BITS_send_data_position(uint8 row, uint8 col, uint8 data){
    LCD_4BITS_SET_CURSOR(row, col);
    LCD_4BITS_send_char_data(data);
}

/**
 * @brief: To send data to LCD but string here we uses the character function and
 * increment to point on second character until NULL termination reached
 * @param string: The string needed to be sent to LCD
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
Std_ReturnType LCD_4BITS_send_string(uint8 *string){
    Std_ReturnType ret = E_OK;
    //check on NULL pointer
    if(NULL == string){
        ret = E_NOT_OK;
    }
    else{
        //while there is a value true implement the function until NULL termination (while(False)
         while (*string){
         //string++ to point to second character
         LCD_4BITS_send_char_data(*string++);
         }
    }
    return ret;
}

/**
 * @brief: To send string to LCD but in specific posistion
 * @param string: String needed to be sent to LCD
 *        col: The column where the first character in string is printed
 *        row: The row where the first character in string is printed
 * @return Status of the function
 *         (E_OK): The function executed successfully
 *          (E_NOT_OK) : Function failed to execute
 */
Std_ReturnType LCD_4BITS_send_string_position(uint8 *string, uint8 row, uint8 col){
    Std_ReturnType ret = E_OK;
    //check on NULL pointer
        if(NULL == string){
            ret = E_NOT_OK;
        }
        else{
            LCD_4BITS_SET_CURSOR(row, col);
            LCD_4BITS_send_string(string);
        }
        return ret;
}

/**
 * @brief: To set cursor on specific position
 * @param col: column to start at
 *        row: row to start at
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

/*** ================ Sub-program Details Section End ====================== ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Maria       07Dec24     Created LCD source file
**/
