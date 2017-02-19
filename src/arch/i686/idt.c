/* 
 * Part of OS4, idt.c
 * Author Mikael Henriksson, miklhh.
 */

#include <stdint.h>
#include <kernel/idt.h>
#include <stdio.h>
#include <kernel/panic.h>


/* Variables. */
static uint32_t idtr_location =	0;
static uint32_t idt_location = 0;
static uint16_t idt_size = 0x800;
static uint8_t idt_initialized = 0;

/* Extern functions */
extern void	_set_idtr();
extern void	__idt_default_handler();
extern void	interrupt_test_handler();

uint64_t 	idt_create_entry(uint32_t int_addr, uint16_t selector, uint8_t type_attr);
void 		idt_register_interrupt(uint8_t i, uint32_t entry, uint8_t type_attribute);

/* Initialize the idt. */
void idt_init()
{
	asm volatile("cli");	// Disable interrupts while initializing interrupts.

	idt_location = 0x2000;
	idtr_location = 0x10F0;
	printf("IDT location (in memory): %h \n", idt_location);
	printf("IDT-Descriptor location (in memory): %h\n", idtr_location);
	
	/* Register the interrupts */
	for (uint8_t i = 0; i < 255; i++)
	{
		idt_register_interrupt(
			i, 						// Interrupt vector
			(uint32_t) &__idt_default_handler, 		// Callback func.
			IDT_PRESENT | IDT_32BIT_INTERRUPT_GATE);	// Type Attributes.
	}
	/* Register a test interrupt */
	idt_register_interrupt(
		0x2f,						// Interrupt vector.
		(uint32_t) &interrupt_test_handler,		// Callback function.
		IDT_PRESENT | IDT_32BIT_INTERRUPT_GATE);	// Type attributes.
	
	
	/* Register the IDT */
	*(uint16_t*)idtr_location 	= idt_size - 1;
	*(uint32_t*)(idtr_location + 2) = idt_location;
	printf("IDTR-size = %u, IDT-offset = %h\n", 
		*(uint16_t*)idtr_location,
		*(uint32_t*)(idtr_location + 2));
	
	_set_idtr();
	printf("IDTR set, preforming test interrupt.\n");

	
	asm volatile("sti");		// Enable interrupts again.
	asm volatile("int $0x2f");	// Test an interrupt.
	idt_initialized = 1;

}

/* Set an interrupt (interrupts must be initialized). */
void set_int(uint8_t i, uint32_t callback, uint8_t type_attribute)
{
	if (!idt_initialized)
	{
		panic("Kernel panic! IDT not initialized, cannot add interrupt.\n");
	}
	else
	{
		printf(
		   "Setting new interrupt INT #%u to address: %h, with attribute: %h\n", 
	   	   i,
	   	   callback,
		   type_attribute);
		idt_register_interrupt(i, callback, type_attribute);
	}
}

/* Register an interrupt */
void idt_register_interrupt(uint8_t i, uint32_t callback, uint8_t type_attribute)
{
	*(uint16_t*)(idt_location + 8*i + 0) = (uint16_t)(callback & 0x0000ffff);
	*(uint16_t*)(idt_location + 8*i + 2) = (uint16_t)0x8;
	*(uint8_t*) (idt_location + 8*i + 4) = 0x00;
	*(uint8_t*) (idt_location + 8*i + 5) = type_attribute;
	*(uint16_t*)(idt_location + 8*i + 6) = (uint16_t)((callback & 0xffff0000) >> 16);
}