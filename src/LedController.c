#include "LedController.h"
#include "Arduino.h"
#include "TeensyLedDriver.h"

static TeensyLedDriver ledDrivers[MAX_LEDS] =
{ NULL };

static uint32_t ledsImage;
static uint32_t * ledsAddress;

static uint16_t getBitLocationFromLedNumber(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

void LedController_Create(uint32_t * address)
{
	memset(ledDrivers, 0, sizeof ledDrivers);
	ledsAddress = address;
	ledsImage = 0x0000;
	*ledsAddress = ledsImage;
}

void LedController_Activate(int ledNumber)
{
	TeensyLedDriver driver = TeensyLedDriver_Create(ledNumber);
	ledDrivers[ledNumber] = driver;
	ledsImage |= getBitLocationFromLedNumber(ledNumber);
	*ledsAddress = ledsImage;
}

void LedController_Deactivate(int ledNumber)
{
	int ledId = ledNumber;
	TeensyLedDriver_Destroy(ledDrivers[ledNumber]);
	ledsImage &= ~(getBitLocationFromLedNumber(ledId));
	*ledsAddress = ledsImage;
}

void LedController_TurnOn(int ledNumber)
{
	if (ledsImage == getBitLocationFromLedNumber(ledNumber))
	{
		TeensyLedDriver_TurnOn(ledDrivers[ledNumber]);
	}
}

void LedController_TurnOff(int ledNumber)
{
	if (ledsImage == getBitLocationFromLedNumber(ledNumber))
	{
		TeensyLedDriver_TurnOff(ledDrivers[ledNumber]);
	}
}
