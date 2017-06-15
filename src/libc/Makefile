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
SOURCES = $(wildcard stdlib/*.c) $(wildcard stdio/*.c) $(wildcard string/*.c)
LIBK_OBJFILES = $(wildcard $(OBJOUTPATH)/*.libk.o)
LIBC_OBJFILES = $(wildcard $(OBJOUTPATH)/*.libc.o)

###Build-options
COMPILE = $(GCC) --sysroot=$(SYSROOT) $(CFLAGS) \
	       -Iinclude -D__is_libk -D__is_libc -isystem=/usr/include

###Recipes:
headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr

libs:
	mkdir -p $(SYSROOT)/usr/lib
	$(AR) rcs $(SYSROOT)/usr/lib/libk.a $(LIBK_OBJFILES)
	$(AR) rcs $(SYSROOT)/usr/lib/libc.a $(LIBC_OBJFILES)

objfiles: $(SOURCES)
	$(COMPILE) -o $(OBJOUTPATH)/putchar.libc.o 	-c stdio/putchar.c
	$(COMPILE) -o $(OBJOUTPATH)/printf.libc.o 	-c stdio/printf.c
	$(COMPILE) -o $(OBJOUTPATH)/puts.libc.o 	-c stdio/puts.c
	$(COMPILE) -o $(OBJOUTPATH)/memcmp.libc.o 	-c string/memcmp.c
	$(COMPILE) -o $(OBJOUTPATH)/memmove.libc.o 	-c string/memmove.c
	$(COMPILE) -o $(OBJOUTPATH)/strlen.libc.o 	-c string/strlen.c
	$(COMPILE) -o $(OBJOUTPATH)/abort.libc.o 	-c stdlib/abort.c
	$(COMPILE) -o $(OBJOUTPATH)/memset.libc.o 	-c string/memset.c
	$(COMPILE) -o $(OBJOUTPATH)/memcpy.libc.o 	-c string/memcpy.c
	$(COMPILE) -o $(OBJOUTPATH)/kprintf.libk.o 	-c kstdio/kprintf.c
	$(COMPILE) -o $(OBJOUTPATH)/kputchar.libk.o	-c kstdio/kputchar.c
	$(COMPILE) -o $(OBJOUTPATH)/kputs.libk.o 	-c kstdio/kputs.c

clean:
	-rm $(OBJOUTPATH)/*.libk.o
	-rm -rf $(SYSROOT)/usr/include/stdlib.h
	-rm -rf $(SYSROOT)/usr/include/stdio.h
	-rm -rf $(SYSROOT)/usr/include/string.h
