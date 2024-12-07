/*
 * LCD.h
 *
 *  Created on: Dec 7, 2024
 *      Author: Maria George
 */

#ifndef ECU_LAYER_LCD_LCD_H_
#define ECU_LAYER_LCD_LCD_H_

/*-----------------------Includes-----------------------*/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "tm4c123gh6pm_registers.h"
#include "Common_functions.h"
#include <string.h>

/*------------------Macros Declarations------------------*/
#define RS_PIN      1
#define RW_PIN      2
#define ENABLE_PIN  3
#define Data_PIN0   4
#define Data_PIN1   5
#define Data_PIN2   6
#define Data_PIN3   7

/*-------------Macros Functions Declarations-------------*/
/*-------------Macros Functions Declarations-------------*/
#define LCD_CLEAR           0x01 /*To clear screen 0000 0001*/

#define LCD_CURSOR_HOME     0x02 /*To return cursor to intial position 0000 001**/

/*@brief Entry Mode*/
#define LCD_DECREMENT_SHIFT_OFF     0x04 //0000 0100
#define LCD_DECREMENT_SHIFT_ON      0x05 //0000 0101
#define LCD_INCREMENT_SHIFT_OFF     0x06 //0000 0110
#define LCD_INCREMENT_SHIFT_ON      0x07 //0000 0111

/*@brief Move cursor and Shift display*/
#define LCD_SHIFT_CURSOR_LEFT       0x10 //0001 0000
#define LCD_SHIFT_CURSOR_RIGHT      0x14 //0001 0100
#define LCD_SHIFT_DISPLAY_LEFT      0x18 //0001 1000
#define LCD_SHIFT_DISPLAY_RIGHT     0x1C //0001 1100

/*@brief Display ON/OFF*/
#define LCD_DISPLAY_OFF_UNDERLINE_OFF_CURSOR_OFF    0x08 //0000 1000
#define LCD_DISPLAY_OFF_UNDERLINE_OFF_CURSOR_ON     0x09 //0000 1001
#define LCD_DISPLAY_OFF_UNDERLINE_ON_CURSOR_OFF     0x0A //0000 1010
#define LCD_DISPLAY_OFF_UNDERLINE_ON_CURSOR_ON      0x0B //0000 1011
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF     0x0C //0000 1100
#define LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON      0x0D //0000 1101
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF      0x0E //0000 1110
#define LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON       0x0F //0000 1111

/*@brief Function set*/
#define LCD_4BIT_1LINE_SMALL_FONT   0x20 //0010 0000
#define LCD_4BIT_1LINE_LARGE_FONT   0x24 //0010 0100
#define LCD_4BIT_2LINE_SMALL_FONT   0x28 //0010 1000
#define LCD_4BIT_2LINE_LARGE_FONT   0x2C //0010 1100
#define LCD_8BIT_1LINE_SMALL_FONT   0x30 //0011 0000
#define LCD_8BIT_1LINE_LARGE_FONT   0x34 //0011 0100
#define LCD_8BIT_2LINE_SMALL_FONT   0x38 //0011 1000
#define LCD_8BIT_2LINE_LARGE_FONT   0x3C //0011 1100

#define ROW1    1
#define ROW2    2

/*@brief Address Set -> CGRAM*/
#define LCD_CGRAM_START     0x40 //0100 0000

/*@brief Address Set -> DDRAM*/
#define LCD_DDRAM_START     0x80 //1000 000

/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/
void LCD_4BITS_INIT(void);
void LCD_4BITS_send_command(uint8 command);
void LCD_4BITS_send_char_data(uint8 data);
void LCD_4BITS_send_data_position(uint8 row, uint8 col, uint8 data);
Std_ReturnType LCD_4BITS_send_string(uint8 *string);
Std_ReturnType LCD_4BITS_send_string_position(uint8 *string, uint8 row, uint8 col);

#endif /* ECU_LAYER_LCD_LCD_H_ */
