/*
 ============================================================================
 Name        : servo.h
 Module Name : SERVO MOTOR
 Author      : Ahmed Ali
 Date        : 3 July 2024
 Description : Header file for the SERVO driver
 ============================================================================
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	Degree_0, Degree_90, Degree_180
} ServoMotor_State;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SERVO_PORTID				PORTB_ID
#define SERVO_PINID  				PIN3_ID

#define OCR0_VALUE_FOR_0_DEGREES	62
#define OCR0_VALUE_FOR_90_DEGREES	93
#define OCR0_VALUE_FOR_180_DEGREES	124

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * 1. The Function responsible for setup the direction for the servo motor pins through the GPIO driver.
 * 2. Setup the timer0 driver with PWM mode.
 * 3. Set the servo in 0 degree position as initial state.
 */
void ServoMotor_init(void);

/*
 * Description :
 * 1. The function responsible for rotate the servo Motor 0, 90 or 180 degree
 *    based on the state input state value.
 */
void ServoMotor_Rotate(ServoMotor_State a_state);

#endif /* SERVO_H_ */
