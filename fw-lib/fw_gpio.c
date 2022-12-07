#include "fw_gpio.h"


void fw_gpio_configure(gioPORT_t *port, uint32 pin, eGPIODirection dir/* , eGPIOResistor res */)
{
	port->DIR    |= (uint32)( dir << pin);

	//  TODO: Not tested with actual GPIOS
	// port->PULDIS |= (uint32)( 0 << pin); // enable pullup/pulldowns 
	// port->PSL    |= (uint32)( res << pin);
}

void fw_gpio_led_init()
{
	fw_gpio_configure(USER_LEDA, FW_GPIO_OUTPUT);
	fw_gpio_configure(USER_LEDB, FW_GPIO_OUTPUT);
}

void fw_gpio_button_init()
{
	fw_gpio_configure(USER_SWITCHA, FW_GPIO_INPUT);
	fw_gpio_configure(USER_SWITCHB, FW_GPIO_INPUT); 
}

void fw_gpio_set(gioPORT_t *port, uint32 bit, eGPIOStates state)
{
	state == FW_GPIO_TOGGLE ? gioToggleBit(port, bit) : gioSetBit(port, bit, state);
}

bool fw_gpio_get(gioPORT_t *port, uint32 bit)
{
	return gioGetBit(port, bit);
}
