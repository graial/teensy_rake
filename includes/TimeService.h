#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time Time;

struct Time
{
    int milliseconds;
};

void TimeService_GetTime(Time * );

void TimeService_Create(void);
void TimeService_Destroy(void);

#endif 