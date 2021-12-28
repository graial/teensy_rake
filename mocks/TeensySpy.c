#include <stdint.h>
#include "TeensySpy.h"

static int lastId;
static int lastState;

void TeensySpy_Create()
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
}

void pinMode(int ledNumber, int command)
{
  lastId = ledNumber;
  lastState = command;
}

int TeensySpy_GetLastId()
{
  return lastId;
}

int TeensySpy_GetLastState()
{
  return lastState;
}

void digitalWriteFast(int ledNumber, int LEVEL)
{
  if (lastId == ledNumber)
  {
    lastState = LEVEL;
  } else
  {
    lastId = LED_ID_UNKNOWN;
      lastState = LED_STATE_UNKNOWN;
  }
}