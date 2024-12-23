/***
==================================================================================
* @file     : main.c
* @author   : Rawan Waleed
* @version  : v1.0
* @brief    : Application Main Run File
* @details  :
==================================================================================
***/


/*** ===================== Include Section Start =========================== ***/
#include <_1_MCAL_Layer/GPIO/GPIO.h>
#include <_1_MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.h>
#include <_1_MCAL_Layer/UART/UART.h>
#include <_1_MCAL_Layer/INTERRUPT/INTERRUPT.h>
#include <_1_MCAL_Layer/ADC/ADC.h>
#include <_1_MCAL_Layer/EEPROM/EEPROM.h>
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include <_2_ECU_Layer/DC_MOTOR/DC_MOTOR.h>
#include <_2_ECU_Layer/LCD/LCD.h>
#include <_2_ECU_Layer/PUSH_BUTTONS/PUSH_BUTTONS.h>
#include <_2_ECU_Layer/Ultrasonic/ULTRASONIC.h>
#include <_2_ECU_Layer/LM35/LM35.h>

/*** ===================== Include Section End ============================= ***/


/*** ================= Global Declaration Section Start ==================== ***/
void System_Init(void);
void Monitor_Subsystems(void);
char* To_String_Temp(uint32 number);
char* To_String_Dist(uint32 number);
void Update_LCD(void);
void Start_Operation(void);
void Stop_System(void);

/*** ================= Global Declaration Section End ====================== ***/


//int main(void)
//{
//
//    System_Init();
//    UART0_SendString("Please Enter one of these values (1, 2, 3) .\n");
//    while (1)
//    {
//
//
//        char command = UART0_ReceiveByte();        // Read command from the terminal
//        UART0_SendByte(command);
//        switch(command){
//        case '1':
//            Start_Operation();
//            break;
//        case '2':
//            Retrieve_Faults();
//            break;
//        case '3':
//            Stop_System();
//            //UART0_SendString("System Terminated.\n");
//            break;
//        default:
//            //UART0_SendString("Please Enter one of these values (1, 2, 3) .\n");
//            break;
//        }
//
//    }
//}
int main(void)
{
    char last_command = '\0'; // Variable to track the last command
    System_Init();

    UART0_SendString("Please Enter one of these values (1, 2, 3):\n");

    while (1)
    {
        char command = UART0_ReceiveByte();        // Read command from the terminal
        //UART0_SendByte(command);

        // Process the command only if it's different from the last command
        if (command != last_command)
        {
            last_command = command; // Update the last command

            switch (command)
            {
                case '1':
                    Start_Operation();
                    break;

                case '2':
                    Retrieve_Faults();
                    break;

                case '3':
                    Stop_System();
                    // UART0_SendString("System Terminated.\n");
                    break;

                default:
                    UART0_SendString("Invalid command. Please enter 1, 2, or 3:\n");
                    break;
            }
        }
    }
}

/*** ===================== System Initialization ======================= ***/
void System_Init(void){


   UART0_Init();
   SysTick_Init();
   ADC0_Init();

   /* initializing the EEPROM */
     if (EEPROM_INIT() == E_OK) {
         UART0_SendString((unsigned char *)"EEPROM Initialized Successfully!\n");
     } else {
         UART0_SendString((unsigned char *)"EEPROM Initialization Failed!\n");
         while (1); // Halt execution if EEPROM initialization fails
     }

   LCD_4BITS_INIT();
   LCD_4BITS_send_string("LETS START");
   SysTick_DelayMs(1000);
   LCD_4BITS_send_command(LCD_CLEAR);
   Ultrasonic_Init();
   UART0_SendString("Ultra\n");
   PUSH_BUTTONS_INIT();

   DC_MOTORA_INIT();
   UART0_SendString("Motors A\n");
   DC_MOTORB_INIT();\
   UART0_SendString("Motor B\n");

   UART0_SendString("Vehicle Fault Detection System Initialized.\n");
   LCD_4BITS_send_string("VFDS Initialized");
}


/*** ===================== Starting the operation======================= ***/
void Start_Operation(void)
{

    UART0_SendString("Starting the Operation.......\n");

        while (1) {
            char command = UART0_ReceiveByte();        // Read command from the terminal

            Monitor_Subsystems();
            SysTick_DelayMs(500);
            Update_LCD();

            if(command=='3'){
                Stop_System();
                UART0_SendString("System Terminated.\n");
                break;
            }
        }

}


/*** ===================== Functions related to Starting the operation======================= ***/
void Monitor_Subsystems(void){
    Monitor_TEMP();
    Monitor_DIST();
}

void Update_LCD(void){
    LCD_4BITS_send_command(LCD_CLEAR);
    uint64 engineTemperature = (LM35_GET_TEMP()+17);              /* Taking the temperature readings*/
    uint64 measured_Distance = Ultrasonic_GetDistance();     /* Taking the distance readings */

    // Convert temperature and distance to strings
    char* temp = To_String_Temp(engineTemperature);  // Ensure To_String returns a pointer to a valid string
    char* dist = To_String_Dist(measured_Distance);

    // Retrieve motor statuses as strings
    const char* motorA_status = Check_MotorA_status();
    const char* motorB_status = Check_MotorB_status();

    // Display temperature
    //LCD_4BITS_send_string_position((uint8_t*)"Temp=", 1, 0);
    LCD_4BITS_send_string("Temp=");
    LCD_4BITS_send_string_position((uint8*)temp, 1, 6);

    // Display distance
    LCD_4BITS_send_string_position((uint8*)"Dist=", 2, 0);
    LCD_4BITS_send_string_position((uint8*)dist, 2, 6);

    // Display motor statuses
    LCD_4BITS_send_string_position((uint8*)motorA_status, 1, 9);
    LCD_4BITS_send_string_position((uint8*)motorB_status, 2, 9);
}

char* To_String_Temp(uint32 number) {
    static char Str[3];

    // Convert the temperature into a string
    Str[0] = (number / 10) + '0';   // Tens digit
    Str[1] = (number % 10) + '0';   // Ones digit
    Str[2] = '\0';                       // Null-terminate the string

    // Return the formatted string
    return Str;
}
char* To_String_Dist(uint32 number) {
    static char Str[3];

    // Convert the temperature into a string
    Str[0] = (number / 10) + '0';   // Tens digit
    Str[1] = (number % 10) + '0';   // Ones digit
    Str[2] = '\0';                       // Null-terminate the string

    // Return the formatted string
    return Str;
}

/*** ===================== Stopping the system ======================= ***/
void Stop_System(void){
    LCD_4BITS_send_command(LCD_CLEAR);
    DC_MOTORA_STOP();
    DC_MOTORB_STOP();
}
