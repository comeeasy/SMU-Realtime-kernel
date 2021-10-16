// ======================================================================
// File: tasks-priority.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512

// ======================================================================

void TaskStart(void *pdata);
void TaskTime(void *pdata);
void Task1(void *pdata);
void Task2(void *pdata);
void Task3(void *pdata);
void Task4(void *pdata);
void Task5(void *pdata);

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskTimeStk[TASK_STK_SIZE];
OS_STK Task1Stk[TASK_STK_SIZE];
OS_STK Task2Stk[TASK_STK_SIZE];
OS_STK Task3Stk[TASK_STK_SIZE];
OS_STK Task4Stk[TASK_STK_SIZE];
OS_STK Task5Stk[TASK_STK_SIZE];

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

  OSTaskCreate(TaskTime, (void *) 0, &TaskTimeStk[TASK_STK_SIZE - 1], 20);
  OSTaskCreate(Task1, (void *) 0, &Task1Stk[TASK_STK_SIZE - 1], 25);
  OSTaskCreate(Task2, (void *) 0, &Task2Stk[TASK_STK_SIZE - 1], 24);
  OSTaskCreate(Task3, (void *) 0, &Task3Stk[TASK_STK_SIZE - 1], 23);
  OSTaskCreate(Task4, (void *) 0, &Task4Stk[TASK_STK_SIZE - 1], 22);
  OSTaskCreate(Task5, (void *) 0, &Task5Stk[TASK_STK_SIZE - 1], 21);

  UARTputclear();
  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void TaskTime(void *pdata)
{
  for (;;) {
    OSTimeDly(100);
    UARTprintf("\nTime=%d: ", OSTimeGet() / 100);
  }
}

// ======================================================================

void Task1(void *pdata)
{
  for (;;) {
    OSTimeDly(100);
    UARTprintf("Task1 ");
  }
}

// ======================================================================

void Task2(void *pdata)
{
  for (;;) {
    OSTimeDly(200);
    UARTprintf("Task2 ");
  }
}

// ======================================================================

void Task3(void *pdata)
{
  for (;;) {
    OSTimeDly(300);
    UARTprintf("Task3 ");
  }
}

// ======================================================================

void Task4(void *pdata)
{
  for (;;) {
    OSTimeDly(400);
    UARTprintf("Task4 ");
  }
}

// ======================================================================

void Task5(void *pdata)
{
  for (;;) {
    OSTimeDly(500);
    UARTprintf("Task5 ");
  }
}

// ======================================================================
