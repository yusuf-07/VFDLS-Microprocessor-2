/***
==================================================================================
* @file     : main.c
* @author   : Maria George
* @version  : v1.0
* @brief    : Application Main Run File
* @details  :
==================================================================================
***/

/*** ===================== Include Section Start =========================== ***/
#include <1.MCAL_Layer/GPIO/GPIO.h>
#include <1.MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
#include <1.MCAL_Layer/UART/UART.h>
#include <2.ECU_Layer/DC_MOTOR/DC_MOTOR.h>
#include <2.ECU_Layer/LCD/LCD.h>
#include <2.ECU_Layer/PUSH_BUTTONS/PUSH_BUTTONS.h>
#include <2.ECU_Layer/Ultrasonic/ULTRASONIC.h>
/*** ===================== Include Section End ============================= ***/

/*** ===================== Public Function Section Start ===================== ***/
void main(void) {

    // Initialize UART, LCD, and Push Buttons
    UART0_Init();
    LCD_4BITS_INIT();
    PUSH_BUTTONS_INIT();

    unsigned char message[] = "Welcome to LCD";  // Message to send via UART
    unsigned char receivedMessage[100];         // Buffer to store received UART data

    // Display an initial message on the LCD
    LCD_4BITS_send_string_position((uint8 *)"Press Button", ROW1, 1);
    LCD_4BITS_send_string_position((uint8 *)"to Send Msg", ROW2, 1);

    while (1) {
        // Check if SW1 (PF4) is pressed
        if (PUSH_BUTTON_STATUS(PB_SW0) == PB_PRESSED) {
            // Send the message via UART
            UART0_SendString(message);

            // Receive the message via UART
            UART0_ReceiveString(receivedMessage);  // Wait until the '#' symbol is received

            // Display the received message on the LCD
            LCD_4BITS_send_command(LCD_CLEAR);  // Clear the LCD
            LCD_4BITS_send_string_position(receivedMessage, ROW1, 1);
        }
    }
}
/*** ===================== Public Function Section End ======================= ***/

/***
*******************************************************
User        Date        Brief
*******************************************************
Maria       15Dec24     Created Main
Yusuf       16Dec24     Created Test Cases Source File
**/
