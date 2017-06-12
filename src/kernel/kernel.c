/*
 * Part of OS4, kernel.c
 * Author Mikael Henriksson, miklhh
 */

#include <memory/paging.h>
#include <memory/memory.h>
#include <stdio.h>
#include <driver/tty.h>
#include <driver/keyboard.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pit.h>
#include <kernel/pic.h>
#include <kernel/exceptions.h>
#include <kernel/task.h>
#include <kernel/ksleep.h>
#include <system/cpuid.h>
#include <string.h>

extern uint32_t __kernel_start;
extern uint32_t __kernel_end;

void kernel_main(void)
{
	// Initialize terminal, for being able to write.
	terminal_initialize();

	// Initialize the GDT.
	gdt_init();
	
	// Initialize the IDT.
	idt_init();

	// Initialize exeptions.
	exceptions_init();
	
	// Initalize the heap data.
	mm_init(&__kernel_end);
	
	// Initialize the paging.
	paging_init();

	// Initialse the PIC
	pic_init();

	// Initialze PIT.
	pit_init();

	// Print kernel start and kernel end.
	printf("Kernel start: %h, and kernel end: %h\n", &__kernel_start, &__kernel_end);

	// Initialize keyboard driver.
	keyboard_init();

    // Test if the CPUID instructions works.
    if (test_cpuid())
    {
        printf("CPUID-instruction available.\n");
        uint32_t a, b, c, d;
        __cpuid(0, a, b, c, d);
        printf("EAX: %h\nEBX: %h\nECX: %h\nEDX: %h\n", a, b, c, d);
        print_vendor_label();
    }
    else
    {
        printf("CPUID-instriction NOT availabe.\n");
    }


	/* ------------------------------------------------ */
	set_kernel_stack();
	switch_to_user_mode();
	/* Testing keyboard. */
	while (1)
	{
		char c = keyboard_get_key();
		if (c)
		{
			putchar(c);
		}
	}
}
