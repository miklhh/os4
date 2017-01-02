###Include:
include make.config
GCC = $(CROSSCOMPILER)
SUBDIR = kernel libc drivers
###PATHS:
BUILD = ../build
SYSROOT = $(BUILD)/sysroot
OBJOUTPATH = $(BUILD)/objfiles

###Files:
#Linkfiles, excluding crti.o, crtn.o, crtbegin.o and crtend.o
LINKFILES := $(wildcard $(OBJOUTPATH)/*.kernel.o) \
	     $(wildcard $(OBJOUTPATH)/*.driver.o) 

#CRT-linkfiles:
CRTI_OBJ := $(OBJOUTPATH)/crti.crtx.o
CRTBEGIN_OBJ := $(shell $(GCC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(GCC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ := $(OBJOUTPATH)/crtn.crtx.o

#Link-list (please note the links inside of the crt-objects):
OBJ_LINK_ORDER := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(LINKFILES) -nostdlib \
		    -lk -lgcc $(CRTEND_OBJ) $(CRTN_OBJ)

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11
LINKERFLAGS = -ffreestanding -Wall -Wextra -O2
LINKER = $(GCC) $(LINKERFLAGS) --sysroot=$(SYSROOT) -isystem=/usr/include \
	 -Tlinker.ld

headers:
	cd libc && $(MAKE) headers
	cd drivers && $(MAKE) headers
	cd kernel && $(MAKE) headers 

objfiles:
	cd libc && $(MAKE) objfiles
	cd drivers && $(MAKE) objfiles
	cd kernel && $(MAKE) objfiles

libs:
	cd libc && $(MAKE) libk

os: $(LINKFILES) $(CRTBEGIN_OBJ) $(CRTEND_OBJ) $(CRTI_OBJ) $(CRTN_OBJ)
	$(LINKER)	-o $(BUILD)/os.bin 		$(OBJ_LINK_ORDER)

iso:
	echo "I am not ready for this yet..."

clean:
	-rm -rf $(SYSROOT)/usr		# Remove all the sysroot files.
	-rm -rf $(OBJOUTPATH)/*.o	# Remove all the object files.
	-rm $(BUILD)/os.bin
	-rm $(BUILD)/os.iso

all: headers objfiles libs os
