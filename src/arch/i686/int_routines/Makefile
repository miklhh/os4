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
	$(ASSEMBLE) -o $(OBJOUTPATH)/_set_idtr.arch.o \
		    _set_idtr.asm
	$(ASSEMBLE) -o $(OBJOUTPATH)/pit_irq_wrapper.arch.o \
		    pit_irq_wrapper.asm

	$(COMPILE) -o $(OBJOUTPATH)/interrupt_test_handler.arch.o \
		   -c interrupt_test_handler.c

clean:
	echo "Nothing to clean here."