#ifndef D_TeensySpy_H
#define D_TeensySpy_H

#include <stdint.h>
#include "Arduino.h"

elapsedMillis timeCounter;

enum
{
  LED_ID_UNKNOWN = -1, LED_STATE_UNKNOWN = -1 ,
  LIGHT_ON = 1,  LIGHT_OFF = 0, 
};

void TeensySpy_Create();

int TeensySpy_GetLastId(void);
int TeensySpy_GetLastState(void);

void pinMode(int ledNumber, int command);

elapsedMillis TeensySpy_GetElapsedMillis(void);
elapsedMillis TeensySpy_AdvanceElapsedMillis(int milliseconds);
void TeensySpy_ResetElapsedMillis(void);

#endif
