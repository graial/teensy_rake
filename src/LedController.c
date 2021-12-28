#include <stdint.h>

#include "LedController.h"
#include "Arduino.h"

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
	digitalWriteFast(ledNumber, HIGH);
}

void LedController_TurnOff(int ledNumber)
{
	ledsImage &= ~(getBitLocationFromLedNumber(ledNumber));

	*ledsAddress = ledsImage;
	digitalWriteFast(ledNumber, LOW);
}

BOOL LedController_IsOn(int ledNumber)
{
  if ((*ledsAddress & getBitLocationFromLedNumber(ledNumber)) >> (ledNumber -1))
  {
    return TRUE;
  } else {
    return FALSE;
  }
}