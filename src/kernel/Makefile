###Include:
include ../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(sysroot)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Files:
HEADERS = include/kernel/io.h
SOURCES = kernel.c \
	   crti.asm \
	   crtn.asm \
	   boot.asm

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
	$(COMPILE) -o $(OBJOUTPATH)/kernel.kernel.o		-c kernel.c
	$(COMPILE) -o $(OBJOUTPATH)/pit.kernel.o		-c pit.c
	$(COMPILE) -o $(OBJOUTPATH)/ksleep.kernel.o		-c ksleep.c
	$(COMPILE) -o $(OBJOUTPATH)/panic.kernel.o		-c panic.c
	$(COMPILE) -o $(OBJOUTPATH)/syscall.kernel.o	-c syscall.c
	cd syscalls && $(MAKE) objfiles

clean:
	-rm -r $(SYSROOT)/usr/include/kernel
	-rm -r $(wildcard $(OBJOUTPATH)/*.kernel.o)
