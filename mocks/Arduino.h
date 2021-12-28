#ifndef D_Arduino_H
#define D_Arduino_H

enum
{
  HIGH = 1, LOW = 0,
  OUTPUT = 10
};

void pinMode(int ledNumber, int command);
void digitalWriteFast(int ledNumber, int LEVEL);

#endif