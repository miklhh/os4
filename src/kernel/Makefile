###Include:
include ../make.config
GCC =$(CROSSCOMPILER)

###Paths:
BUILD = ../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(sysroot)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Files:
HEADERS := include/kernel/io.h
SOURCES := kernel.c \
	   crti.asm \
	   crtn.asm \
	   boot.asm

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -std=gnu11
ASMFLAGS = -Wall -O2 -std=gnu11 -felf32
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	   -isystem=/usr/include
ASSEMBLER = nasm $(ASMFLAGS) -D__is_kernel -Iinclude


###Recipes:
headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr/

objfiles:
	$(COMPILE) 	-o $(OBJOUTPATH)/kernel.kernel.o -c kernel.c
	$(ASSEMBLER) 	-o $(OBJOUTPATH)/boot.kernel.o	    boot/boot.asm
	$(ASSEMBLER) 	-o $(OBJOUTPATH)/crtn.crtx.o	    boot/crtn.asm
	$(ASSEMBLER) 	-o $(OBJOUTPATH)/crti.crtx.o	    boot/crti.asm	
	#Comment: The prefix *.crtx.o is used so that the linkers wildcard
	#	  will not link the file crtx files twice.

clean:
	-rm -r $(SYSROOT)/usr/include/kernel
	-rm -r $(wildcard $(OBJOUTPATH)/*.kernel.o)
