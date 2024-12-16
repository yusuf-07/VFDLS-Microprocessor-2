/***
==================================================================================
* @file     : DC_MOTOR.h
* @author   : Maria George
* @version  : v1.2
* @brief    : DC Motor Driver Header File
* @details  : Provides function prototypes for DC Motor initialization and operations
==================================================================================
***/

#ifndef 2_ECU_LAYER_DC_MOTOR_DC_MOTOR_H_
#define 2_ECU_LAYER_DC_MOTOR_DC_MOTOR_H_

/*** ===================== Include Section Start =========================== ***/
#include <1.MCAL_Layer/MCAL_STD_TYPES.h>
#include <2.ECU_Layer/DC_MOTOR/DC_MOTOR_TYPES.h>

/*** ===================== Include Section End ============================= ***/

/*** ====================== Macros Section Start =========================== ***/
/***
 * Port B Pin 2 for IN1
 * Port B Pin 3 for IN2
 * Port B Pin 4 for IN3
 * Port B Pin 5 for IN4
 * Port B Pin 6 for ENA
 * Port B Pin 7 for ENB
 ***/
#define IN1_PIN     2
#define IN2_PIN     3
#define IN3_PIN     4
#define IN4_PIN     5
#define ENA_PIN     6
#define ENB_PIN     7

/*** ====================== Macros Section End ============================= ***/

/*** ================= Global Declaration Section Start ==================== ***/
void DC_MOTORA_INIT(void);
void DC_MOTORA_START(DC_DIR_T DCdir);
void DC_MOTORA_STOP(void);

void DC_MOTORB_INIT(void);
void DC_MOTORB_START(DC_DIR_T DCdir);
void DC_MOTORB_STOP(void);
/*** ================= Global Declaration Section End ====================== ***/

#endif /* 2_ECU_LAYER_DC_MOTOR_DC_MOTOR_H_ */
/**
*******************************************************
User        Date        Brief
*******************************************************
Maria       07Dec24     Created DC Motor Header File
**/
