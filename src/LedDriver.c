#include "LedDriver.h"
#include "TeensyLedDriver.h"

static int driverState;

LedDriver LedDriver_Create(int pinNumber)
{
	driverState = 1;
	TeensyLedDriver teensySelf = TeensyLedDriver_Create(pinNumber);
	LedDriver self;
	self = teensySelf->base;
	return self;
}

void LedDriver_Destroy(LedDriver self)
{
	driverState = 0;
	TeensyLedDriver teensySelf;
	teensySelf->base.id = self->id;
	TeensyLedDriver_Destroy(teensySelf);	
}

void LedDriver_TurnOn(LedDriver self)
{
	if (driverState == 1) 
	{	
		TeensyLedDriver teensySelf;
		teensySelf->base.id = self->id;
		TeensyLedDriver_TurnOn(teensySelf);
	}
}

void LedDriver_TurnOff(LedDriver self)
{
	if (driverState == 1) 
	{	
		TeensyLedDriver teensySelf;
		teensySelf->base.id = self->id;
		TeensyLedDriver_TurnOff(teensySelf);
	}
}