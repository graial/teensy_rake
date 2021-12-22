#ifndef D_TeensySpy_H
#define D_TeensySpy_H

#include <stdint.h>

enum
{
  LED_ID_UNKNOWN = -1, LED_STATE_UNKNOWN = -1 , 
  LIGHT_ON = 1,  LIGHT_OFF = 0, 
  OUTPUT = 10
};

void TeensySpy_Create();

void pinMode(int ledNumber, int command);

int TeensySpy_GetLastId(void);
int TeensySpy_GetLastState(void);

#endif

