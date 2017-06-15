###Include:
include make.config
GCC = $(CROSSCOMPILER)
SUBDIR = kernel libc drivers

###PATHS:
BUILDPATH = ../build
SYSROOT = $(BUILDPATH)/sysroot
OBJOUTPATH = $(BUILDPATH)/objfiles

###Files:
#Linkfiles, excluding crti.o, crtn.o, crtbegin.o and crtend.o
LINKFILES =										\
		$(wildcard $(OBJOUTPATH)/*.kernel.o)	\
	    $(wildcard $(OBJOUTPATH)/*.driver.o)	\
	    $(wildcard $(OBJOUTPATH)/*.arch.o)		\
	    $(wildcard $(OBJOUTPATH)/*.memory.o)	\
		$(wildcard $(OBJOUTPATH)/*.syscall.o)

#CRT-linkfiles:
CRTI_OBJ = $(OBJOUTPATH)/crti.crtx.o
CRTBEGIN_OBJ = $(shell $(GCC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ = $(shell $(GCC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ = $(OBJOUTPATH)/crtn.crtx.o

#Link-list (please note the links inside of the crt-objects):
OBJ_LINK_ORDER = $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(LINKFILES) -nostdlib \
		    -lk -lc -lgcc $(CRTEND_OBJ) $(CRTN_OBJ)

###Build-options:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11
LINKERFLAGS = -ffreestanding -Wall -Wextra -O2
LINKER = $(GCC) $(LINKERFLAGS) --sysroot=$(SYSROOT) -isystem=/usr/include \
	 -Tlinker.ld

headers:
	@echo "Making Headers"
	cd libc && $(MAKE) headers
	cd drivers && $(MAKE) headers
	cd kernel && $(MAKE) headers 
	cd arch && $(MAKE) headers
	cd memory && $(MAKE) headers

objfiles:
	-mkdir -p $(BUILDPATH)/objfiles
	cd libc && $(MAKE) objfiles
	cd drivers && $(MAKE) objfiles
	cd kernel && $(MAKE) objfiles
	cd arch && $(MAKE) objfiles
	cd memory && $(MAKE) objfiles

libs:
	cd libc && $(MAKE) libs

os: $(LINKFILES) $(CRTBEGIN_OBJ) $(CRTEND_OBJ) $(CRTI_OBJ) $(CRTN_OBJ)
	$(LINKER)	-o $(BUILDPATH)/sysroot/boot/os.bin 		$(OBJ_LINK_ORDER)

iso:
	@echo "I am not ready for this yet..."

clean:
	-rm -rf $(SYSROOT)/usr		# Remove all the sysroot files.
	-rm -rf $(OBJOUTPATH)/*.o	# Remove all the object files.
	-rm $(BUILDPATH)/sysroot/boot/os.bin

