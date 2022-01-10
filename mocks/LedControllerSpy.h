#ifndef D_LedControllerSpy_H
#define D_LedControllerSpy_H

#include <stdint.h>
#include "LedController.h"

enum
{
  LED_ID_UNKNOWN = -1, LED_STATE_UNKNOWN = -1, 
  LED_OFF = 0, LED_ON = 1
};

int LedControllerSpy_GetLastId(void);
int LedControllerSpy_GetLastState(void);

#endif
