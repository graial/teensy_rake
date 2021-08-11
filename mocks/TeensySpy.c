#include <stdlib.h>

#include "TeensySpy.h"

typedef struct TeensyLedDriverSpyStruct * TeensyLedDriverSpy;

typedef struct TeensyLedDriverSpyStruct
{
    struct TeensyLedDriverStruct base;
} TeensyLedDriverSpyStruct;

static int lastId;
static int lastState;
static int lastCall = UNKNOWN;

TeensyLedDriver TeensyLedDriver_Create(int id)
{
	TeensyLedDriverSpy self = calloc(1, sizeof(TeensyLedDriverSpyStruct));
    self->base.id = id;
	lastId = id;
	lastState = LED_STATE_UNKNOWN;
	lastCall = CREATE;
	return (TeensyLedDriver)self;
}

void TeensyLedDriver_Destroy(TeensyLedDriver self)
{
	lastId = LED_STATE_UNKNOWN;
	lastState = LED_STATE_UNKNOWN;
	lastCall = DESTROY;
}

void TeensyLedDriver_TurnOn(TeensyLedDriver super)
{
	TeensyLedDriverSpy self = (TeensyLedDriverSpy)super;
	lastId = self->base.id;
	lastState = LED_ON;
	lastCall = TURN_ON;
}

void TeensyLedDriver_TurnOff(TeensyLedDriver super)
{
	TeensyLedDriverSpy self = (TeensyLedDriverSpy)super;
	lastId = self->base.id;
	lastState = LED_OFF;
	lastCall = TURN_OFF;
}

int TeensyLedDriverSpy_GetLastCall(void)
{
	return lastCall;
}

int TeensyLedDriverSpy_GetLastId(void)
{
	return lastId;
}

int TeensyLedDriverSpy_GetLastState(void)
{
	return lastState;
}
