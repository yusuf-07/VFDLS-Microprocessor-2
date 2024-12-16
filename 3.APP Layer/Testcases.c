/***
==================================================================================
* @file     : TEST_CASES.c
* @author   : Yusuf Abulfotouh
* @version  : v1.0
* @brief    : Test cases for GPIO, Ultrasonic, and LCD functionalities
* @details  : Implements scenarios to test GPIO configurations, ultrasonic measurements,
*             and LCD displays.
==================================================================================
***/

/*** ===================== Include Section Start =========================== ***/
#include "GPIO.h"
#include "ULTRASONIC.h"
#include "LCD.h"
/*** ===================== Include Section End ============================= ***/

/*** ===================== Public Function Section Start ===================== ***/

/***
* @brief    : Test Case 1 - Configure an LED as Output
* @param    : None
* @return   : None
***/
void Test_LED_Output(void)
{
    /* Initialize PF1 as Digital Output (LED) */
    GPIO_InitPin(GPIO_PORTF, 1, GPIO_DIGITAL, GPIO_OUTPUT, 0);

    /* Turn LED ON */
    GPIO_SetPinLogic(GPIO_PORTF, 1, GPIO_HIGH);
    SysTick_DelayMs(1000); /* Wait 1 second */

    /* Turn LED OFF */
    GPIO_SetPinLogic(GPIO_PORTF, 1, GPIO_LOW);
    SysTick_DelayMs(1000); /* Wait 1 second */
}

/***
* @brief    : Test Case 2 - Configure a Push Button as Input
* @param    : None
* @return   : None
***/
void Test_PushButton_Input(void)
{
    /* Initialize PF4 as Digital Input with Pull-Up (Push Button) */
    GPIO_InitPin(GPIO_PORTF, 4, GPIO_DIGITAL, GPIO_INPUT, 0);
    GPIO_ConfigurePull(GPIO_PORTF, 4, GPIO_PULL_UP);

    while (1)
    {
        if (GPIO_GetPinLogic(GPIO_PORTF, 4) == GPIO_LOW)
        {
            /* Button Press Detected */
            GPIO_SetPinLogic(GPIO_PORTF, 1, GPIO_HIGH); /* Turn LED ON */
        }
        else
        {
            GPIO_SetPinLogic(GPIO_PORTF, 1, GPIO_LOW); /* Turn LED OFF */
        }
    }
}

/***
* @brief    : Test Case 3 - Toggle an LED Using a Push Button
* @param    : None
* @return   : None
***/
void Test_LED_Toggle_With_Button(void)
{
    /* Initialize PF1 as Output (LED) and PF4 as Input (Button) */
    GPIO_InitPin(GPIO_PORTF, 1, GPIO_DIGITAL, GPIO_OUTPUT, 0);
    GPIO_InitPin(GPIO_PORTF, 4, GPIO_DIGITAL, GPIO_INPUT, 0);
    GPIO_ConfigurePull(GPIO_PORTF, 4, GPIO_PULL_UP);

    while (1)
    {
        if (GPIO_GetPinLogic(GPIO_PORTF, 4) == GPIO_LOW)
        {
            /* Toggle LED */
            GPIO_SetPinLogic(GPIO_PORTF, 1, !GPIO_GetPinLogic(GPIO_PORTF, 1));

            /* Wait for Button Release */
            while (GPIO_GetPinLogic(GPIO_PORTF, 4) == GPIO_LOW);
        }
    }
}

/***
* @brief    : Test Case 4 - Measure a Known Distance Using Ultrasonic Sensor
* @param    : None
* @return   : None
***/
void Test_Ultrasonic_Known_Distance(void)
{
    /* Initialize Ultrasonic and LCD */
    Ultrasonic_Init();
    LCD_4BITS_INIT();

    while (1)
    {
        /* Measure Distance */
        uint32 distance = Ultrasonic_GetDistance();

        /* Display on LCD */
        char distance_text[16];
        sprintf(distance_text, "Distance: %d cm", distance);
        LCD_4BITS_send_string_position(distance_text, ROW1, 1);

        /* Add Delay */
        SysTick_DelayMs(1000);
    }
}

/***
* @brief    : Test Case 5 - Measure Minimum and Maximum Distances
* @param    : None
* @return   : None
***/
void Test_Ultrasonic_MinMax_Distance(void)
{
    /* Initialize Ultrasonic */
    Ultrasonic_Init();

    while (1)
    {
        /* Measure Distance */
        uint32 distance = Ultrasonic_GetDistance();

        /* Check Min and Max Range */
        if (distance < 2)
        {
            LCD_4BITS_send_string_position("Too Close!", ROW1, 1);
        }
        else if (distance > 400)
        {
            LCD_4BITS_send_string_position("Out of Range!", ROW1, 1);
        }
        else
        {
            char distance_text[16];
            sprintf(distance_text, "Distance: %d cm", distance);
            LCD_4BITS_send_string_position(distance_text, ROW1, 1);
        }

        /* Add Delay */
        SysTick_DelayMs(1000);
    }
}

/***
* @brief    : Test Case 6 - Validate Ultrasonic Interrupt Functionality
* @param    : None
* @return   : None
***/
void Test_Ultrasonic_Interrupts(void)
{
    /* Initialize Ultrasonic */
    Ultrasonic_Init();

    /* Wait for Echo Pin Interrupts */
    while (1)
    {
        if (!edge_detected)
        {
            /* Measure Distance */
            uint32 distance = measured_distance;

            /* Display on LCD */
            char distance_text[16];
            sprintf(distance_text, "Distance: %d cm", distance);
            LCD_4BITS_send_string_position(distance_text, ROW1, 1);
        }
    }
}

/***
* @brief    : Test Case 7 - Display Static Text on LCD
* @param    : None
* @return   : None
***/
void Test_LCD_Static_Text(void)
{
    /* Initialize LCD */
    LCD_4BITS_INIT();

    /* Display Text */
    LCD_4BITS_send_string("Hello World!");
}

/***
* @brief    : Test Case 8 - Display Measured Distance on LCD
* @param    : None
* @return   : None
***/
void Test_LCD_Distance(void)
{
    /* Initialize Ultrasonic and LCD */
    Ultrasonic_Init();
    LCD_4BITS_INIT();

    while (1)
    {
        /* Measure Distance */
        uint32 distance = Ultrasonic_GetDistance();

        /* Display Distance on LCD */
        char distance_text[16];
        sprintf(distance_text, "Distance: %d cm", distance);
        LCD_4BITS_send_string_position(distance_text, ROW1, 1);

        /* Add Delay */
        SysTick_DelayMs(1000);
    }
}

/***
* @brief    : Test Case 9 - Real-Time Distance Display on LCD
* @param    : None
* @return   : None
***/
void Test_LCD_RealTime_Distance(void)
{
    /* Initialize Ultrasonic and LCD */
    Ultrasonic_Init();
    LCD_4BITS_INIT();

    while (1)
    {
        /* Continuously Measure and Display Distance */
        uint32 distance = Ultrasonic_GetDistance();

        /* Display Real-Time Distance on LCD */
        char distance_text[16];
        sprintf(distance_text, "Dist: %d cm", distance);
        LCD_4BITS_send_string_position(distance_text, ROW1, 1);

        /* Short Delay to Update */
        SysTick_DelayMs(500);
    }
}

/*** ===================== Public Function Section End ======================= ***/

/***
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       16Dec24     Created Test Cases Source File
**/
