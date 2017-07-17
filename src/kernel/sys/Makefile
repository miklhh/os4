###Include:
include ../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(sysroot)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -std=gnu11
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	-isystem=/usr/include

###Recipes:
headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr/
	cd syscalls && $(MAKE) headers

objfiles:
	$(COMPILE) -o $(OBJOUTPATH)/panic.sys.kernel.o		-c panic.c
	$(COMPILE) -o $(OBJOUTPATH)/syscall.sys.kernel.o	-c syscall.c
	$(COMPILE) -o $(OBJOUTPATH)/task.sys.kernel.o		-c task.c
	cd syscalls && $(MAKE) objfiles

clean:
	-rm -r $(SYSROOT)/usr/include/kernel
	-rm -r $(wildcard $(OBJOUTPATH)/*.sys.kernel.o)
