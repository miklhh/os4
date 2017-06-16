/*
 * Part of OS4, exceptions.c
 * Author Mikael Henriksson, miklhh
 */

#include <kernel/exceptions.h>
#include <kernel/idt.h>
#include <kstdio.h>

extern void general_protection_fault_wrapper();
extern void divide_by_zero_error_wrapper();
extern void page_fault_wrapper();

#define EXCEPTION_FLAGS (IDT_32BIT_INTERRUPT_GATE | IDT_PRESENT)

void exceptions_init()
{
	/* Vector 0x00, 'Divide-by-zero Error' */
	set_int(
		0x00,
		(uint32_t) &divide_by_zero_error_wrapper,
		EXCEPTION_FLAGS);

	/* Vector 0x0d, 'General Protection Fault'. */
	set_int(
		0x0d, 
		(uint32_t) &general_protection_fault_wrapper,
		EXCEPTION_FLAGS);

	/* Vector 0x0e, 'Page Fault'. */
	set_int(
		0x0e,
		(uint32_t) &page_fault_wrapper,
		EXCEPTION_FLAGS);
}

// Divide by zero exception.
void divide_by_zero_error()
{
	kprintf("ERROR, DIVEDE-BY-ZERO ERROR, HALTING.");
	asm volatile("cli; hlt;");
}

// General protection fault.
void general_protection_fault()
{
	uint32_t error_code = 0;
	kprintf("ERROR, GENERAL PROTECTION FAULT, HALTING. ERROR CODE: ");
	asm volatile ("			\
		movl	(%%esp), %%eax;	\
		movl	%%eax, %0;"
		:"=r"(error_code)       // Output.
		:                       // Input.
		:"%eax");               // Clobbered registers.
	kprintf("%h", error_code);

	asm volatile("cli; hlt;");
}

// Page fault.
void page_fault()
{
	kprintf("ERROR, PAGE FAULT, HALTING.");
	asm volatile("cli; hlt");
}
