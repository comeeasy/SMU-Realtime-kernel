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

all:	sem-sync.elf sem-sync.bin sem-sync.dis1 sem-sync.dis2 \
	sem-prod-cons.elf sem-prod-cons.bin sem-prod-cons.dis1 sem-prod-cons.dis2 \
	sem-dine-phil.elf sem-dine-phil.bin sem-dine-phil.dis1 sem-dine-phil.dis2

# ======================================================================

sem-sync.elf:	sem-sync.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o sem-sync.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o sem-sync.elf

sem-sync.bin:	sem-sync.elf
	$(OBJCOPY) -O binary sem-sync.elf sem-sync.bin

sem-sync.dis1:	sem-sync.elf
	$(OBJDUMP) -Dx sem-sync.elf > sem-sync.dis1

sem-sync.dis2:	sem-sync.elf
	$(OBJDUMP) -DSx sem-sync.elf > sem-sync.dis2

# ======================================================================

sem-prod-cons.elf:	sem-prod-cons.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o sem-prod-cons.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o sem-prod-cons.elf

sem-prod-cons.bin:	sem-prod-cons.elf
	$(OBJCOPY) -O binary sem-prod-cons.elf sem-prod-cons.bin

sem-prod-cons.dis1:	sem-prod-cons.elf
	$(OBJDUMP) -Dx sem-prod-cons.elf > sem-prod-cons.dis1

sem-prod-cons.dis2:	sem-prod-cons.elf
	$(OBJDUMP) -DSx sem-prod-cons.elf > sem-prod-cons.dis2

# ======================================================================

sem-dine-phil.elf:	sem-dine-phil.o $(UCOS_OBJS) $(UCOS_PORT_OBJS)
	$(LD) $(LDFLAGS) $(LIB_TM4C1294XL_DIR)/startup.o sem-dine-phil.o $(LIB_TM4C1294XL_DIR)/tm4c1294xl.o $(LIB_TM4C1294XL_DIR)/pinout.o $(LIB_TM4C1294XL_DIR)/uartstdio.o $(UCOS_OBJS) $(UCOS_PORT_OBJS) $(LIBRARIES) -o sem-dine-phil.elf

sem-dine-phil.bin:	sem-dine-phil.elf
	$(OBJCOPY) -O binary sem-dine-phil.elf sem-dine-phil.bin

sem-dine-phil.dis1:	sem-dine-phil.elf
	$(OBJDUMP) -Dx sem-dine-phil.elf > sem-dine-phil.dis1

sem-dine-phil.dis2:	sem-dine-phil.elf
	$(OBJDUMP) -DSx sem-dine-phil.elf > sem-dine-phil.dis2

# ======================================================================

indent:
	indent -i2 -kr -nfca *.c
	@rm -f *~

# ======================================================================

clean:
	@rm -f *~ *.o *.d *.elf *.bin *.dis1 *.dis2

# ======================================================================
