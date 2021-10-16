# ======================================================================
# File: Makefile
# ======================================================================

UCOS_ROOT_DIR=/home/rk/uCOS-II-2.92.10-tm4c1294xl
UCOS_SOURCE_DIR=$(UCOS_ROOT_DIR)/Source
UCOS_PORT_DIR=$(UCOS_ROOT_DIR)/Ports
LIB_TM4C1294XL_DIR=$(UCOS_ROOT_DIR)/Lib/tm4c1294xl
LIB_UTILITY_DIR=$(UCOS_ROOT_DIR)/Lib/utility
TIVAWARE_DIR=/home/rk/SW-TM4C-2.2.0.295

# ======================================================================

UCOS_OBJS=$(UCOS_SOURCE_DIR)/os_core.o $(UCOS_SOURCE_DIR)/os_flag.o $(UCOS_SOURCE_DIR)/os_mbox.o $(UCOS_SOURCE_DIR)/os_mem.o $(UCOS_SOURCE_DIR)/os_mutex.o $(UCOS_SOURCE_DIR)/os_q.o $(UCOS_SOURCE_DIR)/os_sem.o $(UCOS_SOURCE_DIR)/os_task.o $(UCOS_SOURCE_DIR)/os_time.o $(UCOS_SOURCE_DIR)/os_tmr.o $(UCOS_SOURCE_DIR)/os_hooks.o
UCOS_PORT_OBJS=$(UCOS_PORT_DIR)/os_cpu_c.o $(UCOS_PORT_DIR)/os_cpu_a.o $(UCOS_PORT_DIR)/os_dbg.o

# ======================================================================

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

# ======================================================================

ASFLAGS=-mthumb -mcpu=cortex-m4
CFLAGS=-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_TM4C1294NCPDT -c -Os -DTARGET_IS_TM4C129_RA2 -I. -I$(UCOS_SOURCE_DIR) -I$(UCOS_PORT_DIR) -I$(LIB_TM4C1294XL_DIR) -I$(LIB_UTILITY_DIR) -I$(TIVAWARE_DIR) -Dgcc
LDFLAGS=-T $(LIB_TM4C1294XL_DIR)/link.ld --entry ResetISR --gc-sections -L $(LIB_TM4C1294XL_DIR) -L $(LIB_UTILITY_DIR)
LIBRARIES=-ldriver -lutility

# ======================================================================

all:	mutual-problem.elf mutual-problem.bin mutual-problem.dis1 mutual-problem.dis2 \
	mutual-critical.elf mutual-critical.bin mutual-critical.dis1 mutual-critical.dis2 \
	mutual-scheduler.elf mutual-scheduler.bin mutual-scheduler.dis1 mutual-scheduler.dis2 \
	mutual-semaphore.elf mutual-semaphore.bin mutual-semaphore.dis1 mutual-semaphore.dis2

# ======================================================================

mutual-problem.elf:	mutual-problem.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o mutual-problem.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o mutual-problem.elf

mutual-problem.bin:	mutual-problem.elf
	$(OBJCOPY) -O binary mutual-problem.elf mutual-problem.bin

mutual-problem.dis1:	mutual-problem.elf
	$(OBJDUMP) -Dx mutual-problem.elf > mutual-problem.dis1

mutual-problem.dis2:	mutual-problem.elf
	$(OBJDUMP) -DSx mutual-problem.elf > mutual-problem.dis2

# ======================================================================

mutual-critical.elf:	mutual-critical.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o mutual-critical.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o mutual-critical.elf

mutual-critical.bin:	mutual-critical.elf
	$(OBJCOPY) -O binary mutual-critical.elf mutual-critical.bin

mutual-critical.dis1:	mutual-critical.elf
	$(OBJDUMP) -Dx mutual-critical.elf > mutual-critical.dis1

mutual-critical.dis2:	mutual-critical.elf
	$(OBJDUMP) -DSx mutual-critical.elf > mutual-critical.dis2

# ======================================================================

mutual-scheduler.elf:	mutual-scheduler.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o mutual-scheduler.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o mutual-scheduler.elf

mutual-scheduler.bin:	mutual-scheduler.elf
	$(OBJCOPY) -O binary mutual-scheduler.elf mutual-scheduler.bin

mutual-scheduler.dis1:	mutual-scheduler.elf
	$(OBJDUMP) -Dx mutual-scheduler.elf > mutual-scheduler.dis1

mutual-scheduler.dis2:	mutual-scheduler.elf
	$(OBJDUMP) -DSx mutual-scheduler.elf > mutual-scheduler.dis2

# ======================================================================

mutual-semaphore.elf:	mutual-semaphore.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o mutual-semaphore.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o mutual-semaphore.elf

mutual-semaphore.bin:	mutual-semaphore.elf
	$(OBJCOPY) -O binary mutual-semaphore.elf mutual-semaphore.bin

mutual-semaphore.dis1:	mutual-semaphore.elf
	$(OBJDUMP) -Dx mutual-semaphore.elf > mutual-semaphore.dis1

mutual-semaphore.dis2:	mutual-semaphore.elf
	$(OBJDUMP) -DSx mutual-semaphore.elf > mutual-semaphore.dis2

# ======================================================================

indent:
	indent -i2 -kr -nfca *.c
	@rm -f *~

# ======================================================================

clean:
	@rm -f *~ *.o *.d *.elf *.bin *.dis1 *.dis2

# ======================================================================
