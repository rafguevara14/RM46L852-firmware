/*
 * hardware_peripherals.c
 *
 *  Created on: Dec 6, 2022
 *      Author: rafgu
 */

#include "hardware_peripherals.h"

void halcogen_init()
{
    gioInit();
    adcInit();
    rtiInit();
    sciInit();
}


