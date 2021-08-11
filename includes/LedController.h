#ifndef D_LedController_H
#define D_LedController_H

#include <stdint.h>

enum {MAX_LEDS = 32};

void LedController_Create(uint32_t * address);
void LedController_Destroy();
void LedController_Activate(int pinNumber);
void LedController_Deactivate(int pinNumber);

void LedController_TurnOn(int pinNumber);
void LedController_TurnOff(int pinNumber);

#endif