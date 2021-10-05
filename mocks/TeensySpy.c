#include "TeensySpy.h"

static int lastId;
static int lastState;

void TeensySpy_Create()
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
}

void pinMode(uint8_t ledNumber, uint8_t command)
{
  lastId = ledNumber;
  lastState = command;
}

void digitalWriteFast(uint8_t ledNumber, uint8_t LEVEL)
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

int TeensySpy_GetLastId(void)
{
  return lastId;
}

int TeensySpy_GetLastState(void)
{
  return lastState;
}
