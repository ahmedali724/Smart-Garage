/*
 ============================================================================
 Name        : lamp.h
 Module Name : HAL
 Author      : Ahmed Ali
 Date        : 4 July 2024
 Description : Header file for the LAMP driver
 ============================================================================
 */

#ifndef LAMP_H_
#define LAMP_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LED_PORT  	PORTD_ID
#define LED_PIN  	PIN1_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void LAMP_init(void);

void LAMP_ON(void);

void LAMP_OFF(void);

#endif /* LAMP_H_ */
