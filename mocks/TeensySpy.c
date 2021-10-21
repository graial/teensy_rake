#include "TeensySpy.h"
#include "common.h"

static int lastId;
static int lastState;
static BOOL callback;

void TeensySpy_Create()
{
  lastId = LED_ID_UNKNOWN;
  lastState = LED_STATE_UNKNOWN;
  timeCounter = 0;
  callback = FALSE;
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

int TeensySpy_GetElapsedMillis(void)
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

int TeensySpy_GetLastCallback(void)
{
    return callback;
}

void testCallback(void)
{
	callback = TRUE;
}

