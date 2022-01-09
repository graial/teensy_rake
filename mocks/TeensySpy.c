#include "TeensySpy.h"

static int lastId;
static int lastState;
static BOOL callbackReturn;
static BOOL callbackCount;

void TeensySpy_Create()
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
  timeCounter = 0;
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

elapsedMillis TeensySpy_GetElapsedMillis(void)
{
  return timeCounter;
}

void TeensySpy_AdvanceElapsedMillis(int milliseconds)
{
  timeCounter += milliseconds;
}

void TeensySpy_ResetElapsedMillis(void)
{
  timeCounter = 0;
}