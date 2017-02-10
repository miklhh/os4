#include <memory/paging.h>
#include <stdio.h>
#include <tty/tty.h>
#include <kernel/gdt.h>

void kernel_main(void)
{
	// Initialize terminal, for being able to write.
	terminal_initialize();

	// Initialize the paging.
	paging_init();

	// Initialize the GDT.
	gdt_init();

	//Test:
	printf("Testing \n");
	printf("%h", 0x123abc);
	printf(" %h %h %h %h\n", 12345678, 0x123abcff, 0, 0xffffffff);

	printf("%u %u %u", 9, 123, 13371337);
}
