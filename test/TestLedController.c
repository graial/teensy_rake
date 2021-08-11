#include "unity.h"
#include "LedController.h"
#include "TeensySpy.h"

uint32_t activeLeds;

void setUp(void)
{
  LedController_Create(&activeLeds);
}

void tearDown(void)
{
}

void test_LedController_is_inactive_upon_creation(void)
{
  uint32_t activeLeds = 0xface;
  LedController_Create(&activeLeds);
  TEST_ASSERT_EQUAL_HEX16(0, activeLeds);
}

void test_LedController_Activate_Led_seven(void)
{
  LedController_Activate(7);
  TEST_ASSERT_EQUAL_HEX16(0x40, activeLeds);
}

void test_LedController_Deactivate_Led_seven(void)
{
  LedController_Activate(7);
  LedController_Deactivate(7);
  TEST_ASSERT_EQUAL_HEX16(0, activeLeds);
}

void test_LedController_Activate_MultipleLeds(void)
{
  LedController_Activate(10);
  LedController_Activate(7);
  TEST_ASSERT_EQUAL_HEX16(0x240, activeLeds);
  TEST_ASSERT_EQUAL_HEX16(CREATE, TeensyLedDriverSpy_GetLastCall());
}

void test_LedController_Deactivate_AnLed(void)
{
  LedController_Activate(10);
  LedController_Activate(7);
  LedController_Deactivate(10);
  TEST_ASSERT_EQUAL_HEX16(0x40, activeLeds);
  TEST_ASSERT_EQUAL_HEX16(DESTROY, TeensyLedDriverSpy_GetLastCall());
}

void test_LedController_does_not_read_the_LedMemoryMap_for_state(void)
{
  activeLeds = 0xffff;
  LedController_Activate(8);
  TEST_ASSERT_EQUAL_HEX16(0x80, activeLeds);
}

void test_Unactivated_Led_will_return_LED_id_if_activated(void)
{
  LedController_Activate(10);
  TEST_ASSERT_EQUAL_HEX16(10, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensyLedDriverSpy_GetLastState());
}

void test_Activated_Led_can_be_turned_on(void)
{
  LedController_Activate(10);
  LedController_TurnOn(10);
  TEST_ASSERT_EQUAL_HEX16(10, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, TeensyLedDriverSpy_GetLastState());
  TEST_ASSERT_EQUAL_HEX16(TURN_ON, TeensyLedDriverSpy_GetLastCall());
}

void test_Activated_Led_can_be_turned_off(void)
{
  LedController_Activate(10);
  LedController_TurnOn(10);
  LedController_TurnOff(10);
  TEST_ASSERT_EQUAL_HEX16(10, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, TeensyLedDriverSpy_GetLastState());
  TEST_ASSERT_EQUAL_HEX16(TURN_OFF, TeensyLedDriverSpy_GetLastCall());
}

void test_Unactivated_Led_will_return_unknown_if_deactivated_and_turned_on(void)
{
  LedController_Activate(10);
  LedController_Deactivate(10);
  LedController_TurnOn(10);
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensyLedDriverSpy_GetLastState());
  TEST_ASSERT_EQUAL_HEX16(DESTROY, TeensyLedDriverSpy_GetLastCall());
}

void test_Unactivated_Led_will_return_unknown_if_deactivated_and_turned_off(void)
{
  LedController_Activate(10);
  LedController_TurnOn(10);
  LedController_Deactivate(10);
  LedController_TurnOff(10);
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensyLedDriverSpy_GetLastState());
  TEST_ASSERT_EQUAL_HEX16(DESTROY, TeensyLedDriverSpy_GetLastCall());
}