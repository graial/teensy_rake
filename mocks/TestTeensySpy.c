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
  TEST_ASSERT_EQUAL_HEX16(UNKNOWN, TeensyLedDriverSpy_GetLastCall());
}

void test_TeensySpy_create(void)
{
  driver = TeensyLedDriver_Create(1);
  TEST_ASSERT_EQUAL_HEX16(CREATE, TeensyLedDriverSpy_GetLastCall());
}

void test_TeensySpy_destroy(void)
{
  TeensyLedDriver_Destroy(driver);
  TEST_ASSERT_EQUAL_HEX16(DESTROY, TeensyLedDriverSpy_GetLastCall());
}

void test_TeensySpy_turnOn(void)
{
  TeensyLedDriver_TurnOn(driver);
  TEST_ASSERT_EQUAL_HEX16(TURN_ON, TeensyLedDriverSpy_GetLastCall());
}

void test_TeensySpy_turnOff(void)
{
  TeensyLedDriver_TurnOff(driver);
  TEST_ASSERT_EQUAL_HEX16(TURN_OFF, TeensyLedDriverSpy_GetLastCall());
}

void test_TeensyLedDriverSpy_unknown_on_create(void)
{
  driver = TeensyLedDriver_Create(4);

  TEST_ASSERT_EQUAL_HEX16(4, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, TeensyLedDriverSpy_GetLastState());
}

void test_TeensyLedDriverSpy_turnOn(void)
{
  driver = TeensyLedDriver_Create(4);
  TeensyLedDriver_TurnOn(driver);
  TEST_ASSERT_EQUAL_HEX16(4, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, TeensyLedDriverSpy_GetLastState());
}

void test_TeensyLedDriverSpy_turnOff(void)
{
  driver = TeensyLedDriver_Create(4);
  TeensyLedDriver_TurnOn(driver);
  TeensyLedDriver_TurnOff(driver);
  TEST_ASSERT_EQUAL_HEX16(4, TeensyLedDriverSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, TeensyLedDriverSpy_GetLastState());
}