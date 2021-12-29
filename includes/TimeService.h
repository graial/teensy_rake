#ifndef D_TimeService_H
#define D_TimeService_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Time Time;
    typedef void (*WakeUpCallback)(void);

    struct Time
    {
        int milliseconds;
    };

    void TimeService_GetTime(Time * );
    void TimeService_Create(void);
    void TimeService_Destroy(void);
    void TimeService_Delay(int milliseconds);
    void TimeService_SetPeriodicAlarmInMilliseconds(int milliseconds, WakeUpCallback cb);
    void TimeService_CancelPeriodicAlarmInMilliseconds(int milliseconds, WakeUpCallback cb);

#ifdef __cplusplus
}
#endif

#endif