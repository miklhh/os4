#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

/* TTY functions */
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_scroll();

/* Typedef for an entry in the tty. */
// Move this header to the local source path, no need to show this here.
typedef struct
{
	size_t x;
	size_t y;
} ttyposition;


#endif
