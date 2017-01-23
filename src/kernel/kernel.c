#include <memory/paging.h>
#include <stdio.h>
#include <tty/tty.h>

void kernel_main(void)
{
	// Initialize terminal, for being able to write.
	terminal_initialize();

	//Initialize the paging.
	paging_init();

	//Test:
	printf("Testing \n");
	printf("1 %h 3", 0x123abc);
}
