// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

void sprio(INT8U prio1, INT8U prio2)
{
	OS_CPU_SR cpu_sr;
	INT8U tmp;
	OS_TCB *tcbtmp;

	OS_ENTER_CRITICAL();
	
	// OSTCBPrio swap
	tmp = OSTCBPrioTbl[prio1]->OSTCBPrio;
	OSTCBPrioTbl[prio1]->OSTCBPrio = OSTCBPrioTbl[prio2]->OSTCBPrio;
	OSTCBPrioTbl[prio2]->OSTCBPrio = tmp;

	// OSTCBX
	tmp = OSTCBPrioTbl[prio1]->OSTCBX;
	OSTCBPrioTbl[prio1]->OSTCBX = OSTCBPrioTbl[prio2]->OSTCBX;
	OSTCBPrioTbl[prio2]->OSTCBX = tmp;
	
	// OSTCBY
	tmp = OSTCBPrioTbl[prio1]->OSTCBY;
	OSTCBPrioTbl[prio1]->OSTCBY = OSTCBPrioTbl[prio2]->OSTCBY;
	OSTCBPrioTbl[prio2]->OSTCBY = tmp;

	// OSTCBBitX
	tmp = OSTCBPrioTbl[prio1]->OSTCBBitX;
	OSTCBPrioTbl[prio1]->OSTCBBitX = OSTCBPrioTbl[prio2]->OSTCBBitX;
	OSTCBPrioTbl[prio2]->OSTCBBitX = tmp;

	// OSTCBBitY
	tmp = OSTCBPrioTbl[prio1]->OSTCBBitY;
	OSTCBPrioTbl[prio1]->OSTCBBitY = OSTCBPrioTbl[prio2]->OSTCBBitY;
	OSTCBPrioTbl[prio2]->OSTCBBitY = tmp;

	// TCB
	tcbtmp = OSTCBPrioTbl[prio1];
	OSTCBPrioTbl[prio1] = OSTCBPrioTbl[prio2];
	OSTCBPrioTbl[prio2] = tcbtmp;
	OS_EXIT_CRITICAL();

	
}

// ======================================================================

OS_STK Task1Stk[128];

void Task1(void *pdata)
{
  for (;;) {
    OSTimeDly(200);
    UARTprintf("Task1 ");
  }
}

// ======================================================================

OS_STK Task2Stk[128];

void Task2(void *pdata)
{
  for (;;) {
    OSTimeDly(200);
    UARTprintf("Task2 ");
  }

}

// ======================================================================

OS_STK TaskStartStk[128];

void TaskStart(void *pdata)
{
  unsigned int uptime;

  OSSoCInit();			// The first task should call this.
  OSStatInit();

  UARTputclear();
  UARTprintf("==========\n");
  UARTprintf("3-sprio\n");
  UARTprintf("==========\n");

  OSTaskCreate(Task1, 0, &Task1Stk[128 - 1], 10);
  OSTaskCreate(Task2, 0, &Task2Stk[128 - 1], 20);

  UARTprintf("\nTime=0: ");
  for (;;) {
    OSTimeDly(200);
    uptime = OSTimeGet() / 100;
    if ((uptime % 5) == 0) {
      UARTprintf("\n*** priority swapped ***");
      sprio(10, 20);
    }
    UARTprintf("\nTime=%d: ", uptime);
  }
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
