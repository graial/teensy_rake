// #include "Arduino.h"
// #include "TeensyLedDriver.h"

void TeensyLedDriver_Create(int ledNumber)
{
	pinMode(ledNumber, OUTPUT);
}

// void TeensyLedDriver_TurnOn(int ledNumber)
// {
// 	digitalWriteFast(ledNumber, HIGH);
// }

// void TeensyLedDriver_TurnOff(int ledNumber)
// {
// 	digitalWriteFast(ledNumber, LOW);
// }
