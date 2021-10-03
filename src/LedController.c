#include "LedController.h"
#include <Arduino.h>

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
	// pinMode(ledNumber, OUTPUT);
}

void LedController_TurnOn(int ledNumber)
{
	ledsImage |= getBitLocationFromLedNumber(ledNumber);
	*ledsAddress = ledsImage;
}

void LedController_TurnOff(int ledNumber)
{
	ledsImage &= ~(getBitLocationFromLedNumber(ledNumber));
	*ledsAddress = ledsImage;
} 
