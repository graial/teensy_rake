#ifndef D_TeensyLedDriver_H
#define D_TeensyLedDriver_H

#include <stdint.h>

void TeensyLedDriver_Create(int pinNumber);
void TeensyLedDriver_TurnOn(int pinNumber);
void TeensyLedDriver_TurnOff(int pinNumber);

#endif