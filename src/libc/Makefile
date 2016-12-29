#Compiler stuff:
include ../make.config
GCC = $(CROSSCOMPILER)
AR = $(CROSSAR)
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11

#PATHS:
SYSROOT = ../../build/sysroot
OBJOUTPATH = ../../build/objfiles
BUILDPATH = ../../build

#Files:
LIBKOBJFILES := $(wildcard $(OBJOUTPATH)/*.libk.o)
SOURCEFILES := $(wildcard stdlib/*.c) $(wildcard stdio/*.c) $(wildcard string/*.c)

#Definitions:
DEFS = -D__is_libc -D__is_libk

GCCBUILDOBJ := $(GCC) --sysroot=$(SYSROOT) $(CFLAGS) -Iinclude

#Makes:
all: objfiles libk headers

clean:
	-rm $(OBJOUTPATH)/*.libk.o
	-rm -rf $(SYSROOT)/usr

objfiles: $(SOURCEFILES)
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/putchar.libk.o 	-c stdio/putchar.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/printf.libk.o 	-c stdio/printf.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/puts.libk.o 	-c stdio/puts.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/memcmp.libk.o 	-c string/memcmp.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/memmove.libk.o 	-c string/memmove.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/strlen.libk.o 	-c string/strlen.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/abort.libk.o 	-c stdlib/abort.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/memset.libk.o 	-c string/memset.c
	$(GCCBUILDOBJ) -o $(OBJOUTPATH)/memcpy.libk.o 	-c string/memcpy.c
	
	
libk: $(LIBKOBJFILES)
	mkdir -p $(SYSROOT)/usr/lib
	$(AR) rcs $(SYSROOT)/usr/lib/libk.a $(LIBKOBJFILES)

headers:
	cp -r include/ $(SYSROOT)/usr/include
