#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

enum {MILLISECONDS_UNKNOWN = -1 };

void FakeTimeService_SetMilliseconds(int);

int FakeTimeService_GetAlarmPeriod(void);

#endif