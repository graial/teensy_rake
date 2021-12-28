#ifndef D_LedScheduler_H
#define D_LedScheduler_H

void LedScheduler_Create(void);
void LedScheduler_WakeUp(void);
void LedScheduler_ScheduleDelay(int id, int milliseconds);
#endif
