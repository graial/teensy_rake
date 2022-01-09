#include "FakeTimeService.h"

static Time fakeTime;
static int period;

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

void TimeService_Delay(int milliseconds)
{
}

void TimeService_Reset(void)
{
    fakeTime.milliseconds = 0;
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return period;
}