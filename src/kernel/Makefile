COMPILER = ~/opt/cross/bin/i686-elf-gcc
FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
OUTPATH = ../../bin/objfiles

kernel.o: kernel.c
	$(COMPILER) $(FLAGS) -o $(OUTPATH)/kernel.o -c kernel.c

clean:
	-rm $(OUTPATH)/kernel.o
