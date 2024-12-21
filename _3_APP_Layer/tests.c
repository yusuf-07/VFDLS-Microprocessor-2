/*
 * tests.c
 *
 *  Created on: Dec 21, 2024
 *      Author: User
 */




/*** ===================== Include Section Start =========================== ***/
#include <_1_MCAL_Layer/GPIO/GPIO.h>
#include <_1_MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
#include <_1_MCAL_Layer/UART/UART.h>
#include <_2_ECU_Layer/DC_MOTOR/DC_MOTOR.h>
#include <_2_ECU_Layer/LCD/LCD.h>
#include <_2_ECU_Layer/PUSH_BUTTONS/PUSH_BUTTONS.h>
#include <_2_ECU_Layer/Ultrasonic/ULTRASONIC.h>
#include <_1_MCAL_Layer/ADC/ADC.h>
#include <_2_ECU_Layer/LM35/LM35.h>
/*** ===================== Include Section End ============================= ***/

/*** ===================== Public Function Section Start ===================== ***/
//void main(void) {
//
//    // Initialize UART, LCD, and Push Buttons
//    UART0_Init();
//    LCD_4BITS_INIT();
//    PUSH_BUTTONS_INIT();
//
//    unsigned char message[] = "Welcome to LCD";  // Message to send via UART
//    unsigned char receivedMessage[100];         // Buffer to store received UART data
//
//    // Display an initial message on the LCD
//    LCD_4BITS_send_string_position((uint8 *)"Press Button", ROW1, 1);
//    LCD_4BITS_send_string_position((uint8 *)"to Send Msg", ROW2, 1);
//
//    while (1) {
//        // Check if SW1 (PF4) is pressed
//        if (PUSH_BUTTON_STATUS(PB_SW0) == PB_PRESSED) {
//            // Send the message via UART
//            UART0_SendString(message);
//
//            // Receive the message via UART
//            UART0_ReceiveString(receivedMessage);  // Wait until the '#' symbol is received
//
//            // Display the received message on the LCD
//            LCD_4BITS_send_command(LCD_CLEAR);  // Clear the LCD
//            LCD_4BITS_send_string_position(receivedMessage, ROW1, 1);
//        }
//    }
//}

// Function prototypes
//void test_LCD_with_push_buttons(void);
////
//int main(void)
//{
//    DC_MOTORA_INIT();
//    DC_MOTORB_INIT();
//    PUSH_BUTTONS_INIT();
////    // Initialize LCD and Push Buttons
////    LCD_4BITS_INIT();
////    PUSH_BUTTONS_INIT();
////
////    // Start testing LCD with push buttons
////    test_LCD_with_push_buttons();
//
//    while(1)
//    {
//        // Continuous checking in the main loop
//    }
//}
//
// Function to test LCD functionality with Push Buttons
//void test_LCD_with_push_buttons(void)
//{
//    uint8 pb_status = PB_RELEASED;
//
//    // Display an initial message
//    LCD_4BITS_send_string("Push Buttons Test");
//
//    while(1)
//    {
//        // Check if PB_SW0 (PF4) is pressed
//        pb_status = PUSH_BUTTON_STATUS(PB_SW0);  // PB_SW0 is connected to PF4
//
//        if(pb_status == PB_PRESSED)
//        {
//            // If PB_SW0 is pressed, clear the LCD screen
//            LCD_4BITS_send_command(LCD_CLEAR);
//            LCD_4BITS_send_string("PB_0 Pressed!");
//            while(PUSH_BUTTON_STATUS(PB_SW0) == PB_PRESSED);  // Wait for button release
//        }
//
//        // Check if PB_SW1 (PF0) is pressed
//        pb_status = PUSH_BUTTON_STATUS(PB_SW1);  // PB_SW1 is connected to PF0
//
//        if(pb_status == PB_PRESSED)
//        {
//            // If PB_SW1 is pressed, display a message on the LCD
//            LCD_4BITS_send_command(LCD_CLEAR);
//            LCD_4BITS_send_string("PB_1 Pressed!");
//            while(PUSH_BUTTON_STATUS(PB_SW1) == PB_PRESSED);  // Wait for button release
//        }
//    }
//}


//#define DELAY_TIME 1000 // 1-second delay for periodic monitoring
//
//void System_Init(void);
//void Display_Temperature(void);
//
//int main(void) {
//    System_Init();  // Initialize UART, ADC, and GPIO
//
//    UART0_SendString("System Initialized. Monitoring Temperature...\n");
//
//    while (1) {
//        Display_Temperature();  // Read and display the temperature
//        SysTick_DelayMs(DELAY_TIME); // 1-second delay
//    }
//
//}
//
///**
// * @brief Initializes the required peripherals: UART0, ADC, and PE0 for LM35.
// */
//void System_Init(void) {
//
//    UART0_Init();    // Initialize UART0 for communication
//    ADC0_Init();     // Initialize ADC0 for LM35 on PE0
//    SysTick_Init(15999999);  // Initialize SysTick timer for delays
//}
//
///**
// * @brief Reads the temperature from the LM35 sensor and displays it over UART.
// */
//void Display_Temperature(void) {
//    uint32 temperature = LM35_GET_TEMP();  // Get the temperature in Celsius
//
//    // Print the temperature to the UART terminal
//    UART0_SendString("Room Temperature: ");
//    UART0_SendByte((temperature / 10) + '0');   // Tens digit
//    UART0_SendByte((temperature % 10) + '0');   // Ones digit
//    UART0_SendString(" C#");
//}



//int main(void) {
//    // Initialize UART for terminal communication
//    UART0_Init();
//
//    // Initialize EEPROM
//    if (EEPROM_INIT() == E_OK) {
//        UART0_SendString((unsigned char *)"EEPROM Initialized Successfully!\n");
//    } else {
//        UART0_SendString((unsigned char *)"EEPROM Initialization Failed!\n");
//        while (1); // Halt execution if EEPROM initialization fails
//    }
//
//    // Log fault codes into EEPROM
//    UART0_SendString((unsigned char *)"Logging Fault Codes...\n");
//
//    Log_Fault("P001"); // Log fault code "P001"
//    Log_Fault("P002"); // Log fault code "P002"
//
//    UART0_SendString((unsigned char *)"Fault Codes Logged!\n");
//
//    // Retrieve fault codes from EEPROM
//    UART0_SendString((unsigned char *)"Retrieving Fault Codes...\n");
//    Retrieve_Faults();
//
//    // Loop indefinitely
//    while (1) {
//        // Optionally add a delay or additional functionality here
//    }
//
//    return 0;
//}
/*** ===================== Public Function Section End ======================= ***/

/***
*******************************************************
User        Date        Brief
*******************************************************
Maria       15Dec24     Created Main
Yusuf       16Dec24     Created Test Cases Source File
**/
