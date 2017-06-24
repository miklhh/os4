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
	cd int_routines && make headers
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr/

objfiles: $(SOURCES)
	$(ASSEMBLE)		-o $(OBJOUTPATH)/cpuid.arch.o		cpuid.asm
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/boot.arch.o	   	boot.asm
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/task.arch.o	   	task.asm
	$(ASSEMBLE) 										\
		-o $(OBJOUTPATH)/load_page_directory.arch.o 	\
		load_page_directory.asm
	$(ASSEMBLE) 										\
		-o $(OBJOUTPATH)/enable_paging.arch.o  			\
		enable_paging.asm
	$(ASSEMBLE)											\
		-o $(OBJOUTPATH)/load_idtr.arch.o				\
		load_idtr.asm
	$(ASSEMBLE)											\
		-o $(OBJOUTPATH)/load_gdtr.arch.o				\
		load_gdtr.asm
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/crtn.crtx.o	   	crtn.asm
	$(ASSEMBLE) 	-o $(OBJOUTPATH)/crti.crtx.o	   	crti.asm
	#Comment: The prefix *.crtx.o is used so that the linkers wildcard
	#	  will not link the file crtx files twice.
	$(COMPILE)	-o $(OBJOUTPATH)/io.arch.o			-c io.c
	$(COMPILE)	-o $(OBJOUTPATH)/gdt.arch.o			-c gdt.c
	$(COMPILE)	-o $(OBJOUTPATH)/idt.arch.o			-c idt.c
	$(COMPILE)	-o $(OBJOUTPATH)/pic.arch.o			-c pic.c
	$(COMPILE)	-o $(OBJOUTPATH)/exceptions.arch.o	-c exceptions.c
	$(COMPILE)	-o $(OBJOUTPATH)/registers.arch.o	-c registers.c
	cd int_routines && make objfiles

clean:
	-rm -r $(wildcard $(OBJOUTPATH)/*.arch.o)
	-rm -r $(wildcard $(OBJOUTPATH)/*.crtx.o)
