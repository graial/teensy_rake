#include "unity.h"
#include "LedControllerSpy.h"

void setUp(void)
{
  LedControllerSpy_Create();
}

void tearDown(void)
{
}

void test_LedControllerSpy_on_create(void)
{
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedControllerSpy_GetLastState());
}

void test_LedControllerSpy_remembers_light_after_TurnOn(void)
{
  LedController_TurnOn(10);
  TEST_ASSERT_EQUAL_HEX16(10, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, LedControllerSpy_GetLastState());
}
void test_LedControllerSpy_remembers_light_after_TurnOff(void)
{
  LedController_TurnOff(10);
  TEST_ASSERT_EQUAL_HEX16(10, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, LedControllerSpy_GetLastState());
}
