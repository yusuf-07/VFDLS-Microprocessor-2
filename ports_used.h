/***
==================================================================================
* @file     : ports_used.h
* @author   : Yusuf
* @version  : v1.0
* @brief    : Ports Used Header File
* @details  : Defines port pin assignments for switches and LCD connections
==================================================================================
***/

#ifndef PORTS_USED_H_
#define PORTS_USED_H_

/*** ====================== Switches ======================= ***/
/***
 * Port F Pin 4 for Switch 0
 * Port F Pin 0 for Switch 1
 * Port B Pin 0 for Switch 2
 * Port B Pin 1 for Switch 3
 ***/

/*** ====================== LCD =========================== ***/
/***
 * Port A Pin 3 for Data Line
 * Port A Pin 4 for Data Line
 * Port A Pin 5 for Data Line
 * Port A Pin 6 for Data Line
 * Port E Pin 1 for Rs
 * Port E Pin 2 for R/W
 * Port E Pin 3 for Enable
 ***/

/*** ====================== UART ========================== ***/
/***
 * Port A Pin 0 for Rx
 * Port A Pin 1 for Tx
 ***/

/*** ====================== DC_MOTOR ========================== ***/
/***
 * Port B Pin 2 for IN1
 * Port B Pin 3 for IN2
 * Port B Pin 4 for IN3
 * Port B Pin 5 for IN4
 * Port B Pin 6 for ENA
 * Port B Pin 7 for ENB
 ***/

/*** ====================== Ultrasonic ========================== ***/
/***
 * Port B Pin 5 for Trigger
 * Port B Pin 6 for Echo

 ***/

/*** ========================== ADC ============================== ***/
/***
 * Port E Pin 0 for connection to AIN3 (ADC Channel 3)

 ***/

/**
*******************************************************
User        Date        Brief
*******************************************************
Yusuf       07Dec24     Created Ports Used Header File
**/



#endif /* PORTS_USED_H_ */
