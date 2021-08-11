#ifndef D_TeensyLedDriver_H
#define D_TeensyLedDriver_H

#include <stdint.h>

#include "LedDriver.h"

typedef struct TeensyLedDriverStruct * TeensyLedDriver;

typedef struct TeensyLedDriverStruct
{
	LedDriverStruct base;
} TeensyLedDriverStruct;

TeensyLedDriver TeensyLedDriver_Create(int pinNumber);
void TeensyLedDriver_Destroy(TeensyLedDriver self);
void TeensyLedDriver_TurnOn(TeensyLedDriver self);
void TeensyLedDriver_TurnOff(TeensyLedDriver self);

#endif