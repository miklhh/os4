#include <stdio.h>

#if defined (__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int character)
{
#if defined(__is_libk)
	char c = (char) character;
	terminal_write(&c, sizeof(c));
#else
	// TODO: Impement stdio and make system call.
#endif
	return character;
}
