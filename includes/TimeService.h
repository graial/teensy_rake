#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time Time;

struct Time
{
    int milliseconds;
};

void TimeService_GetTime(Time * time);

void TimeService_Create(void);
void TimeService_Destroy(void);

#endif  /* D_TimeService_H */

// int TimeService_GetMinute(void);
// int TimeService_GetDay(void);

// BOOL TimeService_MatchesDayOfWeek(const Time *, Day day);
// BOOL TimeService_MatchesMinuteOfDay(const Time *, int minute);
// BOOL TimeService_MatchesNow(int reactionDay, int minute);

