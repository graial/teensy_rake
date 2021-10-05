#include <Arduino.h>

extern "C" {
	#include "LedController.h"
}

extern "C" int main(void)
{
uint16_t activeLeds;
    LedController_Create(&activeLeds);
    int boardLed = 13;
    LedController_Activate(boardLed);

	while (1) {
		LedController_TurnOn(boardLed);
		delay(500);
		LedController_TurnOff(boardLed);
		delay(500);
	}
}