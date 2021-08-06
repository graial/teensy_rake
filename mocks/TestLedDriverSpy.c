#include "unity.h"
#include "LedDriverSpy.h"

void setUp(void)
{
  // uint16_t ledsAddress;
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

// void test_LedDriverSpy_off_on_activate(void)
// {
//   LedController_Activate(5);
//   TEST_ASSERT_EQUAL_HEX16(5, LedDriverSpy_GetLastId());
//   TEST_ASSERT_EQUAL_HEX16(LED_OFF, LedDriverSpy_GetLastState());
// }

// void test_LedDriverSpy_unknown_on_deactivate(void)
// {
//   LedController_Activate(5);
//   LedController_Deactivate(5);
//   TEST_ASSERT_EQUAL_HEX16(5, LedDriverSpy_GetLastId());
//   TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedDriverSpy_GetLastState());
// }

// void test_LedDriverSpy_TurnOn(void)
// {
//   LedDriver_Activate(5);
//   LedDriver_TurnOn(5);
//   TEST_ASSERT_EQUAL_HEX16(5, LedDriverSpy_GetLastId());
//   TEST_ASSERT_EQUAL_HEX16(LED_ON, LedDriverSpy_GetLastState());
// }

// void test_LedDriverSpy_TurnOff(void)
// {
//   LedDriver_Activate(5);
//   LedDriver_TurnOn(5);
//   LedDriver_TurnOff(5);
//   TEST_ASSERT_EQUAL_HEX16(5, LedDriverSpy_GetLastId());
//   TEST_ASSERT_EQUAL_HEX16(LED_OFF, LedDriverSpy_GetLastState());
// }