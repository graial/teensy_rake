#include "LedControllerSpy.h"
#include "common.h"

static int lastId;
static int lastState;

void LedController_Create(uint16_t * virtualPin)
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
}

void LedController_Destroy(void)
{
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

BOOL LedController_IsOn(int ledNumber)
{
  if (lastId == ledNumber & lastState == LED_ON)
  {
    return TRUE;
  } else {
    return FALSE;
  }
}