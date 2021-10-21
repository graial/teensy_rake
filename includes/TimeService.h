#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time Time;

struct Time
{
    int milliseconds;
};

typedef void (*WakeUpCallback)(void);

void TimeService_GetTime(Time * time);

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_Delay(int milliseconds);

void TimeService_SetPeriodicAlarmInMilliseconds(int milliseconds, WakeUpCallback cb);
void TimeService_CancelPeriodicAlarmInMilliseconds(int milliseconds);
void TimeService_CheckForPeriodicAlarm();

#endif  /* D_TimeService_H */
