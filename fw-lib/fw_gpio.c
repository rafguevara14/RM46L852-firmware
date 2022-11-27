#include "fw_gpio.h"

void fw_gpio_init()
{
	gioInit();
}

void fw_gpio_set(gioPORT_t *port, uint32 bit, eGPIOStates state)
{
	if (state == FW_GPIO_TOGGLE)
	{
		gioToggleBit(port, bit);
	}
	else
	{
		gioSetBit(port, bit, state);
	}
}
