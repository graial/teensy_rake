#ifndef D_LedController_H
#define D_LedController_H

#include "common.h"

void LedController_Create(uint16_t * pinNumber);
void LedController_TurnOn(int ledNumber);
void LedController_TurnOff(int ledNumber);
void LedController_Activate(int ledNumber);
BOOL LedController_IsOn(int ledNumber);

#endif
