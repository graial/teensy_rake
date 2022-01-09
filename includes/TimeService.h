#ifndef D_TimeService_H
#define D_TimeService_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Time Time;

    struct Time
    {
        int milliseconds;
    };

    void TimeService_GetTime(Time * );
    void TimeService_Create(void);
    void TimeService_Destroy(void);
    void TimeService_Reset(void);
    void TimeService_Delay(int milliseconds);
    
#ifdef __cplusplus
}
#endif

#endif