#include "LedController.h"
#include "Arduino.h"

static LedDriver ledDrivers[MAX_LEDS] =
{ NULL };

static uint16_t ledsImage;
static uint16_t * ledsAddress;

static uint16_t getBitLocationFromLedNumber(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

void LedController_Create()
{
	ledsAddress = memset(ledDrivers, 0, sizeof ledDrivers);
	ledsImage = 0x0000;
	*ledsAddress = ledsImage;
}

void LedController_Activate(int ledNumber)
{
	LedDriver driver = LedDriver_Create(ledNumber);
	ledDrivers[ledNumber] = driver;
	ledsImage |= getBitLocationFromLedNumber(ledNumber);
	*ledsAddress = ledsImage;
}

void LedController_Deactivate(int ledNumber)
{
	int ledId = ledNumber;
	LedDriver_Destroy(ledDrivers[ledNumber]);
	ledsImage &= ~(getBitLocationFromLedNumber(ledId));
	*ledsAddress = ledsImage;
}

void LedController_TurnOn(int ledNumber)
{
	if (ledsImage == getBitLocationFromLedNumber(ledNumber))
	{
		LedDriver_TurnOn(ledDrivers[ledNumber]);
	}
}

void LedController_TurnOff(int ledNumber)
{
	if (ledsImage == getBitLocationFromLedNumber(ledNumber))
	{
		LedDriver_TurnOff(ledDrivers[ledNumber]);
	}
}
