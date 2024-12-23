/////*
//// * tests.c
//// *
//// *  Created on: Dec 21, 2024
//// *      Author: User
//// */
////
////
////
////
/////*** ===================== Include Section Start =========================== ***/
//#include <_1_MCAL_Layer/GPIO/GPIO.h>
//#include <_1_MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
//#include <_1_MCAL_Layer/UART/UART.h>
//#include <_2_ECU_Layer/DC_MOTOR/DC_MOTOR.h>
//#include <_2_ECU_Layer/LCD/LCD.h>
//#include <_2_ECU_Layer/PUSH_BUTTONS/PUSH_BUTTONS.h>
//#include <_2_ECU_Layer/Ultrasonic/ULTRASONIC.h>
//#include <_1_MCAL_Layer/ADC/ADC.h>
//#include <_2_ECU_Layer/LM35/LM35.h>
//#include "common_macros.h"
//#include "tm4c123gh6pm_registers.h"
/////*** ===================== Include Section End ============================= ***/
////
/////*** ===================== Public Function Section Start ===================== ***/
//////void main(void) {
//////
//////    // Initialize UART, LCD, and Push Buttons
//////    UART0_Init();
//////    LCD_4BITS_INIT();
//////    PUSH_BUTTONS_INIT();
//////
//////    unsigned char message[] = "Welcome to LCD";  // Message to send via UART
//////    unsigned char receivedMessage[100];         // Buffer to store received UART data
//////
//////    // Display an initial message on the LCD
//////    LCD_4BITS_send_string_position((uint8 *)"Press Button", ROW1, 1);
//////    LCD_4BITS_send_string_position((uint8 *)"to Send Msg", ROW2, 1);
//////
//////    while (1) {
//////        // Check if SW1 (PF4) is pressed
//////        if (PUSH_BUTTON_STATUS(PB_SW0) == PB_PRESSED) {
//////            // Send the message via UART
//////            UART0_SendString(message);
//////
//////            // Receive the message via UART
//////            UART0_ReceiveString(receivedMessage);  // Wait until the '#' symbol is received
//////
//////            // Display the received message on the LCD
//////            LCD_4BITS_send_command(LCD_CLEAR);  // Clear the LCD
//////            LCD_4BITS_send_string_position(receivedMessage, ROW1, 1);
//////        }
//////    }
//////}
////
////// Function prototypes
//////void test_LCD_with_push_buttons(void);
////////
////int main(void)
////{
////    //DC_MOTORA_INIT();
////    //DC_MOTORB_INIT();
////    //PUSH_BUTTONS_INIT();
//////    // Initialize LCD and Push Buttons
////    LCD_4BITS_INIT();
////    PUSH_BUTTONS_INIT();
//////
////    // Start testing LCD with push buttons
////    //test_LCD_with_push_buttons();
////    uint8 pb_status = PB_RELEASED;
////
////        // Display an initial message
////        LCD_4BITS_send_string("Push Buttons Test");
////
////        while(1)
////        {
////            // Check if PB_SW0 (PF4) is pressed
////            pb_status = PUSH_BUTTON_STATUS(PB_SW0);  // PB_SW0 is connected to PF4
////
////            if(pb_status == PB_PRESSED)
////            {
////                // If PB_SW0 is pressed, clear the LCD screen
////                LCD_4BITS_send_command(LCD_CLEAR);
////                LCD_4BITS_send_string("PB_0 Pressed!");
////                while(PUSH_BUTTON_STATUS(PB_SW0) == PB_PRESSED);  // Wait for button release
////            }
////
////            // Check if PB_SW1 (PF0) is pressed
////            pb_status = PUSH_BUTTON_STATUS(PB_SW1);  // PB_SW1 is connected to PF0
////
////            if(pb_status == PB_PRESSED)
////            {
////                // If PB_SW1 is pressed, display a message on the LCD
////                LCD_4BITS_send_command(LCD_CLEAR);
////                LCD_4BITS_send_string("PB_1 Pressed!");
////                while(PUSH_BUTTON_STATUS(PB_SW1) == PB_PRESSED);  // Wait for button release
////            }
////        }
////
//////    while(1)
//////    {
//////        // Continuous checking in the main loop
//////    }
////}
//////
////// Function to test LCD functionality with Push Buttons
//////void test_LCD_with_push_buttons(void)
//////{
//////    uint8 pb_status = PB_RELEASED;
//////
//////    // Display an initial message
//////    LCD_4BITS_send_string("Push Buttons Test");
//////
//////    while(1)
//////    {
//////        // Check if PB_SW0 (PF4) is pressed
//////        pb_status = PUSH_BUTTON_STATUS(PB_SW0);  // PB_SW0 is connected to PF4
//////
//////        if(pb_status == PB_PRESSED)
//////        {
//////            // If PB_SW0 is pressed, clear the LCD screen
//////            LCD_4BITS_send_command(LCD_CLEAR);
//////            LCD_4BITS_send_string("PB_0 Pressed!");
//////            while(PUSH_BUTTON_STATUS(PB_SW0) == PB_PRESSED);  // Wait for button release
//////        }
//////
//////        // Check if PB_SW1 (PF0) is pressed
//////        pb_status = PUSH_BUTTON_STATUS(PB_SW1);  // PB_SW1 is connected to PF0
//////
//////        if(pb_status == PB_PRESSED)
//////        {
//////            // If PB_SW1 is pressed, display a message on the LCD
//////            LCD_4BITS_send_command(LCD_CLEAR);
//////            LCD_4BITS_send_string("PB_1 Pressed!");
//////            while(PUSH_BUTTON_STATUS(PB_SW1) == PB_PRESSED);  // Wait for button release
//////        }
//////    }
//////}
////
////
//////#define DELAY_TIME 1000 // 1-second delay for periodic monitoring
//////
//////void System_Init(void);
//////void Display_Temperature(void);
//////
//////int main(void) {
//////    System_Init();  // Initialize UART, ADC, and GPIO
//////
//////    UART0_SendString("System Initialized. Monitoring Temperature...\n");
//////
//////    while (1) {
//////        Display_Temperature();  // Read and display the temperature
//////        SysTick_DelayMs(DELAY_TIME); // 1-second delay
//////    }
//////
//////}
//////
///////**
////// * @brief Initializes the required peripherals: UART0, ADC, and PE0 for LM35.
////// */
//////void System_Init(void) {
//////
//////    UART0_Init();    // Initialize UART0 for communication
//////    ADC0_Init();     // Initialize ADC0 for LM35 on PE0
//////    SysTick_Init(15999999);  // Initialize SysTick timer for delays
//////}
//////
///////**
////// * @brief Reads the temperature from the LM35 sensor and displays it over UART.
////// */
//////void Display_Temperature(void) {
//////    uint32 temperature = LM35_GET_TEMP();  // Get the temperature in Celsius
//////
//////    // Print the temperature to the UART terminal
//////    UART0_SendString("Room Temperature: ");
//////    UART0_SendByte((temperature / 10) + '0');   // Tens digit
//////    UART0_SendByte((temperature % 10) + '0');   // Ones digit
//////    UART0_SendString(" C#");
//////}
////
////
////
//////int main(void) {
//////    // Initialize UART for terminal communication
//////    UART0_Init();
//////
//////    // Initialize EEPROM
//////    if (EEPROM_INIT() == E_OK) {
//////        UART0_SendString((unsigned char *)"EEPROM Initialized Successfully!\n");
//////    } else {
//////        UART0_SendString((unsigned char *)"EEPROM Initialization Failed!\n");
//////        while (1); // Halt execution if EEPROM initialization fails
//////    }
//////
//////    // Log fault codes into EEPROM
//////    UART0_SendString((unsigned char *)"Logging Fault Codes...\n");
//////
//////    Log_Fault("P001"); // Log fault code "P001"
//////    Log_Fault("P002"); // Log fault code "P002"
//////
//////    UART0_SendString((unsigned char *)"Fault Codes Logged!\n");
//////
//////    // Retrieve fault codes from EEPROM
//////    UART0_SendString((unsigned char *)"Retrieving Fault Codes...\n");
//////    Retrieve_Faults();
//////
//////    // Loop indefinitely
//////    while (1) {
//////        // Optionally add a delay or additional functionality here
//////    }
//////
//////    return 0;
//////}
////
////
////
////
////
////
//////uint8_t Read_PushButton(uint8_t pin);
//////
//////int main(void) {
//////    UART0_Init();          // Initialize UART0 for communication
//////    PUSH_BUTTONS_INIT();    // Initialize push buttons on PB0 and PB1
//////
//////    UART0_SendString("Push Button Test Program\n");
//////
//////    while (1) {
//////        if (Read_PushButton(0)) { // Check if PB0 is pressed
//////            UART0_SendString("PB0 is pressed.\n");
//////            while (Read_PushButton(0)); // Wait until the button is released
//////        }
//////
//////        if (Read_PushButton(1)) { // Check if PB1 is pressed
//////            UART0_SendString("PB1 is pressed.\n");
//////            while (Read_PushButton(1)); // Wait until the button is released
//////        }
//////    }
//////}
//////
//////uint8_t Read_PushButton(uint8_t pin) {
//////    return ((GPIO_PORTB_DATA_REG & (1 << pin)) == 0) ? 1 : 0; // Active LOW logic
//////}
////
//#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND    364
//void Delay_MS(unsigned long long n);
//void Delay_MS(unsigned long long n){
//    volatile unsigned long long count = 0;
//    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n));
//}
//void Leds_Init(void) {
//    SYSCTL_RCGCGPIO_REG |= 0x20;
//    while ((SYSCTL_PRGPIO_REG & 0x20) == 0);
//    GPIO_PORTF_AMSEL_REG &= 0xF1;
//    GPIO_PORTF_PCTL_REG &= 0xFFFF000F;
//    GPIO_PORTF_DIR_REG |= 0x0E;
//    GPIO_PORTF_AFSEL_REG &= 0xF1;
//    GPIO_PORTF_DEN_REG |= 0x0E;
//    GPIO_PORTF_DATA_REG &= 0xF1;
//}
////void Check_Button_Release(void)
////{
////    // Check if SW0 (PF4) is pressed
////    if (GET_BIT(GPIO_PORTF_DATA_REG, 4) == 0) {  // Button is pressed when the bit is 0 (active-low)
////        DC_MOTORA_START();  // Start Motor A when SW0 is pressed
////    }
////    // Check if SW0 (PF4) is released
////    else if (GET_BIT(GPIO_PORTF_DATA_REG, 4) == 1) {
////        DC_MOTORA_STOP();  // Stop Motor A when SW0 is released
////    }
////
////    // Check if SW1 (PF0) is pressed
////    if (GET_BIT(GPIO_PORTF_DATA_REG, 0) == 0) {  // Button is pressed when the bit is 0 (active-low)
////        DC_MOTORA_START();  // Start Motor A when SW1 is pressed
////    }
////    // Check if SW1 (PF0) is released
////    else if (GET_BIT(GPIO_PORTF_DATA_REG, 0) == 1) {
////        DC_MOTORA_STOP();  // Stop Motor A when SW1 is released
////    }
////
////    // Check if SW2 (PB0) is pressed
////    if (GET_BIT(GPIO_PORTB_DATA_REG, 0) == 0) {  // Button is pressed when the bit is 0 (active-low)
////        DC_MOTORB_START();  // Start Motor B when SW2 is pressed
////    }
////    // Check if SW2 (PB0) is released
////    else if (GET_BIT(GPIO_PORTB_DATA_REG, 0) == 1) {
////        DC_MOTORB_STOP();  // Stop Motor B when SW2 is released
////    }
////
////    // Check if SW3 (PB1) is pressed
////    if (GET_BIT(GPIO_PORTB_DATA_REG, 1) == 0) {  // Button is pressed when the bit is 0 (active-low)
////        DC_MOTORB_START();  // Start Motor B when SW3 is pressed
////    }
////    // Check if SW3 (PB1) is released
////    else if (GET_BIT(GPIO_PORTB_DATA_REG, 1) == 1) {
////        DC_MOTORB_STOP();  // Stop Motor B when SW3 is released
////    }
////}
//static volatile uint8 motorA_state = 0;  // 0: Stop, 1: Start CCW, 2: Start CW
//static volatile uint8 motorB_state = 0;  // 0: Stop, 1: Start CCW, 2: Start CW
//static volatile uint8 motor_active = 0;
////void Process_Motor_States(void)
////{
////    /* Motor A Control */
////    if (motorA_state == 1) {                 /* Start Motor A CCW */
////        DC_MOTORA_START(DIR_CCW);
////        if (GET_BIT(GPIO_PORTF_DATA_REG, 4) == 1) {  /* Stop when SW0 (PF4) is released */
////            DC_MOTORA_STOP();
////            motorA_state = 0;                /* Reset state */
////        }
////    } else if (motorA_state == 2) {          /* Start Motor A CW */
////        DC_MOTORA_START(DIR_CW);
////        if (GET_BIT(GPIO_PORTF_DATA_REG, 0) == 1) {  /* Stop when SW1 (PF0) is released */
////            DC_MOTORA_STOP();
////            motorA_state = 0;                /* Reset state */
////        }
////    }
////
////    /* Motor B Control */
////    if (motorB_state == 1) {                 /* Start Motor B CCW */
////        DC_MOTORB_START(DIR_CCW);
////        if (GET_BIT(GPIO_PORTB_DATA_REG, 0) == 1) {  /* Stop when SW2 (PB0) is released */
////            DC_MOTORB_STOP();
////            motorB_state = 0;                /* Reset state */
////        }
////    } else if (motorB_state == 2) {          /* Start Motor B CW */
////        DC_MOTORB_START(DIR_CW);
////        if (GET_BIT(GPIO_PORTB_DATA_REG, 1) == 1) {  /* Stop when SW3 (PB1) is released */
////            DC_MOTORB_STOP();
////            motorB_state = 0;                /* Reset state */
////        }
////    }
////}
////int main(void)
////{
////    DC_MOTORA_INIT();  // Initialize Motor A
////    DC_MOTORB_INIT();  // Initialize Motor B
////    PUSH_BUTTONS_INIT();  // Initialize Push Buttons
////
////    while (1) {
////        Process_Motor_States();
////        //Check_Button_Release();  // Continuously check the button states
////    }
////}
//int main(void)
//{
//    /* Initialize GPIO, motors, and interrupts */
//    DC_MOTORA_INIT();
//    DC_MOTORB_INIT();
//    PUSH_BUTTONS_INIT();
////    GPIO_InterruptEnable(GPIO_PORTB, 0, 2); /* Enable PB0 interrupt with priority 2 */
////    GPIO_InterruptEnable(GPIO_PORTB, 1, 2); /* Enable PB1 interrupt with priority 2 */
////    GPIO_InterruptEnable(GPIO_PORTF, 4, 2); /* Enable PF4 interrupt with priority 2 */
////    GPIO_InterruptEnable(GPIO_PORTF, 0, 2); /* Enable PF0 interrupt with priority 2 */
//
//    while (1)
//    {
//        switch(motor_active)
//        {
//                case 0:
//                    DC_MOTORB_STOP();
//                case 1:
//                    DC_MOTORB_START(DIR_CCW);
//                    break;
//                case 2:
//                    DC_MOTORB_START(DIR_CW);
//                    break;
//                default:
//                    DC_MOTORB_STOP();
//                    break;
//        }
//
//    }
//}
//
////    DC_MOTORA_START(DIR_CW);
////    DC_MOTORB_START(DIR_CW);
////    Delay_MS(3000);
////    DC_MOTORA_START(DIR_CCW);
////    DC_MOTORB_START(DIR_CCW);
//
////    Leds_Init();
////    SysTick_Init();
////    Ultrasonic_Init();
////    unsigned long distance = 0;
////
////    while (1)
////    {
////
////            distance = Ultrasonic_GetDistance();
////
////            GPIO_PORTF_DATA_REG &= ~0x0E; // Clear previous LED state
////
////            if (distance < 5) {
////                GPIO_PORTF_DATA_REG |= 0x0E;
////            } else if (distance >= 5 && distance <= 20) {
////                GPIO_PORTF_DATA_REG |= 0x02;
////            } else if (distance > 20 && distance <= 100) {
////                GPIO_PORTF_DATA_REG |= 0x04;
////            } else {
////                GPIO_PORTF_DATA_REG |= 0x08;
////            }
////        }
////}
/////*** ===================== Public Function Section End ======================= ***/
////
/////***
////*******************************************************
////User        Date        Brief
////*******************************************************
////Maria       15Dec24     Created Main
////Yusuf       16Dec24     Created Test Cases Source File
////**/
