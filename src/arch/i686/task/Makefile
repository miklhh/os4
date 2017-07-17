###Include:
include ../../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../../build
SYSROOT = $(BUILD)/sysroot
OBJOUTPATH = $(BUILD)/objfiles

###Build-options:
CFLAGS = -ffreestanding -O2 -Wall -Wextra -g -std=gnu11
ASMFLAGS = -Wall -O2 -std=gnu11 -felf32
ASSEMBLE = nasm $(ASMFLAGS) -D__is_kernel -Iinclude
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include

###Recipes:
headers:
	@echo "No headers here."

objfiles: $(SOURCES)
	$(ASSEMBLE)													\
	-o $(OBJOUTPATH)/task.task.arch.o							\
	task.asm

clean:
	-rm -r $(wildcard $(OBJOUTPATH)/*.arch.o)
