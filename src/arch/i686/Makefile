###Include:
include ../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../build
SYSROOT = $(BUILD)/sysroot
OBJOUTPATH = $(BUILD)/objfiles

###Files:
SOURCES = boot.asm crtn.asm crti.asm io.c

###Build-options:
CFLAGS = -ffreestanding -O2 -Wall -Wextra -g -std=gnu11
ASMFLAGS = -Wall -O2 -std=gnu11 -felf32
ASSEMBLE = nasm $(ASMFLAGS) -D__is_kernel -Iinclude
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include

###Recipes:
headers:
	cd memory && make headers
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr/

objfiles: $(SOURCES)
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/boot.arch.o	   boot.asm
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/crtn.crtx.o	   crtn.asm
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/crti.crtx.o	   crti.asm
	#Comment: The prefix *.crtx.o is used so that the linkers wildcard
	#	  will not link the file crtx files twice.
	$(COMPILE) 	-o $(OBJOUTPATH)/io.arch.o	-c io.c
	$(COMPILE)	-o $(OBJOUTPATH)/gdt.arch.o	-c gdt.c

	cd memory && make objfiles

clean:
	-rm -r $(wildcard $(OBJOUTPATH)/*.arch.o)
	-rm -r $(wildcard $(OBJOUTPATH)/*.crtx.o)
