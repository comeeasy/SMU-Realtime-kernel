// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

OS_EVENT *sem1;
OS_EVENT *sem2;
OS_EVENT *sem3;

// ======================================================================

OS_STK Task1Stk[128];

void Task1(void *pdata)
{
	INT8U err;

  for(;;) {
		OSSemPend(sem3, 0, &err);
		OSTimeDly(100);
		UARTprintf("Task1 ");
		OSSemPost(sem1);
	}
}

// ======================================================================

OS_STK Task2Stk[128];

void Task2(void *pdata)
{
	INT8U err;

  for(;;) {
		OSSemPend(sem1, 0, &err);
		OSTimeDly(200);
		UARTprintf("Task2 ");
		OSSemPost(sem2);
	}
}

// ======================================================================

OS_STK Task3Stk[128];

void Task3(void *pdata)
{
	INT8U err;

  for(;;) {
		OSSemPend(sem2, 0, &err);
		OSTimeDly(300);
		UARTprintf("Task3 ");
		OSSemPost(sem3);
	}
}

// ======================================================================

OS_STK TaskStartStk[128];

void TaskStart(void *pdata)
{
  OSSoCInit();			// The first task should call this.
  OSStatInit();

  UARTputclear();
  UARTprintf("==========\n");
  UARTprintf("1-sync\n");
  UARTprintf("==========\n\n");

  OSTaskCreate(Task1, 0, &Task1Stk[128 - 1], 30);
  OSTaskCreate(Task2, 0, &Task2Stk[128 - 1], 20);
  OSTaskCreate(Task3, 0, &Task3Stk[128 - 1], 10);

  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

int main(void)
{
  OSInit();

  sem1 = OSSemCreate(0);
	sem2 = OSSemCreate(0);
	sem3 = OSSemCreate(1);
  

  OSTaskCreate(TaskStart, (void *) 0, &TaskStartStk[128 - 1], 5);

  OSStart();

  return 0;
}

// ======================================================================
