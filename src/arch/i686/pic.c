/*
 * Part of OS4, pic.c
 * Author: Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <kstdio.h>
#include <kernel/io.h>

#define PIC1            0x20  // IO-Port of master PIC.
#define PIC2            0xA0  // IO-Port of slave PIC.

#define PIC1_COMMAND    0x20
#define PIC1_DATA       0x21
#define PIC2_COMMAND    0xA0
#define PIC2_DATA       0xA1
#define PIC_EOI         0x20

/* End-of-interrupt routine. */
void pic_send_eoi(uint8_t irq)
{
	/* If the IRQ level is higher than 7 (in other word the slave PIC has sent an
	 * interrupt), than 'end-of-interrupt' must be sent to both PICs. */
	if (irq > 7)
	{
		outb(PIC2_COMMAND, PIC_EOI);
	}
	outb(PIC1_COMMAND, PIC_EOI);

}

void pic_init()
{
	/* Remap the PIC IRQs so they wond clash with the CPU exeption interrupts. */
	outb(0x11, PIC1_COMMAND);	// Initialize cascading mode PIC1.
	outb(0x11, PIC2_COMMAND);	// Initialize cascading mode PIC2.
	outb(0x20, PIC1_DATA);		// Interrupt vector offset PIC1.
	outb(0x28, PIC2_DATA);		// Interrupt vector offset PIC2.
	outb(0x04, PIC1_DATA);		// Tell PIC1 it is a master PIC.
	outb(0x02, PIC2_DATA);		// Tell PIC2 it is a slave PIC.
	outb(0x01, PIC1_DATA);		// Enable 8086-mode (PIC1).
	outb(0x01, PIC2_DATA);		// Enable 8086-mode (PIC2).
	outb(0x00, PIC1_DATA);		// Reset the mask level (PIC1).
	outb(0x00, PIC2_DATA);		// Reset the mask level (PIC2).
	kprintf("PIC initialized!\n");
}
