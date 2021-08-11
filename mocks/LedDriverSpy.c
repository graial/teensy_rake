#include "LedDriverSpy.h"
#include <stdlib.h>

typedef struct LedDriverSpyStruct * LedDriverSpy;
typedef struct LedDriverSpyStruct
{
    struct LedDriverStruct base;
} LedDriverSpyStruct;

static int lastId;
static int lastState;

LedDriver LedDriver_Create(int id)
{
    LedDriverSpy self = calloc(1, sizeof(LedDriverSpyStruct));
    self->base.id = id;
	lastId = id;
	lastState = LED_STATE_UNKNOWN;
    return (LedDriver)self;
}

void LedDriver_Destroy(LedDriver self)
{
	lastId = LED_STATE_UNKNOWN;
	lastState = LED_STATE_UNKNOWN;
}

void LedDriver_TurnOn(LedDriver super)
{
	LedDriverSpy self = (LedDriverSpy)super;
	lastId = self->base.id;
	lastState = LED_ON;
}

void LedDriver_TurnOff(LedDriver super)
{
	LedDriverSpy self = (LedDriverSpy)super;
	lastId = self->base.id;
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
