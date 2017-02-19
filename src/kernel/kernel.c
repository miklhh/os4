#include <memory/paging.h>
#include <stdio.h>
#include <tty/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pit.h>
#include <kernel/pic.h>
#include <system/sleep.h>

void kernel_main(void)
{
	// Initialize terminal, for being able to write.
	terminal_initialize();

	// Initialize the GDT.
	gdt_init();
	
	// Initialize the IDT.
	idt_init();
	
	// Initialize the paging.
	paging_init();

	// Initialse the PIC
	pic_init();

	// Initialze PIT.
	pit_init();
	//asm volatile ("int $0x20");

	while(1) 
	{
		static uint32_t i = 0;
		sleep(1000);
		printf("Done sleeping, going back to sleep: %u \n", i);
		i++;
	}

}
