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
	cd sys && $(MAKE) headers

objfiles:
	$(COMPILE) -o $(OBJOUTPATH)/kernel.kernel.o		-c kernel.c
	$(COMPILE) -o $(OBJOUTPATH)/timer.kernel.o		-c timer.c
	$(COMPILE) -o $(OBJOUTPATH)/ksleep.kernel.o		-c ksleep.c
	cd sys && $(MAKE) objfiles

clean:
	-rm -r $(SYSROOT)/usr/include/kernel
	-rm -r $(wildcard $(OBJOUTPATH)/*.kernel.o)
	cd sys && $(MAKE) clean
