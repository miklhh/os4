#Flags:
CFLAGS = -ffreestanding -Wall -Wextra -O2 -g -std=gnu11
ASMFLAGS = -Wall -O2 -g -std=gnu11 -felf32
LINKERFLAGS = -O2 -g -ffreestanding -Wall -Wextra

#Paths:
OBJOUTPATH = ../../build/objfiles
SYSROOT = ../../build/sysroot
BUILDPATH = ../../build

#Compiler
include ../make.config
GCC = $(CROSSCOMPILER)

#Compiler with options.
COMPILER = $(GCC) $(CFLAGS) -D__is_kernel -Iinclude --sysroot=$(SYSROOT) \
	      -isystem=/usr/include
ASSEMBLER = nasm $(ASMFLAGS) -D__is_kernel -Iinclude

LINKER = $(GCC) --sysroot=$(SYSROOT) -isystem=/usr/include -Tarch/i386/linker.ld \
	    $(LINKERFLAGS)

#	 


#Files:
#Linkfiles, excluding crti.o, crtn.o, crtbegin.o and crtend.o
LINKFILES := $(OBJOUTPATH)/boot.kernel.o 	$(OBJOUTPATH)/tty.kernel.o \
	     $(OBJOUTPATH)/kernel.kernel.o

CRTI_OBJ := $(OBJOUTPATH)/crti.kernel.o
CRTBEGIN_OBJ := $(shell $(GCC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(GCC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ := $(OBJOUTPATH)/crtn.kernel.o

OBJ_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(LINKFILES) -nostdlib \
		    -lk -lgcc $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJ := $(CRTI_OBJ) $(LINKFILES) $(CRTN_OBJ)

headers:
	mkdir -p $(SYSROOT)/usr/include
	cp -r include/ $(SYSROOT)/usr/

objfiles:
	$(COMPILER) 	-o $(OBJOUTPATH)/kernel.kernel.o 	-MD -c kernel/kernel.c
	$(COMPILER) 	-o $(OBJOUTPATH)/tty.kernel.o 		-MD -c arch/i386/tty.c
	$(ASSEMBLER) 	-o $(OBJOUTPATH)/boot.kernel.o		       arch/i386/boot.asm
	$(ASSEMBLER) 	-o $(OBJOUTPATH)/crtn.kernel.o		       arch/i386/crtn.asm
	$(ASSEMBLER) 	-o $(OBJOUTPATH)/crti.kernel.o		       arch/i386/crti.asm	


kernel: $(LINKFILES) $(CRTBEGIN_OBJ) $(CRTEND_OBJ)
	$(LINKER)	-o $(BUILDPATH)/os.bin $(OBJ_LINK_LIST)

clean:
	-rm -r $(INTERNAL_OBJ)
	-rm -r $(SYSROOT)/usr
