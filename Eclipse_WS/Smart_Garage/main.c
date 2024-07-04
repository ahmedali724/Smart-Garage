/*
 ============================================================================
 Name        : main.c
 Module Name : APP
 Author      : Ahmed Ali
 Date        : 4 July 2024
 Description : The main function of project
 ============================================================================
 */

#include "HAL/KEYPAD/keypad.h"
#include "HAL/LCD/lcd.h"
#include "HAL/SERVO_MOTOR/servo.h"
#include "HAL/LAMP/lamp.h"
#include "HAL/LDR/ldr.h"

#include "MCAL/EXTERNAL_INTERRUPT/external_interrupt.h"
#include "MCAL/ADC/adc.h"
#include "MCAL/GPIO/gpio_private.h"

#include "util/delay.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile uint8 carsCounter = 0;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASSWORD_LENGTH			5
#define MAX_CARS_NUMBER			10

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 * Description :
 * Function to active keypad to get input number from it.
 * Function input:  array of uint8 to save numbers from keypad on it.
 * Function output: void.
 */
void getPasswordFromKeyPad(uint8 password[]);

/*
 * Description :
 * This is the call back function which will be executed each interrupt in INT0.
 * Function input:  void.
 * Function output: void.
 */
void INT0_Func(void);

/*
 * Description :
 * This is the call back function which will be executed each interrupt in INT1.
 * Function input:  void.
 * Function output: void.
 */
void INT1_Func(void);

int main(void)
{
	/* Configuration and initialization functions */

	uint16 adc_value;
	uint8 password[PASSWORD_LENGTH] =
	{ 1, 2, 3, 4, 5 }, enteredPassword[PASSWORD_LENGTH], i, flag = 0;

	/* select the configuration of ADC */
	ADC_ConfigType ADC_LDR =
	{ AVCC, PRESCALER_128 };

	/* select the configuration of EXT0 */
	EXT_INT0_ConfigType EXT_INT0_Config =
	{ RISING_EDGE };

	/* select the configuration of EXT1 */
	EXT_INT1_ConfigType EXT_INT1_Config =
	{ RISING_EDGE };

	/* passing the configuration to initialization function of EXT0 */
	EXT_INT0_init(&EXT_INT0_Config);
	/* passing the configuration to initialization function of EXT01 */
	EXT_INT1_init(&EXT_INT1_Config);

	/* passing the configuration to initialization function of ADC */
	ADC_init(&ADC_LDR);

	/* setup the call back function */
	EXT_INT0_setCallBack(INT0_Func);
	/* setup the call back function */
	EXT_INT1_setCallBack(INT1_Func);

	/* call the initialization function of LCD */
	LCD_init();

	/* call the initialization function of SERVO */
	ServoMotor_init();

	/* call the initialization function of LAMP */
	LAMP_init();

	/* enable global interrupt */
	SREG_REG.Bits.I_Bit = 1;

	/* loop until user enter the correct password */
	while (!flag)
	{
		/* take the input password from user */
		LCD_clearScreen();
		LCD_displayString("Enter Password:");
		LCD_moveCursor(1, 0);
		getPasswordFromKeyPad(enteredPassword);
		/* suppose that the password is correct */
		flag = 1;
		/* loop through each number and check if they are equal or not */
		for (i = 0; i < PASSWORD_LENGTH; i++)
		{
			/* if they are not equal, then the assumption is incorrect */
			if (enteredPassword[i] != password[i])
			{
				flag = 0;
			}
		}
	}

	/* welcome message in LCD */
	LCD_clearScreen();
	LCD_displayString("Welcome To Our");
	LCD_moveCursor(1, 0);
	LCD_displayString("Smart Garage");
	_delay_ms(1500);

	/* display number of cars and state of lights */
	LCD_clearScreen();
	LCD_displayString("Cars: ");
	LCD_moveCursor(1, 0);
	LCD_displayString("Lights: ");

	while (1)
	{
		/* get the adc value of LDR */
		adc_value = LDRsensor_getValue();

		/* display the number of cars in LCD */
		LCD_moveCursor(0, 5);
		LCD_intgerToString(carsCounter);

		/* this condition only for LCD display the specific digits from the data  */
		if (carsCounter < 100)
		{
			LCD_moveCursor(0, 7);
			LCD_displayCharacter(' ');
		}
		if (carsCounter < 10)
		{
			LCD_moveCursor(0, 6);
			LCD_displayCharacter(' ');
		}

		/*
		 * check the state of reading, if less than or equal 50 then activate the lamp
		 * else turn off lamp
		 */
		if (adc_value > 512)
		{
			LCD_displayStringRowColumn(1, 7, "ON");
			/*
			 * this to only this the character after ON is space
			 * when switch from OFF to ON we need to remove the last F latter
			 */
			LCD_displayCharacter(' ');
			LAMP_ON();
		}
		else
		{
			LCD_displayStringRowColumn(1, 7, "OFF");

			LAMP_OFF();
		}
	}
}

/*
 * Description :
 * Function to active keypad to get input number from it.
 * Function input:  array of uint8 to save numbers from keypad on it.
 * Function output: void.
 */
void getPasswordFromKeyPad(uint8 password[])
{
	uint8 i, temp;
	i = 0; /* the index and counter for the loop and equal 5 as password is 5 numbers */
	while (i < PASSWORD_LENGTH)
	{
		/* take the input number form keypad */
		temp = KEYPAD_getPressedKey();
		/* wait 250msec before getting a new press from the keypad buttons, Press time is 250msec */
		_delay_ms(250);
		/* if the input is not a number form 0 to 9 then repeat taking input step */
		/* ^ for the keys don't have a number or # or - or + */
		if (temp == '^' || temp == '#' || temp == '-' || temp == '+')
		{
			continue;
		}
		/* the input is a number, then save it to its index in array */
		password[i] = temp;
		/* display the * char in LCD */
		LCD_displayCharacter('*');
		/* increment the index */
		i++;
	}
	/* waiting for pressing enter key */
	while (KEYPAD_getPressedKey() != '#')
		;
}

/*
 * Description :
 * This is the call back function which will be executed each interrupt in INT0.
 * Function input:  void.
 * Function output: void.
 */
void INT0_Func(void)
{
	/* check if the garage is not full */
	if (carsCounter < MAX_CARS_NUMBER)
	{
		/* then increment the counter */
		carsCounter++;
		/* open the door by servo motor */
		ServoMotor_Rotate(Degree_90);
		/* wait 2 seconds */
		_delay_ms(2000);
		/* close the door by servo motor */
		ServoMotor_Rotate(Degree_0);
	}
}

/*
 * Description :
 * This is the call back function which will be executed each interrupt in INT1.
 * Function input:  void.
 * Function output: void.
 */
void INT1_Func(void)
{
	/* check if the garage is not empty */
	if (carsCounter > 0)
	{
		/* decrement increment the counter */
		carsCounter--;
		/* open the door by servo motor */
		ServoMotor_Rotate(Degree_90);
		/* wait 2 seconds */
		_delay_ms(2000);
		/* close the door by servo motor */
		ServoMotor_Rotate(Degree_0);
	}
}
