###Include:
include ../../make.config
GCC = $(CROSSCOMPILER)

###Paths:
BUILD = ../../../build
SYSROOT = $(BUILD)/sysroot
SYSINCLUDE = $(SYSROOT)/usr/include
OBJOUTPATH = $(BUILD)/objfiles

###Files:
HEADERS := include/driver/keyboard.h
SOURCES := keyboard.c

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11
COMPILE = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	  -isystem=/usr/include



###Recipes:
headers: $(HEADERS)
	mkdir -p $(SYSROOT)/usr/include/keyboard
	cp -R include/ $(SYSROOT)/usr/

objfiles: $(SOURCES)
	$(COMPILE)	-o $(OBJOUTPATH)/keyboard.keyboard.driver.o	-c keyboard.c

clean:
	-rm -rf $(OBJOUTPATH)/*.keyboard.driver.o
	-rm -rf $(SYSINCLUDE)/keyboard

