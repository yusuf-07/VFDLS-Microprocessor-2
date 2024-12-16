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
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/* Push Button Configuration Macros */
#define PB_PRESSED  0x00
#define PB_RELEASED 0x01

/* Button Identifiers */
#define PB_SW0   0x00  /* SW1 - PF4 */   /* used for Motor A counterclockwise*/
#define PB_SW1   0x01  /* SW2 - PF0 */   /* used for Motor A clockwise*/
#define PB_SW2   0x02  /* PB0 - PB0 */   /* used for Motor B counterclockwise*/
#define PB_SW3   0x03  /* PB1 - PB1 */   /* used for Motor B clockwise*/

/*interrupts related macros*/
/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

/*interrupt configuration macros for portF*/
#define GPIO_PORTF_PRIORITY_MASK          0x00E00000
#define GPIO_PORTF_PRIORITY_BITS_POS      21
#define GPIO_PORTF_INTERRUPT_PRIORITY     2

/*interrupt configuration macros for portB*/
#define GPIO_PORTB_PRIORITY_MASK          0x0000E000
#define GPIO_PORTB_PRIORITY_BITS_POS      13
#define GPIO_PORTB_INTERRUPT_PRIORITY     2

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
Rawan       12Dec24     Added interrupts macros
**/
