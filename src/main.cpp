#include "Arduino.h"

extern "C" {
#include "LedController.h"
    int main(void)
    {
        uint16_t activeLeds;
        LedController_Create(&activeLeds);
        int boardLed = 13;
        LedController_Activate(boardLed);
        // pinMode(13, OUTPUT);
        while (1) {
            LedController_TurnOn(boardLed);
            delay(500);
            LedController_TurnOff(boardLed);            
            delay(500);
        }
    }
}