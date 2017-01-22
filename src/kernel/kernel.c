#include <memory/paging.h>
#include <stdio.h>
#include <tty/tty.h>

void kernel_main(void)
{
	// Initialize terminal, for being able to write.
	terminal_initialize();

	//Initialize the paging.
	paging_init();
}
