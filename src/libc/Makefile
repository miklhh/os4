##
# NOTE TO SELF:
# I was a newb and could not figure out how to make everything with a make all
# recipie, since libk requires some wildcard files that only could exist when
# objfiles have been build. So the 'all' recipie has been removed (as i said it
# did not function properly). Instead, please (IN THIS ORDER):
#   1. 'make headers'
#   2. 'make objfiles'
#   3. 'make libk'
##

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
SOURCEFILES := $(wildcard stdlib/*.c) $(wildcard stdio/*.c) $(wildcard string/*.c)
LIBKOBJFILES := $(wildcard $(OBJOUTPATH)/*.libk.o)

#Definitions:
DEFS = -D__is_libc -D__is_libk

GCCBUILDOBJ := $(GCC) --sysroot=$(SYSROOT) $(CFLAGS) \
	          -Iinclude -D__is_libk -isystem=/usr/include

#Makes:
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
	
	

libk: $(OBJOUTPATH)/abort.libk.o
	mkdir -p $(SYSROOT)/usr/lib
	$(AR) rcs $(SYSROOT)/usr/lib/libk.a $(LIBKOBJFILES)

headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr
