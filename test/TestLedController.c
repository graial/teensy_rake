#include "unity.h"
#include "LedController.h"

void setUp(void)
{
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
  uint16_t virtualPin;
  LedController_Create(&virtualPin);
  LedController_TurnOn(7);
  TEST_ASSERT_EQUAL_HEX16(0x07, virtualPin);
}

void test_LedController_TurnOff_Led_seven(void)
{
  uint16_t virtualPin;
  LedController_Create(&virtualPin);
  LedController_TurnOn(7);
  LedController_TurnOff(7);
  TEST_ASSERT_EQUAL_HEX16(0, virtualPin);
}
