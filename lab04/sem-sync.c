// ======================================================================
// File: sem-sync.c
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

OS_EVENT *sem;

// ======================================================================

int main(void) {
  OSInit();
    
	sem = OSSemCreate(1);
	OSTaskCreate(TaskStart, (void *) 0, &TaskStartStk[TASK_STK_SIZE - 1],
	       10);

  OSStart();

  return 0;
}

// ======================================================================

void TaskStart(void *pdata) {
  OSSoCInit();			// The first task should call this.
  OSStatInit();

	UARTputclear();
  OSTaskCreate(Task1, (void *)0, &Task1Stk[TASK_STK_SIZE - 1],
			11);
	OSTaskCreate(Task2, (void *)0, &Task2Stk[TASK_STK_SIZE - 1],
			12);
    
  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void Task1(void *pdata) {
	INT8U err;

  for (;;) {
		OSSemPend(sem, 0, &err);
		UARTputcolor(ANSI_COLOR_RED);
		UARTprintf("[Task1]");
		OSTimeDly(OS_GetRandom(200));
		OSSemPost(sem);
	}
}

// ======================================================================

void Task2(void *pdata) {
	INT8U err;

  for (;;) {
		OSSemPend(sem, 0, &err);
		UARTputcolor(ANSI_COLOR_BLUE);
		UARTprintf("[Task2]");
		OSTimeDly(OS_GetRandom(200));
		OSSemPost(sem);
	}
}

// ======================================================================
