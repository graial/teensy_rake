#ifndef D_LedDriverSpy_H
#define D_LedDriverSpy_H

#include "LedDriver.h"

enum
{
	LED_ID_UNKNOWN = -1, LED_STATE_UNKNOWN = -1, 
	LED_OFF = 0, LED_ON = 1
};

int LedDriverSpy_GetLastId(void);
int LedDriverSpy_GetLastState(void);

#endif