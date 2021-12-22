#include <Arduino.h>

extern "C" int main(void)
{
	#include "LedController.h"

	uint16_t activeLeds;
    int boardLed = 13;
    LedController_Activate(boardLed);
    // pinMode(13, OUTPUT);
    
	while (1) {
		digitalWriteFast(13, HIGH);
		delay(500);
		digitalWriteFast(13, LOW);
		delay(500);
	}
}