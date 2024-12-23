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
#include <_2_ECU_Layer/Flex_Sensor/Flex_Sensor.h>
#include <_2_ECU_Layer/LCD/LCD.h>
#include <_2_ECU_Layer/PUSH_BUTTONS/PUSH_BUTTONS.h>
#include <_2_ECU_Layer/Ultrasonic/ULTRASONIC.h>
#include <_2_ECU_Layer/LM35/LM35.h>

/*** ===================== Include Section End ============================= ***/

static volatile uint8 motorA_state = 0;  // 0: Stop, 1: Start CCW, 2: Start CW
static volatile uint8 motorB_state = 0;  // 0: Stop, 1: Start CCW, 2: Start CW

static volatile uint8 MotorA_Status = 0;
static volatile uint8 MotorB_Status = 0;
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND    364
static void Delay_MS(unsigned long long n);
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
//
//    System_Init();
//    //Clear_Logged_Errors();
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
//            UART0_SendString("System Terminated.\n");
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
    //Clear_Logged_Errors();

    UART0_SendString("Please Enter one of these values (1, 2, 3):\n");

    while (last_command != 1)
    {
        char command = UART0_ReceiveByte();        // Read command from the terminal
        //UART0_SendByte(command);
        if (command != 0xFF)
        {

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
                                UART0_SendString("System Terminated.\n");
                                last_command = 1; //termination flag
                                break;
                            case '4':  // Display flex sensor readings
                                UART0_SendString("Fetching Flex Sensor Pressure...\n");
                                Display_Pressure(); // Call function to display pressure
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
   ADC1_Init(ADC_CHANNEL5);

   /* initializing the EEPROM */
     if (EEPROM_INIT() == E_OK) {
         UART0_SendString((unsigned char *)"EEPROM Initialized Successfully!\n");
     } else {
         UART0_SendString((unsigned char *)"EEPROM Initialization Failed!\n");
         while (1); // Halt execution if EEPROM initialization fails
     }

   LCD_4BITS_INIT();
   LCD_4BITS_send_string("LETS START");
   Delay_MS(1000);
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
            Delay_MS(500);
            Update_LCD();
            if(command == '2')
            {
                UART0_SendString("Exiting System Operations\n");
                break;
            }

            else if(command=='3'){
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

void Update_LCD(void)
{
    LCD_4BITS_send_command(LCD_CLEAR);
    uint64 engineTemperature = (LM35_GET_TEMP()+17);              /* Taking the temperature readings*/
    uint64 measured_Distance = Ultrasonic_GetDistance();     /* Taking the distance readings */

    // Convert temperature and distance to strings
    char* temp = To_String_Temp(engineTemperature);  // Ensure To_String returns a pointer to a valid string
    char* dist = To_String_Dist(measured_Distance);


    // Display temperature
    //LCD_4BITS_send_string_position((uint8_t*)"Temp=", 1, 0);
    LCD_4BITS_send_string("Temp=");
    LCD_4BITS_send_string_position((uint8*)temp, 1, 6);
    if (measured_Distance < 20)
    {
        // Display distance
        LCD_4BITS_send_string_position((uint8*)"Dist=", 2, 0);
        LCD_4BITS_send_string_position((uint8*)dist, 2, 6);
    }
    else
    {
        LCD_4BITS_send_string_position("OutofRange",2,0);
    }



    // Retrieve motor statuses as strings
    const char* motorA_status = Check_MotorA_status();
    // Display motor statuses
    LCD_4BITS_send_string_position((uint8*)motorA_status, 1, 9);

    // Retrieve motor statuses as strings
    const char* motorB_status = Check_MotorB_status();
    // Display motor statuses
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
    GPIO_PORTB_DATA_REG &= ~ (1<<ENA_PIN);
    DC_MOTORB_STOP();
    GPIO_PORTB_DATA_REG &= ~ (1<<ENB_PIN);
}
void Delay_MS(unsigned long long n){
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n));
}
