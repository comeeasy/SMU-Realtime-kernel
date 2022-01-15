// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

void pready(void)
{
	OS_CPU_SR cpu_sr;

	OS_ENTER_CRITICAL();
	UARTprintf("   7 6 5 4 3 2 1 0\n");
	UARTprintf(" +----------------\n");

  for(int i=0; i<8; ++i) {
		UARTprintf("%d|", i);
		for(int j=0; j<8; ++j) {
			UARTprintf(" %d", (OSRdyTbl[i] & OSMapTbl[7 - j]) != 0);
		}
		UARTprintf("\n");
	}
	UARTprintf("\n");
	OS_EXIT_CRITICAL();
}

// ======================================================================

OS_STK TaskStk[10][128];

void Task(void *pdata)
{
  int i, j;

  for (;;) {
    for (i = 0; i < 0x00000ffff; i++)
      j++;			// Run without waiting.
  }
}

// ======================================================================

OS_STK TaskStartStk[128];

void TaskStart(void *pdata)
{
  int i;

  OSSoCInit();			// The first task should call this.
  OSStatInit();

  UARTputclear();
  UARTprintf("==========\n");
  UARTprintf("2-pready\n");
  UARTprintf("==========\n\n");

  OSTimeDly(100);

  for (i = 0; i < 10; i++)
    OSTaskCreate(Task, 0, &TaskStk[i][128 - 1], 10 + i);

  pready();

  OSTimeDly(100);

  for (i = 0; i < 10; i++)
    OSTaskDel(10 + i);

  pready();

  for (;;)			// Wait forever.
    ;
}

// ======================================================================

int main(void)
{
  OSInit();

  OSTaskCreate(TaskStart, (void *) 0, &TaskStartStk[128 - 1], 5);

  OSStart();

  return 0;
}

// ======================================================================
