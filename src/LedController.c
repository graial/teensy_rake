#include "LedController.h"
#include "Arduino.h"
#include "LedDriver.h"

static uint16_t ledsImage;
static uint16_t * ledsAddress;

static uint16_t getBitLocationFromLedNumber(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

void LedController_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsImage = 0x0000;
	*ledsAddress = ledsImage;
}

void LedController_Activate(int ledNumber)
{
	LedDriver_Create(ledNumber);
	ledsImage |= getBitLocationFromLedNumber(ledNumber);
	*ledsAddress = ledsImage;
	// pinMode(ledNumber, OUTPUT);
}

void LedController_Deactivate(int ledNumber)
{
	LedDriver_Destroy(ledNumber);
	ledsImage &= ~(getBitLocationFromLedNumber(ledNumber));
	*ledsAddress = ledsImage;
}

void LedController_TurnOn(int ledNumber)
{
	if (ledsImage == getBitLocationFromLedNumber(ledNumber))
	{
		LedDriver_TurnOn(ledNumber);
	}
}

void LedController_TurnOff(int ledNumber)
{
	if (ledsImage == getBitLocationFromLedNumber(ledNumber))
	{
		LedDriver_TurnOff(ledNumber);
	}
}
