#ifndef D_TeensySpy_H
#define D_TeensySpy_H

#include "TeensyLedDriver.h"

enum
{
  LED_ID_UNKNOWN = -1, LED_STATE_UNKNOWN = -1, 
  LED_OFF = 0, LED_ON = 1,
  UNKNOWN = 10, CREATE = 11, DESTROY = 12, TURN_ON = 13, TURN_OFF = 14
};


int TeensyLedDriverSpy_GetLastId(void);
int TeensyLedDriverSpy_GetLastState(void);
void TeensyLedDriverSpy_Reset(void);
int TeensyLedDriverSpy_GetLastCall(void);

#endif