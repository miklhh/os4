###Include:
include ../../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../../build
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
	echo "No headers here."

objfiles:
	$(ASSEMBLE) -o $(OBJOUTPATH)/__idt_default_handler.arch.o \
	    __idt_default_handler.asm
	$(ASSEMBLE) -o $(OBJOUTPATH)/interrupt_test_handler_wrapper.arch.o \
	    interrupt_test_handler.asm
	$(ASSEMBLE) -o $(OBJOUTPATH)/pit_irq_wrapper.arch.o \
	    pit_irq_wrapper.asm
	$(ASSEMBLE) -o $(OBJOUTPATH)/keyboard_irq_wrapper.arch.o \
	    keyboard_irq_wrapper.asm
	$(ASSEMBLE) -o $(OBJOUTPATH)/exception_wrappers.arch.o \
		exception_wrappers.asm
	$(ASSEMBLE) -o $(OBJOUTPATH)/syscall_wapper.arch.o \
		syscall_wrapper.asm

clean:
	echo "Nothing to clean here."
