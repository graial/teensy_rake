#include "LedDriver.h"
#include "TeensyLedDriver.h"

static uint16_t ledsImage;
static uint16_t * ledsAddress;

static uint16_t getBitLocationFromLedNumber(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

void LedDriver_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsImage = 0x0000;
	*ledsAddress = ledsImage;
}

void LedDriver_Activate(int ledNumber)
{
	TeensyLedDriver_Create(ledNumber);
	ledsImage |= getBitLocationFromLedNumber(ledNumber);
	*ledsAddress = ledsImage;
}

void LedDriver_Deactivate(int ledNumber)
{
	ledsImage &= ~(getBitLocationFromLedNumber(ledNumber));
	*ledsAddress = ledsImage;
}
