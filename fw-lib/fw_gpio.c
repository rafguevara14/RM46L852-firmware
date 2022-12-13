#include "fw_gpio.h"

static callback button_callback;

void fw_gpio_configure(gioPORT_t *port, uint32 pin, eGPIODirection dir, callback func, eGPIOPolarity pol/* , eGPIOResistor res */)
{
	port->DIR |= (uint32)( dir << pin);

	gioDisableNotification(port, pin);

	//  TODO: Not tested with actual GPIOS
	// port->PULDIS |= (uint32)( 0 << pin); // enable pullup/pulldowns 
	// port->PSL    |= (uint32)( res << pin);
}

void fw_gpio_led_init()
{
	fw_gpio_configure(USER_LEDA, FW_GPIO_OUTPUT, NULL, 0);
	fw_gpio_configure(USER_LEDB, FW_GPIO_OUTPUT, NULL, 0);
}

void fw_gpio_button_init()
{
	fw_gpio_configure(USER_SWITCHA, FW_GPIO_INPUT, NULL, 0);
	fw_gpio_configure(USER_SWITCHB, FW_GPIO_INPUT, NULL, 0); 
}

void fw_gpio_button_interrupts_init(callback funcA, eGPIOPolarity polA)
{
	/* Interrupts only exist on GPIO pins so we have to steal from the led GPIOs */
	fw_gpio_configure(USER_LEDB, FW_GPIO_INPUT, funcA, polA); 
	
	gioEnableNotification(USER_LEDB);

	/** - interrupt polarity */
	gioREG->POL = (uint32)((uint32) polA << 2);

	button_callback = funcA;
                
	// /** - interrupt level */
	// gioREG->LVLSET = (uint32)((uint32)LOW << pin)   /* Bit 0 */
}

void fw_gpio_set(gioPORT_t *port, uint32 bit, eGPIOStates state)
{
	state == FW_GPIO_TOGGLE ? gioToggleBit(port, bit) : gioSetBit(port, bit, state);
}

bool fw_gpio_get(gioPORT_t *port, uint32 bit)
{
	return gioGetBit(port, bit);
}

void gioNotification(gioPORT_t *port, uint32 bit)
{
	button_callback();
}
