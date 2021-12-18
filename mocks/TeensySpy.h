#ifndef D_TeensySpy_H
#define D_TeensySpy_H

typedef int elapsedMillis;
// elapsedMillis timeCounter;

#include <stdint.h>

enum
{
  LED_ID_UNKNOWN = -1, LED_STATE_UNKNOWN = -1, 
  LED_OFF = 0, LOW = 0, LED_ON = 1, HIGH = 1, OUTPUT = 10
};

void TeensySpy_Create();

void pinMode(uint8_t ledNumber, uint8_t command);
void digitalWriteFast(uint8_t ledNumber, uint8_t LEVEL);

int TeensySpy_GetLastId(void);
int TeensySpy_GetLastState(void);

void TeensySpy_AdvanceElapsedMillis(int milliseconds);
void TeensySpy_ResetElapsedMillis(void);
int TeensySpy_GetElapsedMillis(void);


int TeensySpy_GetLastCallback(void);

void testCallback(void);


#endif