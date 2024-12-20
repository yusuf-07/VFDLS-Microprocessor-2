/*
 * EEPROM.h
 *
 *  Created on: Dec 20, 2024
 *      Author: Rawan Waleed
 */

#ifndef _1_MCAL_LAYER_EEPROM_EEPROM_H_
#define _1_MCAL_LAYER_EEPROM_EEPROM_H_

/*-----------------------Includes-----------------------*/
#include <_1_MCAL_Layer/MCAL_STD_TYPES.h>
#include <_1_MCAL_Layer/UART/UART.h>
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include <stdint.h>
#include <stdbool.h>

/*------------------Macros Declarations------------------*/

#define EEPROM_BASE_ADDRESS 0x00

// Status Flags
#define EEDONE_WORKING   0x01      /* Busy status */
#define EEDONE_NOPERM    0x04      /* No permission */
#define EEDONE_WKERASE   0x08      /* Write/Erase error */
#define EEDONE_WKCOPY    0x10      /* Write/Copy error */

#define EEPROM_EEDONE_WORKING   0x00000001
#define EEPROM_EESUPP_PRETRY    0x00000002  // Programming Retry Error (error during a write operation)
#define EEPROM_EESUPP_ERETRY    0x00000004  // Erase Retry Error (error during an erase operation)


// Unlock Key
#define EEPROM_UNLOCK_KEY 0x1ACCE551



/*-------------Macros Functions Declarations-------------*/


/*-----------------Data Type Declarations-----------------*/

/*-----------------Functions Declarations-----------------*/
Std_ReturnType EEPROM_INIT(void);
void EEPROM_Write(uint32_t address, uint32_t data);
uint32_t EEPROM_Read(uint32_t address);
void Log_Fault(char* faultCode);
void Format_FaultCode(uint32_t faultValue, char *faultCode);
void Retrieve_Faults(void);




#endif /* _1_MCAL_LAYER_EEPROM_EEPROM_H_ */





