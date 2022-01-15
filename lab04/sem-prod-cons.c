// ======================================================================
// File: sem-prod-cons.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"

// ======================================================================

#define TASK_STK_SIZE	512
#define	BUFFER_SIZE	9

// ======================================================================

void TaskStart(void *pdata);
void TaskProducer1(void *pdata);
void TaskProducer2(void *pdata);
void TaskConsumer1(void *pdata);
void TaskConsumer2(void *pdata);
void TaskPrinter(void *pdata);

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK TaskProducer1Stk[TASK_STK_SIZE];
OS_STK TaskProducer2Stk[TASK_STK_SIZE];
OS_STK TaskConsumer1Stk[TASK_STK_SIZE];
OS_STK TaskConsumer2Stk[TASK_STK_SIZE];
OS_STK TaskPrinterStk[TASK_STK_SIZE];

// ======================================================================

struct {
  unsigned int Front, Rear;
  unsigned int Data[BUFFER_SIZE];
} Buffer = {
0, 0,};

// ======================================================================

unsigned int producer_delay = 200;
unsigned int consumer_delay = 200;
unsigned int printer_delay = 20;

OS_EVENT *sem_buf_access;
OS_EVENT *sem_buf_add;
OS_EVENT *sem_buf_rm;

// ======================================================================

int AddToBuffer(int item);
int RemoveFromBuffer(void);
void PrintBuffer(void);

// ======================================================================

int main(void)
{
  OSInit();
	UARTputclear();

	sem_buf_access = OSSemCreate(1);
	// circular queue must remain ont elem 
	sem_buf_add = OSSemCreate(BUFFER_SIZE-1); 
	sem_buf_rm = OSSemCreate(0);

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
	
	OSTaskCreate(TaskPrinter, (void* )0, &TaskPrinterStk[TASK_STK_SIZE-1],
			20);
  OSTaskCreate(TaskProducer1, (void* )0, &TaskProducer1Stk[TASK_STK_SIZE-1],
			21);
	OSTaskCreate(TaskProducer2, (void* )0, &TaskProducer2Stk[TASK_STK_SIZE-1],
			22);
 	OSTaskCreate(TaskConsumer1, (void* )0, &TaskConsumer1Stk[TASK_STK_SIZE-1],
			23);
	OSTaskCreate(TaskConsumer2, (void* )0, &TaskConsumer2Stk[TASK_STK_SIZE-1],
			24);

  OSTaskDel(OS_PRIO_SELF);
}

// ======================================================================

void TaskProducer1(void *pdata) {
	unsigned int item;
	INT8U err;

	for (;;) {
		OSSemPend(sem_buf_add, 0, &err);
		item = OS_GetRandom(10000);

		OSSemPend(sem_buf_access, 0, &err);
		AddToBuffer(item);
		OSSemPost(sem_buf_access);

		UARTputgoto(0, 3);
		UARTprintf("Producer1 dly=%d: %d", producer_delay, item);

		OSSemPost(sem_buf_rm);

		OSTimeDly(producer_delay);
	}
}

void TaskProducer2(void *pdata) {
  unsigned int item;
	INT8U err;
	
		for (;;) {
			OSSemPend(sem_buf_add, 0, &err);
			item = OS_GetRandom(10000);

			OSSemPend(sem_buf_access, 0, &err);
			AddToBuffer(item);
			OSSemPost(sem_buf_access);

			UARTputgoto(0, 4);
			UARTprintf("Producer2 dly=%d: %d", producer_delay, item);

			OSSemPost(sem_buf_rm);

			OSTimeDly(producer_delay);
		}
}

// ======================================================================

void TaskConsumer1(void *pdata) {
  unsigned int item;
	INT8U err;

	for (;;) {
		OSSemPend(sem_buf_rm, 0, &err);
		
		OSSemPend(sem_buf_access, 0, &err);
		item = RemoveFromBuffer();
		OSSemPost(sem_buf_access);
		
		UARTputgoto(0, 6);
		UARTprintf("Consumer1 dly=%d: %d", consumer_delay, item);

		OSSemPost(sem_buf_add);

		OSTimeDly(consumer_delay);
	}
}

void TaskConsumer2(void *pdata) {
  unsigned int item;
	INT8U err;

	for (;;) {
		OSSemPend(sem_buf_rm, 0, &err);
		
		OSSemPend(sem_buf_access, 0, &err);
		item = RemoveFromBuffer();
		OSSemPost(sem_buf_access);
		
		UARTputgoto(0, 7);
		UARTprintf("Consumer2 dly=%d: %d", consumer_delay, item);

		OSSemPost(sem_buf_add);

		OSTimeDly(consumer_delay);
	}
}

// ======================================================================

void TaskPrinter(void *pdata) {
	int c;

	for (;;) {
		UARTputgoto(0, 1);
		UARTprintf("Ticks=%d, Task=%d, CPU=%d%%", OSTime, OSTaskCtr, OSCPUUsage);

		UARTputgoto(0, 5);
		UARTprintf("\x1b[2K");
		PrintBuffer();

		while((c = UARTgetc_nb()) != -1) {
			switch(c) {
				case '=':
				case '+': 
									if (consumer_delay < 250)
										consumer_delay += 10; 
									break;
				case '-':
									if (consumer_delay > 150)
										consumer_delay -= 10; 
									break; 
			}
		}

		OSTimeDly(printer_delay);
	}
}

// ======================================================================

int AddToBuffer(int item)
{
  Buffer.Rear = (Buffer.Rear + 1) % BUFFER_SIZE;
  Buffer.Data[Buffer.Rear] = item;

  return Buffer.Rear;
}

// ======================================================================

int RemoveFromBuffer(void)
{
  unsigned int item;

  Buffer.Front = (Buffer.Front + 1) % BUFFER_SIZE;
  item = Buffer.Data[Buffer.Front];

  return item;
}

// ======================================================================      

void PrintBuffer(void)
{
  int i, j, size;

  size = Buffer.Rear >= Buffer.Front ? (Buffer.Rear - Buffer.Front) :
      (Buffer.Rear + BUFFER_SIZE - Buffer.Front);

  UARTprintf("Buffers[] len=%03d: ", size);
  j = Buffer.Front + 1;
  for (i = 0; i < size; i++) {
    UARTprintf("%d ", Buffer.Data[j % BUFFER_SIZE]);
    j = j + 1;
  }
}

// ======================================================================
