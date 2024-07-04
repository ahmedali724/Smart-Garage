/*
 ============================================================================
 Name        : servo.c
 Module Name : SERVO MOTOR
 Author      : Ahmed Ali
 Date        : 3 July 2024
 Description : Source file for the SERVO driver
 ============================================================================
 */

#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER0/timer0.h"
#include "servo.h"
#include "../../LIB/common_macros.h"

/*
 * Description :
 * 1. The Function responsible for setup the direction for the servo motor pins through the GPIO driver.
 * 2. Setup the timer0 driver with PWM mode.
 * 3. Set the servo in 0 degree position as initial state.
 */
void ServoMotor_init(void)
{
	/* Set The Configuration Of Timer0 To Be in FAST PWM Mode */
	TIMER0_ConfigType TIMER0_CONFIG =
	{ 0, 0, FAST_PWM_MODE, PRESCALER_256, CTC_CLEAR__PWM_NON_INVERTING };

	/* Init Timer0 in FAST PWM Mode */
	Timer0_init(&TIMER0_CONFIG);

	/* Set OC0 pin direction as output */
	GPIO_setupPinDirection(OC0_PORTID, OC0_PINID, PIN_OUTPUT);

	/* Set the servo in 0 degree position as initial state */
	Timer0_PWM_Start(OCR0_VALUE_FOR_0_DEGREES);
}

/*
 * Description :
 * 1. The function responsible for rotate the servo Motor 0, 90 or 180 degree
 *    based on the state input state value.
 */
void ServoMotor_Rotate(ServoMotor_State a_state)
{
	switch (a_state)
	{
	case Degree_90:
		/* Set the servo in 90 degree position */
		Timer0_PWM_Start(OCR0_VALUE_FOR_90_DEGREES);
		break;
	case Degree_180:
		/* Set the servo in 180 degree position */
		Timer0_PWM_Start(OCR0_VALUE_FOR_180_DEGREES);
		break;
	default:
		/* Any case else, set the servo in 0 degree position */
		Timer0_PWM_Start(OCR0_VALUE_FOR_0_DEGREES);
	}
}
