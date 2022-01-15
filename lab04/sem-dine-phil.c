// ======================================================================
// File: sem-dine-phil.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define NO_OF_PHILOSOPHERS	5
#define TASK_STK_SIZE	512
#define True 1
#define False 0

// ======================================================================

void TaskStart(void *pdata);
void TaskPrint(void *pdata);
void TaskPhilosopher(void *pdata);

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskPhilosopherStk[NO_OF_PHILOSOPHERS][TASK_STK_SIZE];
OS_STK TaskPrintStk[TASK_STK_SIZE];

OS_EVENT *sem[NO_OF_PHILOSOPHERS];

int phil_numbers[NO_OF_PHILOSOPHERS];

// ======================================================================

int main(void) {
  OSInit();

  OSTaskCreate(TaskStart, (void *) 0, &TaskStartStk[TASK_STK_SIZE - 1],
	       10);
	
  OSStart();
	
  return 0;
}

// ======================================================================

void TaskStart(void *pdata) {
  OSSoCInit();			// The first task should call this.
  OSStatInit();

	OSTaskCreate(TaskPrint, (void *)0, &TaskPrintStk[TASK_STK_SIZE],
			19);

	for (int i=0; i<NO_OF_PHILOSOPHERS; ++i) {
		phil_numbers[i] = i;
		OSTaskCreate(TaskPhilosopher, &phil_numbers[i], &TaskPhilosopherStk[i][TASK_STK_SIZE-1],
				20 + i);
		sem[i] = OSSemCreate(1);
	}

	UARTputclear();
  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void TaskPrint(void *pdata) {
	int c;

	for (;;) {
PRINT:
		UARTputcolor(ANSI_COLOR_BLACK);
		UARTputgoto(0, 0);
		UARTprintf("Real-time kernel: dining philosophers");

		UARTputgoto(0, 1);
		UARTprintf("Ticks=%d, Task=%d, CPU=%d%%", OSTime, OSTaskCtr, OSCPUUsage);
		
		UARTputgoto(0, 9);
		UARTprintf("Type any char to refresh the screen.");

		while((c = UARTgetc_nb()) != -1) {
			goto PRINT;
		}

		OSTimeDly(100);
	}
}

// ======================================================================

void TaskPhilosopher(void *pdata) {
  INT8U err;
	int number = *(int *)pdata;
	int left_fork = number;
	int right_fork = (number + 1) % NO_OF_PHILOSOPHERS;
	

	for (;;) {
		// thinking
		UARTputgoto(0, 3+number);
		UARTputcolor(ANSI_COLOR_BLUE);
		UARTprintf("Philosopher %d is thinking...", number);
		OSTimeDly(200 + OS_GetRandom(50));

		//eating
		if (number % 2 == 0) {
			OSSemPend(sem[left_fork], 0, &err);
			OSSemPend(sem[right_fork], 0, &err);
		} else {
			OSSemPend(sem[right_fork], 0, &err);
			OSSemPend(sem[left_fork], 0, &err);
		}

		UARTputgoto(0, 3+number);
		UARTputcolor(ANSI_COLOR_MAGENTA);
		UARTprintf("Philosopher %d is eating...", number);
		OSTimeDly(200 + OS_GetRandom(50));

		OSSemPost(sem[left_fork]);
		OSSemPost(sem[right_fork]);
	}
}

// ======================================================================
