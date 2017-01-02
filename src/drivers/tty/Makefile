###Include:
include ../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(SYSROOT)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Files:
HEADERS := include/tty/tty.h
SOURCES := tty.c

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include



###Recipes:
headers: $(HEADERS)
	mkdir -p $(SYSROOT)/usr/include/tty
	cp -R include/ $(SYSROOT)/usr/

objfiles: $(SOURCES)
	$(COMPILE)	-o $(OBJOUTPATH)/tty.tty.driver.o	-c tty.c

clean:
	-rm -rf $(OBJOUTPATH)/*.tty.driver.o
	-rm -rf $(SYSINCLUDE)/tty

