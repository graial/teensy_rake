#include <Arduino.h>

extern "C" {
	#include "LedController.h"
	int main(void)
	{
		uint16_t activeLeds;
	    int boardLed = 13;
	    LedController_Create(&activeLeds);
	    LedController_Activate(boardLed);
	    
		while (1) {
			LedController_TurnOn(boardLed);
			delay(500);
			LedController_TurnOff(boardLed);
			delay(500);
		}
	}
}