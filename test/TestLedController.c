#include "unity.h"
#include "LedController.h"

static uint16_t virtualPin;

void setUp(void)
{
	LedController_Create(&virtualPin);
}

void tearDown(void)
{
}

void test_LedController_is_off_upon_creation(void)
{
	uint16_t virtualPin = 0xface;
	LedController_Create(&virtualPin);
	TEST_ASSERT_EQUAL_HEX16(0, virtualPin);
}

void test_LedController_TurnOn_Led_seven(void)
{
  LedController_TurnOn(7);
  TEST_ASSERT_EQUAL_HEX16(0x40, virtualPin);
}

void test_LedController_TurnOff_Led_seven(void)
{
  LedController_TurnOn(7);
  LedController_TurnOff(7);
  TEST_ASSERT_EQUAL_HEX16(0, virtualPin);
}

void test_LedController_TurnOn_MultipleLeds(void)
{
  LedController_TurnOn(10);
  LedController_TurnOn(7);
  TEST_ASSERT_EQUAL_HEX16(0x240, virtualPin);
}

void test_LedController_TurnOff_AnLed(void)
{
  LedController_TurnOn(10);
  LedController_TurnOn(7);
  LedController_TurnOff(10);
  TEST_ASSERT_EQUAL_HEX16(0x40, virtualPin);
}

void test_LedController_does_not_read_the_LedMemoryMap_for_state(void)
{
  virtualPin = 0xffff;
  LedController_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x80, virtualPin);
}


// void test_Unactivated_Led_will_return_LED_if_activated(void)
// {
//   LedController_Activate(10);
//   TEST_ASSERT_EQUAL_HEX16(10, TeensySpy_GetLastId());
//   TEST_ASSERT_EQUAL_HEX16(LIGHT_OFF, TeensySpy_GetLastState());
// }