/*
 ============================================================================
 Name        : lamp.c
 Module Name : HAL
 Author      : Ahmed Ali
 Date        : 4 July 2024
 Description : Source file for the LAMP driver
 ============================================================================
 */

#include "../../MCAL/GPIO/gpio.h"
#include "lamp.h"

void LAMP_init(void)
{
	GPIO_setupPinDirection(LED_PORT, LED_PIN, PIN_OUTPUT);

	GPIO_writePin(LED_PORT, LED_PIN, LOGIC_LOW);
}

void LAMP_ON(void)
{
	GPIO_writePin(LED_PORT, LED_PIN, LOGIC_HIGH);

}

void LAMP_OFF(void)
{
	GPIO_writePin(LED_PORT, LED_PIN, LOGIC_LOW);

}

