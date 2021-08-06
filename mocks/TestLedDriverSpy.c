#include "unity.h"
#include "LedDriverSpy.h"

void setUp(void)
{
  LedDriver_Create(4);
}

void tearDown(void)
{
  LedDriver_Destroy(4);
}

void test_LedDriverSpy_unknown_on_create(void)
{
  TEST_ASSERT_EQUAL_HEX16(4, LedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedDriverSpy_GetLastState());
}

void test_LedDriverSpy_turnOn(void)
{
  LedDriver_TurnOn(4);
  TEST_ASSERT_EQUAL_HEX16(4, LedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, LedDriverSpy_GetLastState());
}

void test_LedDriverSpy_turnOff(void)
{
  LedDriver_TurnOn(4);
  LedDriver_TurnOff(4);
  TEST_ASSERT_EQUAL_HEX16(4, LedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, LedDriverSpy_GetLastState());
}