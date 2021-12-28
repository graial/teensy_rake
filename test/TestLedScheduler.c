#include "unity.h"
#include "LedScheduler.h"
#include "LedControllerSpy.h"
#include "FakeTimeService.h"

void setUp(void)
{
  LedScheduler_Create();
  LedControllerSpy_Create();
}

void tearDown(void)
{
}

void test_LedScheduler_No_Schedule_No_Action_Taken(void)
{
  FakeTimeService_SetMilliseconds(365);
  LedScheduler_WakeUp();
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedControllerSpy_GetLastState());
}

void test_LedScheduler_No_Lights_On_Initialization(void)
{
  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedControllerSpy_GetLastState());
}

void test_LedScheduler_ScheduledDelay_didnt_arrive_yet(void)
{
  LedScheduler_ScheduleDelay(10, 500);
  FakeTimeService_SetMilliseconds(499);
  LedScheduler_WakeUp();

  TEST_ASSERT_EQUAL_HEX16(LED_ID_UNKNOWN, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_STATE_UNKNOWN, LedControllerSpy_GetLastState());
}

void test_LedScheduler_ScheduledDelay_just_arrived(void)
{
  LedScheduler_ScheduleDelay(4, 500);
  FakeTimeService_SetMilliseconds(500);
  LedScheduler_WakeUp();

  TEST_ASSERT_EQUAL_HEX16(4, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_ON, LedControllerSpy_GetLastState());
}

void test_LedScheduler_ScheduledDelay_just_arrived_Led_is_on(void)
{
  LedController_TurnOn(4);
  LedScheduler_ScheduleDelay(4, 500);
  FakeTimeService_SetMilliseconds(500);
  LedScheduler_WakeUp();

  TEST_ASSERT_EQUAL_HEX16(4, LedControllerSpy_GetLastId());
  TEST_ASSERT_EQUAL_HEX16(LED_OFF, LedControllerSpy_GetLastState());
}

void test_LedScheduler_Initializes_with_correct_alarm(void)
{
  TEST_ASSERT_EQUAL_PTR(
    &LedScheduler_WakeUp, 
    FakeTimeService_GetAlarmCallback()
  );
  TEST_ASSERT_EQUAL_HEX16(60, FakeTimeService_GetAlarmPeriod());
}

void test_LedScheduler_Destroy_cancels_alarm(void)
{
  LedScheduler_Destroy();
  TEST_ASSERT_EQUAL_PTR(
    NULL, 
    FakeTimeService_GetAlarmCallback());
}