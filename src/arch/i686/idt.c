/* 
 * Part of OS4, idt.c
 * Author Mikael Henriksson, miklhh.
 */

#include <stdint.h>
#include <kernel/idt.h>
#include <kstdio.h>
#include <kernel/panic.h>

/* Extern functions. */
extern void	load_idtr(uint32_t idtd_location);
extern void	__idt_default_handler();
extern void	interrupt_test_handler();


/* IDT fields. */
uint8_t         idt_initialized;
static idtd_t   idtd;
static idt_t    idt;



/* Register an interrupt */
void idt_register_interrupt(uint8_t i, uint32_t callback, uint8_t type_attribute)
{
    uint64_t descriptor = 0x00;
    descriptor |= (uint64_t) callback & 0x0000ffff;     // Callback lower addr.
    descriptor |= (uint64_t) 0x08 << 16;                // Kernel code selector.
    descriptor |= (uint64_t) type_attribute << 40;      // Descriptor type atr.
    descriptor |= (uint64_t) (callback >> 16) << 48;    // Callback higher addr.
    idt[i] = descriptor;
}


/* Initialize the idt. */
void idt_init()
{
    interrupt_dissable();

    idt_initialized = 0;

	kprintf("IDT location (in memory): %x \n", (uint32_t) &idt);
	kprintf("IDT-Descriptor location (in memory): %x\n", (uint32_t) &idtd);
	
	/* Register the interrupts */
	for (uint8_t i = 0; i < 255; i++)
	{
		idt_register_interrupt(
			i,                                          // Interrupt vector
			(uint32_t) &__idt_default_handler,          // Callback func.
			IDT_PRESENT | IDT_32BIT_INTERRUPT_GATE);    // Type Attributes.
	}

	/* Register a test interrupt */
	idt_register_interrupt(
		0x2f,                                       // Interrupt vector.
		(uint32_t) &interrupt_test_handler,         // Callback function.
		IDT_PRESENT | IDT_32BIT_INTERRUPT_GATE);    // Type attributes.
	
	/* Register the IDT */
    idtd.size = IDT_ENTRIES * 8 - 1;        // Entries * bytes/entrie - 1.
    idtd.location = (uint32_t) idt;
	kprintf(
        "IDT-size = %u, IDT-location = %x, IDTD-locaion = %x\n", 
        idtd.size,
        idtd.location,
        (uint32_t) &idtd);        
	load_idtr((uint32_t) &idtd);

    /* Preform test interrupt. */
	kprintf("IDTR set, preforming test interrupt.\n");
	interrupt_enable();
    asm volatile("int $0x2f");
    interrupt_dissable();

    /* The test interrupt will, if it succedded have changed the value of
     * the idt_initialized variable. */
    if (idt_initialized != 0xAB)
    {
        kprintf("Testhandler magic number: %x\n", 0xAB);
        kprintf("Testhandler acctual return value: %x\n", idt_initialized);
        panic("Kernel panic: Interrupt test call failed.");
    } 
}


/* Set an interrupt (interrupts must first be initialized). */
void set_int(uint8_t i, uint32_t callback, uint8_t type_attribute)
{
	if (!idt_initialized)
	{
		panic("Kernel panic! IDT not initialized, cannot add interrupt.\n");
	}
	else
	{
		kprintf(
		   "Adding new interrupt INT #%u to address: %x, with attribute: %x\n", 
	   	   i,
	   	   callback,
		   type_attribute);
		idt_register_interrupt(i, callback, type_attribute);
	}
}

