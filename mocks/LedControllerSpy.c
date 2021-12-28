#include "LedControllerSpy.h"

static int lastId;
static int lastState;


void LedControllerSpy_Create(uint16_t * ledsAddress)
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
}

int LedControllerSpy_GetLastId(void) 
{
    return lastId;
}

int LedControllerSpy_GetLastState(void)
{
  return lastState;
}

void LedController_TurnOn(int ledNumber)
{
  lastId = ledNumber;
  lastState = LED_ON;
}

void LedController_TurnOff(int ledNumber)
{
  lastId = ledNumber;
  lastState = LED_OFF;
}