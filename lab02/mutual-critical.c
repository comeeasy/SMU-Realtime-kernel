// ======================================================================
// File: mutual-critical.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512

// ======================================================================

void TaskStart(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];

// ======================================================================

int main(void)
{
  OSInit();

  OSTaskCreate(TaskStart, (void *) 0, &TaskStartStk[TASK_STK_SIZE - 1],
	       10);

  OSStart();

  return 0;
}

// ======================================================================

void TaskStart(void *pdata)
{
  OSSoCInit();			// The first task should call this.
  OSStatInit();

  OSTaskCreate(Task1, (void *) 0, &Task1Stk[TASK_STK_SIZE - 1], 20);
  OSTaskCreate(Task2, (void *) 0, &Task2Stk[TASK_STK_SIZE - 1], 21);

  UARTputclear();

  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void Task1(void *pdata) {
	OS_CPU_SR cpu_sr;

  for (;;) {
    OS_ENTER_CRITICAL();
    UARTprintf("11111111111111111111111111111111111111111111111111\n");
    OS_EXIT_CRITICAL();
    OSTimeDly(OS_GetRandom(5));
  }
}

// ======================================================================

void Task2(void *pdata) {
	OS_CPU_SR cpu_sr;

  for (;;) {
    OS_ENTER_CRITICAL();
    UARTprintf("22222222222222222222222222222222222222222222222222\n");
    OS_EXIT_CRITICAL();
    OSTimeDly(OS_GetRandom(5));
  }
}

// ======================================================================
