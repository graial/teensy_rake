#include "FakeTimeService.h"

static Time fakeTime;

void TimeService_Create(void)
{
    fakeTime.milliseconds = MILLISECONDS_UNKNOWN;
}

void TimeService_Destroy(void)
{
}

void TimeService_GetTime(Time * time)
{
    time->milliseconds = fakeTime.milliseconds;
}

void FakeTimeService_SetMilliseconds(int milliseconds)
{
  fakeTime.milliseconds = milliseconds;
}