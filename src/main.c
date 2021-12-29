#include <stdint.h>
#include "TimeService.h"
#include "LedScheduler.h"
#include "LedController.h"

int main(void)
{
	uint16_t activeLeds;
    LedController_Create(&activeLeds);
    LedScheduler_Create();

    int boardLed = 13;
    int boardDelay = 500;
    LedScheduler_ScheduleDelay(boardLed, boardDelay);
    LedController_Activate(boardLed);
    
	while (1) {
		LedScheduler_WakeUp();
	}
}