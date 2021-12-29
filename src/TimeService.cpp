#include "TimeService.h"
#include "Arduino.h"

static uint16_t board_delay;
static WakeUpCallback callback = NULL;

static void _cpp_delay(int milliseconds)
{
	delay(milliseconds);
}

extern "C" {
	void TimeService_Delay(int milliseconds)
	{
		_cpp_delay(milliseconds);
	}
}
