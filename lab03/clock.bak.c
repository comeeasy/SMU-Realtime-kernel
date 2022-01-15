// ======================================================================
// File: clock.c
// ======================================================================

#include "ucos_ii.h"
#include "tm4c1294xl.h"
#include "utility.h"
#include "fonts.h"

// ======================================================================

#define TASK_STK_SIZE	512
#define LCD_LEN 5
#define FONT_NROW 9
#define FONT_NCOL 8

void TaskStart(void *pdata);
void DisplayClock(void *pdata);

void timer_callback(void *ptmr, void *parg);

void displayMenubar();

// ======================================================================

OS_STK TaskStartStk[TASK_STK_SIZE];
OS_STK DisplayClockStk[TASK_STK_SIZE];

int sec;
char pixel;

#if OS_CRITICAL_METHOD == 3u
	OS_CPU_SR cpu_sr;
#endif

// ======================================================================

int main(void)
{
  OSInit();

  OSTaskCreate(TaskStart, (void *) 0, 
			&TaskStartStk[TASK_STK_SIZE - 1],
	    10);

  OSStart();

  return 0;
}

// ======================================================================

void TaskStart(void *pdata) {
	int dly = 0;
	int period = 10;
	int perr;
	int buf = '0';

  OSSoCInit();			// The first task should call this.
  OSStatInit();

	// periodic timer of delay=0, period=10
  OS_TMR *tmr = OSTmrCreate(
			dly, 
			period,
			OS_TMR_OPT_PERIODIC,
			timer_callback,
			(void *)0,
			(void *)0, 
			&perr
	);
	OSTmrStart(tmr, &perr);

	OSTaskCreate(
			DisplayClock, 
			(void *)0, 
			&DisplayClockStk[TASK_STK_SIZE - 1],
			11
	);

	pixel = buf;
	for(;;) {
		displayMenubar();

		OS_ENTER_CRITICAL();
	  while( (buf = UARTgetc_nb()) != -1) {
			switch(buf) {
				case 's': sec--; break;
				case 'S': sec++; break;
				case 'm': sec -= 60; break;
				case 'M': sec += 60; break;
				case '\n':
				case '\r':
									UARTputclear(); 
									OS_EXIT_CRITICAL();
									displayMenubar(); 
									OS_ENTER_CRITICAL();
									break;
				default: pixel = buf;
			}

			if (sec > 3600 || sec < 0)
				sec = 0;
		}
		OS_EXIT_CRITICAL();

		OSTimeDly(100);
	}
}

// =====================================================================

void displayMenubar() {
		OS_ENTER_CRITICAL();
		UARTputgoto(0, 0);
		UARTprintf("uC/OS-II: clock");
		UARTputgoto(0, 1);
		UARTprintf("Time=%02d:%02d, Tasks=%d, CPU=%d%%", 
				sec / 60, sec % 60, OSTaskCtr, OSCPUUsage);
		UARTputgoto(0, 13);
		UARTprintf("Type 'M'/'m' or 'S'/'s' to adjust min and sec.");
		OS_EXIT_CRITICAL();
}

// ======================================================================

void DisplayClock(void *pdata) {
	// char series to display clock
	char lcd[LCD_LEN];

	lcd[2] = ':' - ' ';
  for(;;) {
		lcd[0] = ((sec / 60) / 10) + '0' - ' ';
		lcd[1] = ((sec / 60) % 10) + '0' - ' ';
		lcd[3] = ((sec / 10) % 6) + '0' - ' ';
		lcd[4] = (sec % 10) + '0' - ' ';

		OS_ENTER_CRITICAL();
		UARTputgoto(0, 3);
		
		for(int r=0; r<FONT_NROW; ++r) {
			for(int i=0; i<LCD_LEN; ++i) {
				for(int c=0; c<FONT_NCOL; ++c) {
					if (font_table[lcd[i]].font[r][c]) 
						UARTputc(pixel);
					else
						UARTputc(' ');
				}
			}
			UARTputc('\n');
		}

		OS_EXIT_CRITICAL();
		OSTimeDly(100);
	}
}

// ======================================================================

void timer_callback(void *ptmr, void *parg) {
	OS_ENTER_CRITICAL();
	sec++;
	OS_EXIT_CRITICAL();
}

// ======================================================================
