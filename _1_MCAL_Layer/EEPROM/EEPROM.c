/*
 * EEPROM.c
 *
 *  Created on: Dec 20, 2024
 *      Author: Rawan Waleed
 */

#include <stdint.h>
#include <_1_MCAL_Layer/EEPROM/EEPROM.h>

Std_ReturnType EEPROM_INIT(void){
    /*EEPROMInitialization and Configuration
    Before writing to any EEPROMregisters, the clock to the EEPROMmodulemustbeenabledthrough
    the EEPROMRunModeClockGatingControl(RCGCEEPROM)register(seepage356)andthe
    following initialization steps must be executed:
    1. Insert delay (6 cycles plus function call overhead).
    2. Poll the WORKING bit in the EEPROM Done Status(EEDONE)register until it is clear,indicating
    that the EEPROM has completed its power-on initialization. When WORKING=0, continue.
    3. Read the PRETRY and ERETRY bits in the EEPROM Support Control and Status (EESUPP)
    register. If either of the bits are set, return an error, else continue.
    4. Reset the EEPROM module using the EEPROM Software Reset (SREEPROM) register at
    offset 0x558 in the System Control register space.
    5. Insert delay (6 cycles plus function call overhead).
    6. Poll the WORKING bit in the EEPROM Done Status (EEDONE) register to determine when it is
    clear. When WORKING=0, continue.
    7. Read the PRETRY and ERETRY bits in the EESUPP register. If either of the bits are set, return
    an error, else the EEPROM initialization is complete and software may use the peripheral as
    normal.*/

    //enable clock
    SYSCTL_RCGCEEPROM_REG = 1;

    //wait for clock to start
    while ((SYSCTL_RCGCEEPROM_REG & 1) == 0);

    //1. Insert delay (6 cycles plus function call overhead).
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");

    /* Check if there are any write/erase errors or if it needs unlocking */
    if (EEPROM_EEDONE_REG & (EEDONE_WKERASE | EEDONE_WKCOPY)) {
        EEPROM_EEUNLOCK_REG = 0x1ACCE551;                 /* Unlock EEPROM with the predefined key */
    }

    //2. Poll the WORKING bit in the EEPROM Done Status(EEDONE)register until it is clear
    while (EEPROM_EEDONE_REG & EEPROM_EEDONE_WORKING); //whether the EEPROM is currently busy performing a read or write operation. will keep checking the status of EEPROM until it is not busy


    // 3. Read the PRETRY and ERETRY bits in (EESUPP) register to check for errors.
    if (EEPROM_EESUPP_REG & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY)){
        return E_NOT_OK; // Return an error if either bit is set
        }//if non-zero at least there is one error

    // 4. Reset the EEPROM module
    EEPROM_SREEPROM_R = 1;
    EEPROM_SREEPROM_R = 0;

    //5. Insert delay (6 cycles plus function call overhead).
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");
    __asm(" NOP");

    //6. Poll the WORKING bit in the EEPROM Done Status (EEDONE) register. When WORKING=0, continue
    while (EEPROM_EEDONE_REG & EEPROM_EEDONE_WORKING);

    // Step 8: Read the PRETRY and ERETRY bits again
    if (EEPROM_EESUPP_REG & (EEPROM_EESUPP_PRETRY | EEPROM_EESUPP_ERETRY)) {
        return E_NOT_OK; // Return an error if either bit is set
    }

    // Initialization successful
    return E_OK;
}


void EEPROM_Write(uint32_t address, uint32_t data){
    /* Wait for EEPROM to be ready */
    while (EEPROM_EEDONE_REG & EEDONE_WORKING);

    /* Set block and offset registers */
    EEPROM_EEBLOCK_REG = address >> 4;         /* Block address (upper 6 bits) */
    EEPROM_EEOFFSET_REG = address & 0x0F;      /* Offset within the block (lower 6 bits) */

    /* Write data to the EEPROM */
    EEPROM_EERDWR_REG = data;

    /* Wait for the write operation to complete */
    while (EEPROM_EEDONE_REG & EEDONE_WORKING);

    /* Check for any errors */
    if (EEPROM_EEDONE_REG & (EEDONE_WKERASE | EEDONE_WKCOPY | EEDONE_NOPERM)) {
        // TO_DO: Error handling
        UART0_SendString("Error writing in the EEPROM...\n");
    }
}

uint32_t EEPROM_Read(uint32_t address) {
    /* Wait for EEPROM to be ready */
    while (EEPROM_EEDONE_REG & EEDONE_WORKING);

    /* Set block and offset registers */
    EEPROM_EEBLOCK_REG = address >> 4;         /* Block address (upper 6 bits) */
    EEPROM_EEOFFSET_REG = address & 0x0F;      /* Offset within the block (lower 6 bits) */

    /* Return the read value from the EEPROM */
    return EEPROM_EERDWR_REG;
}

void Log_Fault(char* faultCode) {
    static uint32_t currentAddress = EEPROM_BASE_ADDRESS;

    /* Convert the fault code string into a 32-bit value */
    uint32_t faultValue = *((uint32_t*)faultCode);

    /* Write the fault code to EEPROM */
    EEPROM_Write(currentAddress, faultValue);

    /* Increment the address for the next fault code */
    currentAddress += 4;       /* Move to the next 32-bit slot */
}

void Retrieve_Faults(void){

    UART0_SendString((unsigned char *)"Fault Log:\n");

    uint32_t address = EEPROM_BASE_ADDRESS;
    uint32_t faultValue;

    while (1) {
        faultValue = EEPROM_Read(address);

        /* Stop if the slot is empty (default EEPROM value is 0xFFFFFFFF) */
        /* EEPROM memory is typically erased (or initialized) to all 1s before any data is written */
        if (faultValue == 0xFFFFFFFF) {
            //UART0_SendString((unsigned char *)"There are no logged errors\n");
            break;
        }

        // Format the fault value into a string
        char faultCode[5];
        Format_FaultCode(faultValue, faultCode);

        // Send the fault code over UART
        UART0_SendString((unsigned char *)faultCode);
        UART0_SendString((unsigned char *)"\n");

        address += 4; // Move to the next EEPROM address
    }
}


void Format_FaultCode(uint32_t faultValue, char *faultCode) {
    // Extract characters from the 32-bit fault value in correct order
        faultCode[0] = (char)(faultValue & 0xFF);         // First byte (LSB)
        faultCode[1] = (char)((faultValue >> 8) & 0xFF);  // Second byte
        faultCode[2] = (char)((faultValue >> 16) & 0xFF); // Third byte
        faultCode[3] = (char)((faultValue >> 24) & 0xFF); // Fourth byte (MSB)
        faultCode[4] = '\0';
}

void Clear_Logged_Errors(void) {
    UART0_SendString((unsigned char *)"Clearing all logged errors...\n");

    uint32_t address = EEPROM_BASE_ADDRESS;

    while (1) {
        uint32_t faultValue = EEPROM_Read(address);

        // Stop if the slot is empty (default EEPROM value is 0xFFFFFFFF)
        if (faultValue == 0xFFFFFFFF) {
            break;
        }

        // Overwrite the slot with the default erased value
        EEPROM_Write(address, 0xFFFFFFFF);

        address += 4; // Move to the next EEPROM address
    }

    UART0_SendString((unsigned char *)"All logged errors cleared.\n");
}



