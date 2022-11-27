#ifndef FW_GPIO_H
#define FW_GPIO_H

#include "hardware_peripherals.h"

typedef enum eGPIOStates
{
	FW_GPIO_OFF = 0,
	FW_GPIO_ON = 1,
	FW_GPIO_TOGGLE = 2

} eGPIOStates;

void fw_gpio_init();
void fw_gpio_set(gioPORT_t *port, uint32 bit, eGPIOStates state);

#endif
