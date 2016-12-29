LINKER = ~/opt/cross/bin/i686-elf-gcc
OBJFILES = objfiles/kernel.o objfiles/boot.o
FLAGS = -ffreestanding -O2 -nostdlib -lgcc -Tlinker.ld

os.bin: $(OBJFILES)
	$(LINKER) $(FLAGS) -o os.bin $(OBJFILES)

os.iso: os.bin
	mv iso.bin isodir/boot
	grub-mkrescue -o os.iso isodir
