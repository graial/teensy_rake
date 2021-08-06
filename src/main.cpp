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
    // pinMode(ledNumber, OUTPUT);

	while (1) {
		// TeensyLedDriver_TurnOn(ledNumber);
        digitalWriteFast(boardLed, HIGH);
		delay(500);
		// TeensyLedDriver_TurnOff(13);
        digitalWriteFast(boardLed, LOW);
		delay(500);
	}
}

