###Include:
include ../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../build
SYSROOT = $(BUILD)/sysroot
OBJOUTPATH = $(BUILD)/objfiles

###Files:
SOURCES = paging.c

###Build-options:
CFLAGS = -ffreestanding -O2 -Wall -Wextra -g -std=gnu11
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include

###Recipes:
headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr/

objfiles: $(SOURCES)
	$(COMPILE) -o $(OBJOUTPATH)/paging.memory.o 	-c paging.c
	$(COMPILE) -o $(OBJOUTPATH)/memory.memory.o 	-c memory.c

clean:
	@echo "Nothing to clean here"
