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
#include <system/sleep.h>
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
	
	// Initialize the paging.
	paging_init();

	// Initialse the PIC
	pic_init();

	// Initialze PIT.
	pit_init();

	// Test the labels.
	printf("Kernel start: %h, and kernel end: %h\n", &__kernel_start, &__kernel_end);

	// Initalize the heap data.
	mm_init(&__kernel_end);

	// Initialize keyboard driver.
	keyboard_init();


	/* ------------------------------------------------ */

	/* Testing keyboard. */
	while (1)
	{
		char c = keyboard_get_key();
		if (c)
		{
			putchar(c);
		}
		asm volatile ("hlt");
	}
}
