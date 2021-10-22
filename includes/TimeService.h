#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time Time;

struct Time
{
    int milliseconds;
};

typedef void (*WakeUpCallback)(void);

#ifdef __cplusplus
extern "C" {
#endif
    void TimeService_GetTime(Time * time);
    void TimeService_Reset(void);
    void TimeService_SetPeriodicAlarmInMilliseconds(int milliseconds, WakeUpCallback cb);
    void TimeService_CancelPeriodicAlarmInMilliseconds(int milliseconds);
#ifdef __cplusplus
}
#endif

void TimeService_Create(void);
void TimeService_Destroy(void);

void TimeService_Delay(int milliseconds);

void TimeService_CheckForPeriodicAlarm();

#endif  /* D_TimeService_H */
