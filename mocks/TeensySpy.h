#ifndef D_TeensySpy_H
#define D_TeensySpy_H

#include "TeensyLedDriver.h"

enum { 
  UNKNOWN, CREATE, DESTROY, TURN_ON, TURN_OFF
};

int TeensySpy_GetLastCall(void);

#endif