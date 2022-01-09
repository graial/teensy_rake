#include "TimeService.h"
#include "Arduino.h"

elapsedMillis timeCounter;

static uint16_t board_delay;

static void _cpp_delay(int milliseconds)
{
	// delay(milliseconds);
}

extern "C" {
	void TimeService_Delay(int milliseconds)
	{
		_cpp_delay(milliseconds);
	}
	void TimeService_GetTime(Time * time)
	{
		time->milliseconds = timeCounter;
	}

	void TimeService_Reset(void)
	{
		timeCounter = 0;
	}
}