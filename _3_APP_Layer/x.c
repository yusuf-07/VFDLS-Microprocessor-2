///*
// * x.c
// *
// *  Created on: 24 Dec 2024
// *      Author: yabul
// */
//
////final micro code before bonus
//#include "tm4c123gh6pm_registers.h"
//#include "lcd.h"
//#include "GPIO.h"
//#include "lm35_sensor.h"
//#include "motor.h"
//#include "EEPROM.h"
//#include "UART.h"
//#include "ultrsonic_bool.h"
//
//
//#define MAX_TEMP 28
//
//pin_config_t MOTOR2_UP_BTN = {.port = PORTF_INDEX,.pin = GPIO_PIN0,.direction = GPIO_DIRECTION_INPUT,.logic = GPIO_LOW};
//pin_config_t MOTOR2_DOWN_BTN = {.port = PORTF_INDEX,.pin = GPIO_PIN4,.direction = GPIO_DIRECTION_INPUT,.logic = GPIO_LOW};
//pin_config_t MOTOR1_UP_BTN = {.port = PORTD_INDEX,.pin = GPIO_PIN0,.direction = GPIO_DIRECTION_INPUT,.logic = GPIO_LOW};
//pin_config_t MOTOR1_DOWN_BTN = {.port = PORTB_INDEX,.pin = GPIO_PIN0,.direction = GPIO_DIRECTION_INPUT,.logic = GPIO_LOW};
//
//pin_config_t BUZZER = {.port = PORTD_INDEX,.pin = GPIO_PIN7 ,.direction = GPIO_DIRECTION_OUTPUT,.logic = GPIO_LOW};
//
//
//uint8 BTN_OPEN_MOTOR1_STATUES = 0;
//uint8 BTN_CLOSE_MOTOR1_STATUES = 0;
//uint8 BTN_OPEN_MOTOR2_STATUES = 0;
//uint8 BTN_CLOSE_MOTOR2_STATUES = 0;
//
//
//uint8 flag_motor1_open = 0;
//uint8 flag_motor1_close = 0;
//uint8 mode = 0;
//uint8 mode_mob = 0;
//
//uint8 flag_motor2_open = 0;
//uint8 flag_motor2_close = 0;
//uint8 distance_flag=0;
//uint8 temp_flag=0;
//void application_initialize(void);
//void motor1_lcd_reading(void);
//void motor2_lcd_reading(void);
//void MODE_2(void);
//// Main function
//int main(void) {
//    uint8 distance = 0;
//    uint8 temp = 0;
//    application_initialize();
//
//    LCD_clearScreen();
//   // eeprom_clear_all();
//    uint8 TEMP_Error[]="ENGINE_HIGH_TEMPERATURE ";
//    uint8 DISTANCE_Error[]="ACCIDENT_MIGHT_HAPPEN";
//    while(1){
//          do{
//            mode=UART_receiveByte();
//             UART_sendByte(mode);
//
//
//
//          }while((mode != '1') );
//
//
//
//        while(1){
//
//            LCD_clearScreen();
//
//            temp = LM35_getTemperature();
//
//                        distance = ultrasonic_bool_measureDistance();
//                        while(distance <=20){
//                            if(distance<10){
//                                GPIO_writePin(&BUZZER, GPIO_HIGH);
//
//                                if(distance_flag==0){
//                                UART_sendString(DISTANCE_Error);
//
//                                eeprom_writeString("P001", 4, 0);
//                                distance_flag++;
//                                }
//
//
//                            }
//
//                            //distance_flag=0;
//                            LCD_clearScreen();
//
//                            LCD_displayString("DIS= ");
//                            LCD_intgerToString(distance);
//                            distance = ultrasonic_bool_measureDistance();
//                            _delay_ms(150);
//                        }
//                        GPIO_writePin(&BUZZER, GPIO_LOW);
//                        LCD_clearScreen();
//                       LCD_displayString("TEMPERATURE= ");
//                       LCD_intgerToString(temp);
//                       LCD_displayString("C");
//                       LCD_moveCursor(1, 0);
//                       motor1_lcd_reading();
//                       motor2_lcd_reading();
//                       if(temp>=MAX_TEMP){
//                         if(temp_flag==0){
//                            UART_sendString(TEMP_Error);
//
//                          eeprom_writeString("P002", 0, 0);
//                          temp_flag++;
//                       }}
//                         //temp_flag=0;
//                       mode=UART_receiveByte();
//                       UART_sendByte(mode);
////                       mode_mob=UART1_receiveByte();
//                       if((mode=='2') ){
//                           MODE_2();
//                       }
//                       if((mode=='3') ){
//                           LCD_clearScreen();
//                           LCD_displayString("Program finished");
//                           break;
//                                  // _delay_ms(500);
//                         // return 0;
//                                                 }
//
//                       _delay_ms(500);
//        }
//
//
//
//    }
//    return 0;
//}
//
//void MODE_2(void){
//    char tempp[20];
//    char distt[20];
//    eeprom_readString(tempp, 0, 0, 4);
//    eeprom_readString(distt, 4, 0, 4);
//    LCD_clearScreen();
//    LCD_displayString(distt);
//    LCD_moveCursor(1, 0);
//    LCD_displayString(tempp);
//    while(1){
//        mode=UART_receiveByte();
//         UART_sendByte(mode);
//         if((mode=='3')){
//            _delay_ms(15);
//           if((mode=='3')){
//            LCD_clearScreen();
//           LCD_displayString("Program finished");
//               break;
//                              //_delay_ms(500);
//              }
//         }
//           else if((mode=='1')){
//               break;
//           }
//
//
//    }
//
//}
//void application_initialize(void){
//
//    UART_init(9600);
//
//    LCD_init();
//    eeprom_init();
//    ultrasonic_bool_init();
//    ADC_Init();
//
//    Motor1_Init();
//    Motor2_Init();
//    GPIO_setupPinDirection(&MOTOR1_UP_BTN);
//    GPIO_setupPinDirection(&MOTOR1_DOWN_BTN);
//    GPIO_setupPinDirection(&MOTOR2_UP_BTN);
//    GPIO_setupPinDirection(&MOTOR2_DOWN_BTN);
//    GPIO_setupPinDirection(&BUZZER);
//
//}
//
//void motor1_lcd_reading(void){
//    LCD_moveCursor(1, 0);
//    LCD_displayString("M1:");
//
//                            GPIO_readPin(&MOTOR1_DOWN_BTN, &BTN_OPEN_MOTOR1_STATUES);
//                              GPIO_readPin(&MOTOR1_UP_BTN, &BTN_CLOSE_MOTOR1_STATUES);
//                                          if(BTN_OPEN_MOTOR1_STATUES == GPIO_LOW){
//                                              _delay_ms(15);
//                                              if(BTN_OPEN_MOTOR1_STATUES == GPIO_LOW){
//                                                  flag_motor1_open = 1;
//                                                 flag_motor1_close = 0;
//                                                 Motor1_Rotate(cw);
//                                              }
//
//                                          }
//
//                                          else  if(BTN_CLOSE_MOTOR1_STATUES == GPIO_LOW){
//                                                    _delay_ms(15);
//                                               if(BTN_CLOSE_MOTOR1_STATUES == GPIO_LOW){
//                                                   flag_motor1_open = 0;
//                                                    flag_motor1_close = 1;
//                                                    Motor1_Rotate(acw);
//                                                   }
//                                              }
//                                          else{
//                                              Motor1_Rotate(stop);
//                                              }
//
//
//                                          /* Read the state of Motor 1 buttons */
//                                          GPIO_readPin(&MOTOR1_DOWN_BTN, &BTN_OPEN_MOTOR1_STATUS);
//                                          GPIO_readPin(&MOTOR1_UP_BTN, &BTN_CLOSE_MOTOR1_STATUS);
//
//                                          if (BTN_OPEN_MOTOR1_STATUS == GPIO_LOW)
//                                          {
//                                              _delay_ms(15);
//                                              if (BTN_OPEN_MOTOR1_STATUS == GPIO_LOW)
//                                              {
//                                                  flag_motor1_open = 1;
//                                                  flag_motor1_close = 0;
//                                                  Motor1_Rotate(CW); /* Rotate Motor 1 Clockwise */
//                                              }
//                                          }
//                                          else if (BTN_CLOSE_MOTOR1_STATUS == GPIO_LOW)
//                                          {
//                                              _delay_ms(15);
//                                              if (BTN_CLOSE_MOTOR1_STATUS == GPIO_LOW)
//                                              {
//                                                  flag_motor1_open = 0;
//                                                  flag_motor1_close = 1;
//                                                  Motor1_Rotate(ACW); /* Rotate Motor 1 Anti-Clockwise */
//                                              }
//                                          }
//                                          else
//                                          {
//                                              Motor1_Rotate(STOP); /* Stop Motor 1 */
//                                          }
//
//  if(flag_motor1_open == 1){
//              LCD_displayStringRowColumn(1, 3, "DOWN");
//   }
// if(flag_motor1_close == 1){
//     LCD_displayStringRowColumn(1, 3, "UP");
//      }
//}
//
//void motor2_lcd_reading(void){
//    LCD_moveCursor(1, 8);
//    LCD_displayString("M2:");
//
//                          GPIO_readPin(&MOTOR2_DOWN_BTN, &BTN_OPEN_MOTOR2_STATUES);
//                          GPIO_readPin(&MOTOR2_UP_BTN, &BTN_CLOSE_MOTOR2_STATUES);
//                                      if(BTN_OPEN_MOTOR2_STATUES == GPIO_LOW){
//                                          _delay_ms(15);
//                                          if(BTN_OPEN_MOTOR2_STATUES == GPIO_LOW){
//                                              flag_motor2_open = 1;
//                                             flag_motor2_close = 0;
//                                             Motor2_Rotate(cw);
//                                          }
//
//                                      }
//
//                                      else  if(BTN_CLOSE_MOTOR2_STATUES == GPIO_LOW){
//                                                _delay_ms(15);
//                                           if(BTN_CLOSE_MOTOR2_STATUES == GPIO_LOW){
//                                               flag_motor2_open = 0;
//                                                flag_motor2_close = 1;
//                                                Motor2_Rotate(acw);
//                                               }
//                                          }
//                                      else{
//                                          Motor2_Rotate(stop);
//                                          }
//  if(flag_motor2_open == 1){
//              LCD_displayStringRowColumn(1, 12, "DOWN");
//   }
// if(flag_motor2_close == 1){
//     LCD_displayStringRowColumn(1, 12, "UP");
//      }
//}
//
//
