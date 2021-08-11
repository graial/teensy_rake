#include "Arduino.h"
#include "TeensyLedDriver.h"

TeensyLedDriver TeensyLedDriver_Create(int id)
{
	TeensyLedDriver self = calloc(1, sizeof(TeensyLedDriverStruct));
	self->id = id;
	pinMode(id, OUTPUT);
	return (TeensyLedDriver)self;
}

void TeensyLedDriver_Destroy(TeensyLedDriver self)
{
	// free(self->base.id)
}

void TeensyLedDriver_TurnOn(TeensyLedDriver self)
{
	digitalWriteFast(self->id, HIGH);
}

void TeensyLedDriver_TurnOff(TeensyLedDriver self)
{
	digitalWriteFast(self->id, LOW);
}
