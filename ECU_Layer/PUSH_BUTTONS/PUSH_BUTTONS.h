/***
==================================================================================
* @file     : PUSH_BUTTONS.h
* @author   : Maria George
* @version  : v1.2
* @brief    : Push Buttons Driver Header File
* @details  : Provides function prototypes for push button initialization and operations
==================================================================================
***/

#ifndef PUSH_BUTTONS_H_
#define PUSH_BUTTONS_H_

/*** ===================== Include Section Start =========================== ***/
#include "MCAL_Layer/MCAL_STD_TYPES.h"
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* Push Button Configuration Macros */
#define PB_PRESSED  0x00
#define PB_RELEASED 0x01

/* Button Identifiers */
#define PB_SW0   0x00  /* SW1 - PF4 */
#define PB_SW1   0x01  /* SW2 - PF0 */
#define PB_SW2   0x02  /* PB0 - PB0 */
#define PB_SW3   0x03  /* PB1 - PB1 */
/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void PUSH_BUTTONS_INIT(void);
uint8 PUSH_BUTTON_STATUS(uint8 button);  // Function to get push button status based on input
/*** ================= Global Declaration Section End ====================== ***/

#endif /* PUSH_BUTTONS_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Maria       07Dec24     Created Push Buttons Header File
Rawan       07Dec24     Included Macros
**/
