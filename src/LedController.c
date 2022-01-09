#include "LedController.h"

static uint16_t * ledsAddress;

void LedController_Create(uint16_t * address)
{
	ledsAddress = address;
	*ledsAddress = 0;
}

void LedController_TurnOn(int ledNumber)
{
  *ledsAddress = ledNumber;
}

void LedController_TurnOff(int ledNumber)
{
  *ledsAddress = 0;
} 