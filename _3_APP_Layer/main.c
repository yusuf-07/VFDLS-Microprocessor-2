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
char* To_String(uint32 number);
void Update_LCD(void);
void Start_Operation(void);
void Stop_System(void);

/*** ================= Global Declaration Section End ====================== ***/


int main(void) {

    System_Init();

    while (1) {

        char command = UART0_ReceiveByte();        // Read command from the terminal
        UART0_SendString("Please Enter one of these values (1, 2, 3) .\n");

        switch(command){
        case '1':
            Start_Operation();
            break;
        case '2':
            Retrieve_Faults();
            break;
        case '3':
            Stop_System();
            UART0_SendString("System Terminated.\n");
            break;
        default:
            UART0_SendString("Please Enter one of these values (1, 2, 3) .\n");
            break;
        }

    }
}

/*** ===================== System Initialization ======================= ***/
void System_Init(void){


   UART0_Init();
   SysTick_Init(15999999);
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
   PUSH_BUTTONS_INIT();

   DC_MOTORA_INIT();
   DC_MOTORB_INIT();

   UART0_SendString("Vehicle Fault Detection System Initialized.\n");
   LCD_4BITS_send_string("VFDS Initialized");
}


/*** ===================== Starting the operation======================= ***/
void Start_Operation(void){

    UART0_SendString("Starting the Operation.......\n");

        while (1) {
            char command = UART0_ReceiveByte();        // Read command from the terminal

            Monitor_Subsystems();
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
    uint32 engineTemperature = LM35_GET_TEMP();              /* Taking the temperature readings*/
    //uint32 measured_Distance = Ultrasonic_GetDistance();     /* Taking the distance readings */

    // Convert temperature and distance to strings
    char* temp = To_String(engineTemperature);  // Ensure To_String returns a pointer to a valid string
    //char* dist = To_String(measured_Distance);

    // Retrieve motor statuses as strings
    const char* motorA_status = Check_MotorA_status();
    const char* motorB_status = Check_MotorB_status();

    // Display temperature
    //LCD_4BITS_send_string_position((uint8_t*)"Temp=", 1, 0);
    LCD_4BITS_send_string("Temp=");
    LCD_4BITS_send_string_position((uint8_t*)temp, 1, 6);

    // Display distance
    LCD_4BITS_send_string_position((uint8_t*)"Dist=", 2, 0);
    //LCD_4BITS_send_string_position((uint8_t*)dist, 2, 6);

    // Display motor statuses
    LCD_4BITS_send_string_position((uint8_t*)motorA_status, 1, 9);
    LCD_4BITS_send_string_position((uint8_t*)motorB_status, 2, 9);
}

char* To_String(uint32 number) {
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
