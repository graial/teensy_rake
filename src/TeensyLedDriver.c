#include "Arduino.h"
#include "LedDriver.h"
#include "TeensyLedDriver.h"

typedef struct TeensyLedDriverStruct * TeensyLedDriver;

typedef struct TeensyLedDriverStruct
{
	LedDriverStruct base;
} TeensyLedDriverStruct;

void TeensyLedDriver_Create(int ledNumber)
{
	pinMode(ledNumber, OUTPUT);
}

void TeensyLedDriver_TurnOn(int ledNumber)
{
	digitalWriteFast(ledNumber, HIGH);
}

void TeensyLedDriver_TurnOff(int ledNumber)
{
	digitalWriteFast(ledNumber, LOW);
}
