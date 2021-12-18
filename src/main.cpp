#include <Arduino.h>

extern "C" {
  #include "LedController.h"
  #include "LedScheduler.h"

  int main(void)
  {
  uint16_t activeLeds;
      LedController_Create(&activeLeds);
      LedScheduler_Create();

      int boardLed = 13;
      int delay = 500;
      LedController_Activate(boardLed);
      LedScheduler_ScheduleDelay(boardLed, delay);

    while (1) {
      LedScheduler_WakeUp();
    }
  }
}