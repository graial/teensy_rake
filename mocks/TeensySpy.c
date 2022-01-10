#include "Arduino.h"
#include "TeensySpy.h"

static int lastId;
static int lastState;

void TeensySpy_Create()
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
  timeCounter = 0;
}

int TeensySpy_GetLastId()
{
  return lastId;
}
int TeensySpy_GetLastState()
{
  return lastState;
}

void pinMode(int ledNumber, int command)
{
  lastId = ledNumber;
  lastState = command;
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

elapsedMillis TeensySpy_GetElapsedMillis(void)
{
  return timeCounter;
}

elapsedMillis TeensySpy_AdvanceElapsedMillis(int milliseconds)
{
  timeCounter += milliseconds;
}

void TeensySpy_ResetElapsedMillis(void)
{
  timeCounter = 0;
}
