// ======================================================================
// File: tasks-random.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512
#define N_TASKS		10

// ======================================================================

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskStk[N_TASKS][TASK_STK_SIZE];

// ======================================================================

void TaskStart(void *data);
void Task(void *data);

char TaskData[N_TASKS];

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
  unsigned char i;

  OSSoCInit();			// The first task should call this.
  OSStatInit();
  
  for(int i=0; i<10; ++i) {
    TaskData[i] = i + '0';
    OSTaskCreate(Task, (void *) (TaskData + i), &TaskStk[i][TASK_STK_SIZE - 1], 20 + i);
  }

refresh:
  UARTputclear();
  UARTputcolor(ANSI_COLOR_BLACK);
  UARTprintf("Real-time kernel: random tasks");
  UARTputgoto(0, 20);
  UARTprintf("Type any char to refresh the screen.");
  for (;;) {
    if (UARTgetc_nb() != -1)
      goto refresh;
    UARTputcolor(ANSI_COLOR_BLACK);
    UARTputgoto(0, 1);
    UARTprintf("Ticks=%d, Tasks=%d, CPU=%d%%   ", OSTimeGet(), OSTaskCtr,
	       OSCPUUsage);
    OSTimeDly(100);
  }

  UARTputclear();
  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void Task(void *pdata) {
  unsigned short x = 0, y = 0, color = 0;

  for(;;) {
    OSTimeDly(5);

    x = OS_GetRandom(50);		// 0 - 49
    y = 3 + OS_GetRandom(16);		// 3 - 18
    color = 30 + OS_GetRandom(8);	// 30 - 37

    UARTputgoto(x, y);
    UARTputcolor(color);
    UARTputc(*(char *)pdata);
  }
}

// ======================================================================
