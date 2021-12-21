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
		digitalWriteFast(13, HIGH);
		delay(500);
		digitalWriteFast(13, LOW);
		delay(500);
	}
}