#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>
#include "TeensyLedDriver.h"

void LedDriver_Create(uint16_t * address);
void LedDriver_Activate(int pinNumber);
void LedDriver_Deactivate(int pinNumber);

#endif