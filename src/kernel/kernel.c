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
	printf("%h", 0x123abc);
	printf(" %h %h %h %h", 12345678, 0x123abcff, 0, 0xffffffff); 
}
