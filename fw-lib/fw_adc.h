/*
 * fw_adc.h
 *
 *  Created on: Dec 5, 2022
 *      Author: rafgu
 */

#ifndef FW_LIB_FW_ADC_H_
#define FW_LIB_FW_ADC_H_

#include "hardware_peripherals.h"

void fw_adc_init();

uint16_t fw_poll_light_sensor();


#endif /* FW_LIB_FW_ADC_H_ */
