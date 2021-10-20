#ifndef D_LedScheduler_H
#define D_LedScheduler_H

#include <stdint.h>

void LedScheduler_Create(void);
void LedScheduler_Destroy(void);

void LedScheduler_ScheduleDelay(int id, int milliseconds);
void LedScheduler_WakeUp(void);

#endif