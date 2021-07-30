#include "unity.h"
#include "LedDriver.h"

static uint16_t activeLeds;

void setUp(void)
{
  LedDriver_Create(&activeLeds);
}

void tearDown(void)
{
}

void test_LedDriver_is_inactive_upon_creation(void)
{
  uint16_t activeLeds = 0xface;
  LedDriver_Create(&activeLeds);
  TEST_ASSERT_EQUAL_HEX16(0, activeLeds);
}

void test_LedDriver_Activate_Led_seven(void)
{
  LedDriver_Activate(7);
  TEST_ASSERT_EQUAL_HEX16(0x40, activeLeds);
}

void test_LedDriver_Deactivate_Led_seven(void)
{
  LedDriver_Activate(7);
  LedDriver_Deactivate(7);
  TEST_ASSERT_EQUAL_HEX16(0, activeLeds);
}

void test_LedDriver_Activate_MultipleLeds(void)
{
  LedDriver_Activate(10);
  LedDriver_Activate(7);
  TEST_ASSERT_EQUAL_HEX16(0x240, activeLeds);
}

void test_LedDriver_Deactivate_AnLed(void)
{
  LedDriver_Activate(10);
  LedDriver_Activate(7);
  LedDriver_Deactivate(10);
  TEST_ASSERT_EQUAL_HEX16(0x40, activeLeds);
}

void test_LedDriver_does_not_read_the_LedMemoryMap_for_state(void)
{
  activeLeds = 0xffff;
  LedDriver_Activate(8);
  TEST_ASSERT_EQUAL_HEX16(0x80, activeLeds);
}