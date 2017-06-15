/*
 * Part of OS4, pit.c
 * Author: Mikael Henriksson, miklhh
 */

#include <kernel/pit.h>
#include <kernel/io.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <stdint.h>
#include <kstdio.h>

/* Wrapper for the pit_irq routine */
extern void pit_irq_wrapper();

/* Global tick variable */
volatile uint32_t __sys_tick = 0;

void pit_irq()
{
	__sys_tick++;
	pic_send_eoi(0);
}

static inline void set_pit_timer_phase(uint32_t freq_hz)
{
	uint16_t divisor = (uint16_t) (1193180 / freq_hz);
	outb(0x36, 0x43);           // LSB then MSB - mode
	outb(divisor & 0xFF, 0x40); // LSB
	outb(divisor >> 8, 0x40);   // MSB
}

static void pit_start_counter (uint32_t freq, uint8_t counter, uint8_t mode)
{
	/* Frequency will not count at all */
	if (freq == 0)
	{
		return;
	}
		
	/* Send operational command words. */
	uint8_t ocw = 0;
	ocw = (ocw & ~PIT_OCW_MASK_MODE)    | mode;
	ocw = (ocw & ~PIT_OCW_MASK_RL) 	    | PIT_OCW_RL_DATA;
	ocw = (ocw & ~PIT_OCW_MASK_COUNTER) | counter;
	outb(ocw, 0x43);

	/* Set the frequency */
	set_pit_timer_phase(freq);

}

void pit_init()
{
	/* Please note that the pit_irq_wrapper function is set as the callback function.
	 * the wrapperfunction will than call the pit_irq function. */
	set_int(
	     0x20,                                      // Interrupt vector.
	     (uint32_t) &pit_irq_wrapper,               // Callback function.
	     IDT_32BIT_INTERRUPT_GATE | IDT_PRESENT);   // Type-attributes.
	kprintf("Interruptvector #32 (IRQ #0) set as PIT_IRQ.\n");
	pit_start_counter(PIT_TICK_RATE, PIT_OCW_COUNTER_0, PIT_OCW_MODE_SQUAREWAVEGEN);

}
