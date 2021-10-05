#ifndef D_LedController_H
#define D_LedController_H

#include <stdint.h>

void LedController_Create(uint16_t * address);
void LedController_Activate(int ledNumber);
void LedController_TurnOn(int ledNumber);
void LedController_TurnOff(int ledNumber);

#endif