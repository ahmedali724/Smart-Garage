/*
 ============================================================================
 Name        : ldr.c
 Module Name : HAL
 Author      : Ahmed Ali
 Date        : 4 July 2024
 Description : Source file for the LDR driver
 ============================================================================
 */

#include "../../LIB/std_types.h"
#include "ldr.h"
#include "../../MCAL/ADC/adc.h"

uint16 LDRsensor_getValue(void)
{
	uint16 adc_value = 0;
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);
	return adc_value;
}
