FILEPATH=../../bin/objfiles

boot.o: boot.asm
	nasm -felf32 -o $(FILEPATH)/boot.o boot.asm

clean:
	-rm $(FILEPATH)/boot.o
