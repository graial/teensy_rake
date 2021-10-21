#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

void FakeTimeService_SetMilliseconds(int);

WakeUpCallback FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod(void);


enum {MILLISECONDS_UNKNOWN = -1 };

#endif