#include "unity.h"
#include "LedScheduler.h"
#include "LedControllerSpy.h"

static uint16_t * virtualPin;

void setUp(void)
{
}

void tearDown(void)
{
}

// void test_LedScheduler_ScheduledDelay_didnt_arrive_yet(void)
// {
//   LedScheduler_ScheduleDelay(10, 500);
//   FakeTimeService_SetMilliseconds(499);
//   LedScheduler_WakeUp();

//   TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, LedControllerSpy_GetLastId());
//   TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedControllerSpy_GetLastState());
// }

void test_LedScheduler_No_Lights_On_Initialization(void)
{
  LedController_Create(virtualPin);
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedControllerSpy_GetLastState());
}
