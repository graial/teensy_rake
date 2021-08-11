#include <stdlib.h>

#include "LedDriver.h"
#include "TeensySpy.h"

static int lastCall = UNKNOWN;

TeensyLedDriver TeensyLedDriver_Create(int id)
{
	TeensyLedDriver self = calloc(1, sizeof(TeensyLedDriverStruct));
	lastCall = CREATE;
	return self;
}

void TeensyLedDriver_Destroy(TeensyLedDriver self)
{
	lastCall = DESTROY;
}

void TeensyLedDriver_TurnOn(TeensyLedDriver self)
{
	lastCall = TURN_ON;
}

void TeensyLedDriver_TurnOff(TeensyLedDriver self)
{
	lastCall = TURN_OFF;
}

int TeensySpy_GetLastCall(void)
{
	return lastCall;
}