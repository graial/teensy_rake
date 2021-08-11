#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>

typedef struct LedDriverStruct * LedDriver;

typedef struct LedDriverStruct
{
	int id;
} LedDriverStruct;

LedDriver LedDriver_Create(int pinNumber);
void LedDriver_Destroy(LedDriver self);
void LedDriver_TurnOn(LedDriver self);
void LedDriver_TurnOff(LedDriver self);

#endif