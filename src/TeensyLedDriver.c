#include "Arduino.h"
#include "TeensyLedDriver.h"

LedDriver TeensyLedDriver_Create(LedDriver self)
{
	// TeensyLedDriver self = calloc(1, sizeof(TeensyLedDriverStruct));
	// self->base.id = ledNumber
	pinMode(self->base.id, OUTPUT);
	// return (LedDriver)self;
}

void TeensyLedDriver_Destroy(LedDriver self)
{
	// free(self->base.id)
}

void TeensyLedDriver_TurnOn(LedDriver self)
{
	digitalWriteFast(self->base.id, HIGH);
}

void TeensyLedDriver_TurnOff(LedDriver self)
{
	digitalWriteFast(self->base.id, LOW);
}
