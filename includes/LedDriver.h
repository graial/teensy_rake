#ifndef D_LedDriver_H
#define D_LedDriver_H

#include <stdint.h>

typedef struct LedDriverStruct * LedDriver;

typedef struct LedDriverStruct
{
	int id;
} LedDriverStruct;

void LedDriver_Create(int pinNumber);
void LedDriver_Destroy(int pinNumber);
void LedDriver_TurnOn(int pinNumber);
void LedDriver_TurnOff(int pinNumber);

#endif