#ifndef D_Arduino_H
#define D_Arduino_H

enum
{
  LOW = 0, HIGH = 1, OUTPUT = 10
};

void digitalWriteFast(int ledNumber, int LEVEL);
void pinMode(int ledNumber, int OUTPUT);

typedef unsigned long elapsedMillis;

#endif