#include "unity.h"
#include "LedDriver.h"
#include "TeensySpy.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_LedDriver_create(void)
{
  TeensyLedDriver_Create(1);
  TEST_ASSERT_EQUAL_HEX16(CREATE, TeensySpy_GetLastCall());
}

void test_LedDriver_destroy(void)
{
  TeensyLedDriver_Destroy(1);
  TEST_ASSERT_EQUAL_HEX16(DESTROY, TeensySpy_GetLastCall());
}

void test_LedDriver_TurnOn_with_Create(void)
{
  TeensyLedDriver_Create(1);
  TeensyLedDriver_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(TURN_ON, TeensySpy_GetLastCall());
}

void test_LedDriver_TurnOn_without_Create(void)
{
  // TeensyLedDriver_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(UNKNOWN, TeensySpy_GetLastCall());
}

void test_LedDriver_TurnOff_with_Create(void)
{
  TeensyLedDriver_Create(1);
  TeensyLedDriver_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(TURN_OFF, TeensySpy_GetLastCall());
}

void test_LedDriver_TurnOff_without_Create(void)
{
  TeensyLedDriver_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(UNKNOWN, TeensySpy_GetLastCall());
}