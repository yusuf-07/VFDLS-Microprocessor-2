/*
 * LCD.c
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#include "LCD.h"
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND    364
static void Delay_MS(unsigned long long n);
static void LCD_4BITS_SET_CURSOR(uint8 row, uint8 column);
static void lcd_send_4bits(uint8 _data_command);
static void lcd_send_enable_4bits(void);

/* ====================== LCD =========================== */
/*
 * Port A Pin 3 for Data Line
 * Port A Pin 4 for Data Line
 * Port A Pin 5 for Data Line
 * Port A Pin 6 for Data Line
 * Port E Pin 1 for Rs
 * Port E Pin 3 for Enable
 */
/**
 * @brief To initialize the LCD
 */


void LCD_4BITS_INIT(void){
    //Enable clock for PortA and PortE
    SYSCTL_RCGCGPIO_REG |= ((1<<0) | (1<<4));
    //SysTick_DelayMs(10); // Add delay to stabilize the clock
    Delay_MS(10);
    while ((SYSCTL_PRGPIO_REG & ((1<<0) | (1<<4))) == 0);

    //LCD_RESET();

    //Data lines->PA3-PA6
    GPIO_PORTA_AMSEL_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));       /* Disable Analog on PA3, PA4, PA5 and PA6 */
    GPIO_PORTA_PCTL_REG  &= 0xF0000FFF;                                                                 /* Clear PMCx bits for PA3, PA4, PA5 and PA6 to use it as GPIO pin */
    GPIO_PORTA_DIR_REG   |= ((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));        /* Configure PA3, PA4, PA5 and PA6 as output pin */
    GPIO_PORTA_AFSEL_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));       /* Disable alternative function on PA3, PA4, PA5 and PA6 */
    GPIO_PORTA_DEN_REG   |= ((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));        /* Enable Digital I/O on PA3, PA5, PA5 and PA6 */
    GPIO_PORTA_DATA_REG  &= ~(((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3)));     /* Clear bit 3, 4, 5 and 6 in Data register */

    //RS->PE1, R/W->PE2,ENABLE->PE3,
    GPIO_PORTE_AMSEL_REG &= ~((1<<RS_PIN) | (1<<ENABLE_PIN));         /* Disable Analog on PE1, PE2 and PE3 */
    GPIO_PORTE_PCTL_REG  &= 0xFFFF000F;                                             /* Clear PMCx bits for PE1, PE2 and PE3 to use it as GPIO pin */
    GPIO_PORTE_DIR_REG   |= ((1<<RS_PIN) | (1<<ENABLE_PIN));          /* Configure PE1, PE2 and PE3 as output pin */
    GPIO_PORTE_AFSEL_REG &= ~((1<<RS_PIN) | (1<<ENABLE_PIN));         /* Disable alternative function on PE1, PE2 and PE3 */
    GPIO_PORTE_DEN_REG   |= ((1<<RS_PIN) | (1<<ENABLE_PIN));          /* Enable Digital I/O on PE1, PE2 and PE3 */
    GPIO_PORTE_DATA_REG  &= ~((1<<RS_PIN) | (1<<ENABLE_PIN));         /* Clear bit 1, 2 and 3 in Data register */

    GPIO_PORTA_DATA_REG &= ~((1<<Data_PIN0) | (1<<Data_PIN1) | (1<<Data_PIN2) | (1<<Data_PIN3));
    GPIO_PORTE_DATA_REG &= ~((1<<RS_PIN) | (1<<ENABLE_PIN));

    //LCD 4-bit Initialization sequence
    // Wait for more than 40 ms after VDD rises to 4.5 V
    //SysTick_DelayMs(50);
    Delay_MS(50);

    // Function Set: 4-bit mode
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    //SysTick_DelayMs(5); // Wait for more than 37 �s
    Delay_MS(5);

    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    //SysTick_DelayUs(200); // Wait for more than 37 �s
    Delay_MS(1);

    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);
    //SysTick_DelayMs(10);
    Delay_MS(10);

    // Clear Display
    LCD_4BITS_send_command(LCD_CLEAR);
    //SysTick_DelayMs(2);
    Delay_MS(2);

    //Set cursor home
    LCD_4BITS_send_command(LCD_CURSOR_HOME);
    //SysTick_DelayMs(2);
    Delay_MS(2);

    // Entry Mode Set: Increment cursor, no display shift
    LCD_4BITS_send_command(LCD_INCREMENT_SHIFT_OFF);
    //SysTick_DelayMs(2);
    Delay_MS(2);

    // Display Control: Turn on display, cursor off
    LCD_4BITS_send_command(LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
    //SysTick_DelayMs(2);
    Delay_MS(2);

    // Function Set: 4-bit mode, 2 lines, 5x8 dots
    LCD_4BITS_send_command(LCD_4BIT_2LINE_SMALL_FONT);

    //0x80->row 1, column 1
    LCD_4BITS_send_command(LCD_DDRAM_START);
}

/**
 * @brief To send command to LCD
 *   To send command:
     * 1. R/W Pin = 0 PE2
     * 2. RS pin = 0 PE1
     * 3. Send command through data lines PA3->PA6
     * 4. Send enable signal on E pin
 * @param command: The command needed to be sent
 */
void LCD_4BITS_send_command(uint8 command){

    GPIO_PORTE_DATA_REG &= ~(1<<RS_PIN); //RS = 0 FOR INSTRUCTION

    // The command is sent in two parts: the higher nibble (bits 4-7) and the lower nibble (bits 0-3)
    // Send the higher nibble of the command (bits 4-7)
    lcd_send_4bits(command >> 4); // Shift the command right by 4 bits to get the higher nibble

    //we must send enable signal after each send command (Falling Edge)
    lcd_send_enable_4bits();

    // Send the lower nibble of the command (bits 0-3)
    lcd_send_4bits(command & 0x0F); //mask the command with 0x0F to get only the lower nibble

    //we must send enable signal after each send command (Falling Edge)
    lcd_send_enable_4bits();
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

    GPIO_PORTE_DATA_REG |= (1<<RS_PIN); //RS = 1 FOR INSTRUCTION

    // The data is sent in two parts: the higher nibble (bits 4-7) and the lower nibble (bits 0-3)
    // Send the higher nibble of the data (bits 4-7)
    lcd_send_4bits(data >> 4); // Shift the data right by 4 bits to get the higher nibble

    //we must send enable signal after each send
    lcd_send_enable_4bits();

    // Send the lower nibble of the data (bits 0-3)
    lcd_send_4bits(data & 0x0F); //mask the data with 0x0F to get only the lower nibble

    //we must send enable signal after each send
    lcd_send_enable_4bits();


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
void LCD_4BITS_send_string(uint8 *string){
    //while there is a value true implement the function until NULL termination (while(False)
     while (*string){
         //string++ to point to second character
         LCD_4BITS_send_char_data(*string++);
     }
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
void LCD_4BITS_send_string_position(uint8 *string, uint8 row, uint8 col){
        LCD_4BITS_SET_CURSOR(row, col);
        LCD_4BITS_send_string(string);
}

void LCD_RESET(void){
    SysTick_DelayMs(3000);
    LCD_4BITS_send_command(LCD_CLEAR);

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
        LCD_4BITS_send_command(LCD_DDRAM_START + ROW1_START_ADD);
        break;
    }
}

static void lcd_send_4bits(uint8 nibble) {
    uint8 i;
    // Loop through the 4 bits
    for (i = 0; i < 4; i++) {
        // Check if the bit is set (1) or cleared (0)
        //nibble shifted by i to move the bit we want to check into the LSB position.
        if ((nibble >> i) & 0x01) {
            GPIO_PORTA_DATA_REG |= (1 << (Data_PIN0 + i)); // Set pin high
        } else {
            GPIO_PORTA_DATA_REG &= ~(1 << (Data_PIN0 + i)); // Set pin low
        }
    }
}


static void lcd_send_enable_4bits(void){
    GPIO_PORTE_DATA_REG |= (1<<ENABLE_PIN);
    //SysTick_DelayUs(500);
    Delay_MS(1);
    GPIO_PORTE_DATA_REG &= ~ (1<<ENABLE_PIN);
    //SysTick_DelayUs(500);
    Delay_MS(1);
}
void Delay_MS(unsigned long long n){
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n));
}
/* ================ Sub-program Details Section End ====================== */

/**
*******************
User        Date        Brief
*******************
Maria       07Dec24     Created LCD source file
**/
