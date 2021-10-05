#ifndef D_Arduino_H
#define D_Arduino_H

#include <stdint.h>

enum
{
 	LOW = 0, HIGH = 1, OUTPUT = 10
};

void pinMode(uint8_t ledNumber,uint8_t io);
void digitalWriteFast(uint8_t ledNumber, uint8_t level);

#endif