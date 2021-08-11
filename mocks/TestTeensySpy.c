#include "unity.h"
#include "TeensySpy.h"

TeensyLedDriver driver;

void setUp(void)
{ 
}

void tearDown(void)
{
}

void test_TeensySpy_default_to_unknown(void)
{
  TEST_ASSERT_EQUAL_HEX16(UNKNOWN, TeensySpy_GetLastCall());
}

void test_TeensySpy_create(void)
{
  driver = TeensyLedDriver_Create(1);
  TEST_ASSERT_EQUAL_HEX16(CREATE, TeensySpy_GetLastCall());
}

void test_TeensySpy_destroy(void)
{
  TeensyLedDriver_Destroy(driver);
  TEST_ASSERT_EQUAL_HEX16(DESTROY, TeensySpy_GetLastCall());
}

void test_TeensySpy_turnOn(void)
{
  TeensyLedDriver_TurnOn(driver);
  TEST_ASSERT_EQUAL_HEX16(TURN_ON, TeensySpy_GetLastCall());
}

void test_TeensySpy_turnOff(void)
{
  TeensyLedDriver_TurnOff(driver);
  TEST_ASSERT_EQUAL_HEX16(TURN_OFF, TeensySpy_GetLastCall());
}
