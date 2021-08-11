#include "unity.h"
#include "LedDriverSpy.h"

LedDriver driver; 

void setUp(void)
{
  driver = LedDriver_Create(4);
}

void tearDown(void)
{
  LedDriver_Destroy(driver);
}

void test_LedDriverSpy_unknown_on_create(void)
{
  TEST_ASSERT_EQUAL_HEX16(4, LedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedDriverSpy_GetLastState());
}

void test_LedDriverSpy_turnOn(void)
{
  LedDriver_TurnOn(driver);
  TEST_ASSERT_EQUAL_HEX16(4, LedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, LedDriverSpy_GetLastState());
}

void test_LedDriverSpy_turnOff(void)
{
  LedDriver_TurnOn(driver);
  LedDriver_TurnOff(driver);
  TEST_ASSERT_EQUAL_HEX16(4, LedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, LedDriverSpy_GetLastState());
}