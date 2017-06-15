###Include:
include ../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(sysroot)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Files:
HEADERS = 
SOURCES = 

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -std=gnu11
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include


###Recipes:
headers:
	@echo "No headers here."

objfiles:
	$(COMPILE) -o $(OBJOUTPATH)/sys_0_default_syscall.syscall.o	\
		-c sys_0_default_syscall.c
	$(COMPILE) -o $(OBJOUTPATH)/sys_1_terminal_putchar.syscall.o \
		-c sys_1_terminal_putchar.c

clean:
	-rm -r $(SYSROOT)/usr/include/kernel
	-rm -r $(wildcard $(OBJOUTPATH)/*.syscall.o)
