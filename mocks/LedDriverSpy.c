#include "LedDriverSpy.h"

static int lastId;
static int lastState;

void LedDriver_Create(int id)
{
	lastId = id;
	lastState = LED_STATE_UNKNOWN;
}

void LedDriver_Destroy(int id)
{
	lastId = LED_STATE_UNKNOWN;
	lastState = LED_STATE_UNKNOWN;
}

void LedDriver_TurnOn(int id)
{
	lastId = id;
	lastState = LED_ON;
}

void LedDriver_TurnOff(int id)
{
	lastId = id;
	lastState = LED_OFF;
}

int LedDriverSpy_GetLastId(void)
{
	return lastId;
}

int LedDriverSpy_GetLastState(void)
{
	return lastState;
}

void LedDriverSpy_Reset(void)
{
	lastId = LED_STATE_UNKNOWN;
	lastState = LED_STATE_UNKNOWN;
}