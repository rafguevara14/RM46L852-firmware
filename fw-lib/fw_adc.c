/*
 * fw_adc.c
 *
 *  Created on: Dec 5, 2022
 *      Author: rafgu
 */

#include "fw_adc.h"

void fw_adc_init()
{
	// do nothing for now...
	// TODO: See if we can dynamically configure ADC pins without halcogen 
}

uint16_t fw_poll_light_sensor()
{
	adcStartConversion(LIGHT_SENSOR);
	while(!adcIsConversionComplete(LIGHT_SENSOR));

	adcData_t data;
	adcGetData(LIGHT_REG, 1U, &data);

	return ADC_TO_VOLTAGE(data.value, LIGHT_MAX_VAL, LIGHT_REFERENCE_MV);
}
