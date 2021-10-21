#include "TimeService.h"
#include "Arduino.h"
#include "common.h"

elapsedMillis timeCounter;
static uint16_t board_delay;
static WakeUpCallback callback = NULL;

void TimeService_Delay(int milliseconds)
{
	// delay(milliseconds);
}

void TimeService_GetTime(Time * time)
{
	time->milliseconds = timeCounter;
}

void TimeService_SetPeriodicAlarmInMilliseconds(int milliseconds, WakeUpCallback cb)
{
	board_delay = milliseconds;
	callback = cb;
}

void TimeService_CancelPeriodicAlarmInMilliseconds(int milliseconds)
{
	board_delay = 0;
	callback = NULL;
}

void TimeService_CheckForPeriodicAlarm()
{
	if (timeCounter < board_delay )
	{
		return;
	} else {
		(callback)();
		timeCounter = 0;
	}
}
