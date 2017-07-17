###Include:
include ../../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(sysroot)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -std=gnu11
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include


###Recipes:
headers:
	@echo "No headers here."

objfiles:
	$(COMPILE) -o $(OBJOUTPATH)/sys_0_default_syscall.sys.kernel.o		\
		-c sys_0_default_syscall.c
	$(COMPILE) -o $(OBJOUTPATH)/sys_1_terminal_putchar.sys.kernel.o 	\
		-c sys_1_terminal_putchar.c
	$(COMPILE) -o $(OBJOUTPATH)/sys_2_sleep.sys.kernel.o				\
		-c sys_2_sleep.c

clean:
	-rm -r $(SYSROOT)/usr/include/kernel
	-rm -r $(wildcard $(OBJOUTPATH)/*.syscall.o)
