#include "FakeTimeService.h"
#include "common.h"

static Time fakeTime;
static WakeUpCallback callback;
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

WakeUpCallback FakeTimeService_GetAlarmCallback(void)
{
    return callback;
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return period;
}

void TimeService_SetPeriodicAlarmInMilliseconds(int milliseconds, WakeUpCallback cb)
{
    callback = cb;
    period = milliseconds;
}

void TimeService_CancelPeriodicAlarmInMilliseconds(int milliseconds)
{
    callback = NULL;
    period = 0;
}

void TimeService_Reset(void)
{
    
}