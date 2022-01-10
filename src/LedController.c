#include "Arduino.h"
#include "LedController.h"

static uint16_t ledsImage;
static uint16_t * ledsAddress;

void LedController_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsImage = 0x0000;
	*ledsAddress = ledsImage;
}

void LedController_Activate(int ledNumber)
{
  pinMode(ledNumber, OUTPUT);
}

static uint16_t getBitLocationFromLedNumber(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

void LedController_TurnOn(int ledNumber)
{
  ledsImage |= getBitLocationFromLedNumber(ledNumber);
  *ledsAddress = ledsImage;
  // digitalWriteFast(ledNumber, HIGH);
}

void LedController_TurnOff(int ledNumber)
{
  ledsImage &= ~(getBitLocationFromLedNumber(ledNumber));
  *ledsAddress = ledsImage;
  // digitalWriteFast(ledNumber, LOW);
}
  