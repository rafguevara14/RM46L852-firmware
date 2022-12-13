#ifndef FW_GPIO_H
#define FW_GPIO_H

#include "hardware_peripherals.h"

typedef enum eGPIOStates
{
	FW_GPIO_OFF = 0,
	FW_GPIO_ON = 1,
	FW_GPIO_TOGGLE = 2

} eGPIOStates;

typedef enum eGPIODirection
{
	FW_GPIO_INPUT = 0,
	FW_GPIO_OUTPUT = 1

} eGPIODirection;

typedef enum eGPIOResistor
{
	FW_GPIO_PULLDOWN = 0,
	FW_GPIO_PULLUP = 1

} eGPIOResistor;

typedef enum eGPIOPolarity
{
	FW_GPIO_RISING = 0,
	FW_GPIO_FALLING = 1

} eGPIOPolarity;


void fw_gpio_configure(gioPORT_t *port, uint32 pin, eGPIODirection dir, callback func, eGPIOPolarity pol/* , eGPIOResistor res */);

void fw_gpio_led_init();
void fw_gpio_button_init();
void fw_gpio_button_interrupts_init(callback funcA, eGPIOPolarity polA);

void fw_gpio_set(gioPORT_t *port, uint32 bit, eGPIOStates state);
bool fw_gpio_get(gioPORT_t *port, uint32 bit);

#endif
