#include <stdint.h>

#include "LedScheduler.h"
#include "TimeService.h"
#include "LedController.h"

enum
{
    UNUSED = -1
};

Time time;
typedef struct
{
  int id;
  int milliseconds;
} ScheduledLedEvent;

static ScheduledLedEvent scheduledEvent;

void LedScheduler_Create(void)
{
  scheduledEvent.id = UNUSED;
}

void LedScheduler_Destroy(void)
{
  scheduledEvent.id = UNUSED;
}

void LedScheduler_ScheduleDelay(int id, int milliseconds)
{
  scheduledEvent.id = id;
  scheduledEvent.milliseconds = milliseconds;
}

void LedScheduler_WakeUp(void)
{
  TimeService_GetTime(&time);

  if (scheduledEvent.id == UNUSED)
  {
    return;
  }
  if (time.milliseconds < scheduledEvent.milliseconds)
  {
    return;
  }
  if (LedController_IsOn(scheduledEvent.id))
  {
  	LedController_TurnOff(scheduledEvent.id);
  } else {
  	LedController_TurnOn(scheduledEvent.id);
  }
  TimeService_Reset();
  // TimeService_Delay(scheduledEvent.milliseconds);
}
