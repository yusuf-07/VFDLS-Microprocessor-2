/***
==================================================================================
* @file     : DC_MOTOR_TYPES.h
* @author   : Maria George
* @version  : v1.2
* @brief    : DC Motor Types Driver Header File
* @details  : Provides function prototypes for DC Motor Types initialization and operations
==================================================================================
***/

#ifndef ECU_LAYER_DC_MOTOR_DC_MOTOR_TYPES_H_
#define ECU_LAYER_DC_MOTOR_DC_MOTOR_TYPES_H_

typedef enum
{
    DC_MOTOR_A,
    DC_MOTOR_B

}DC_MOTOR_T;

typedef enum
{
    DIR_CW,
    DIR_CCW
}DC_DIR_T;

#endif /* ECU_LAYER_DC_MOTOR_DC_MOTOR_TYPES_H_ */

/**
*******************************************************
User        Date        Brief
*******************************************************
Maria       07Dec24     Created DC Motor Types Header File
**/
