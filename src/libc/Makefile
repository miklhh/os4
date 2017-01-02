###Include:
include ../make.config
GCC = $(CROSSCOMPILER)
AR = $(CROSSAR)
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11

###Paths:
SYSROOT = ../../build/sysroot
OBJOUTPATH = ../../build/objfiles
BUILDPATH = ../../build

###Files:
SOURCES := $(wildcard stdlib/*.c) $(wildcard stdio/*.c) $(wildcard string/*.c)
OBJFILES := $(wildcard $(OBJOUTPATH)/*.libk.o)

###Build-options
COMPILE = $(GCC) --sysroot=$(SYSROOT) $(CFLAGS) \
	       -Iinclude -D__is_libk -D__is_libc -isystem=/usr/include

###Recipes:
headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr

libk: $(OBJOUTPATH)/abort.libk.o
	mkdir -p $(SYSROOT)/usr/lib
	$(AR) rcs $(SYSROOT)/usr/lib/libk.a $(OBJFILES)

objfiles: $(SOURCES)
	$(COMPILE) -o $(OBJOUTPATH)/putchar.libk.o 	-c stdio/putchar.c
	$(COMPILE) -o $(OBJOUTPATH)/printf.libk.o 	-c stdio/printf.c
	$(COMPILE) -o $(OBJOUTPATH)/puts.libk.o 	-c stdio/puts.c
	$(COMPILE) -o $(OBJOUTPATH)/memcmp.libk.o 	-c string/memcmp.c
	$(COMPILE) -o $(OBJOUTPATH)/memmove.libk.o 	-c string/memmove.c
	$(COMPILE) -o $(OBJOUTPATH)/strlen.libk.o 	-c string/strlen.c
	$(COMPILE) -o $(OBJOUTPATH)/abort.libk.o 	-c stdlib/abort.c
	$(COMPILE) -o $(OBJOUTPATH)/memset.libk.o 	-c string/memset.c
	$(COMPILE) -o $(OBJOUTPATH)/memcpy.libk.o 	-c string/memcpy.c

clean:
	-rm $(OBJOUTPATH)/*.libk.o
	-rm -rf $(SYSROOT)/usr/include/stdlib.h
	-rm -rf $(SYSROOT)/usr/include/stdio.h
	-rm -rf $(SYSROOT)/usr/include/string.h
