#include <stdint.h>
#include <stddef.h>
#include <iso646.h>
#include <stdbool.h>

/* The structure for the GDT can be found on:
 * http://wiki.osdev.org/GDT 	[1]
 * Last up-time check: 2017-01-07 */

uint64_t gdt_create_descriptor(uint32_t base, uint32_t limit, uint16_t flags)
{
	uint64_t desc = 0;

	/* Create the higher part of the descriptor. */
	desc |= limit 		& 0x000f0000;
	desc |= (flags << 8)	& 0x00f0ff00;
	desc |= (base >> 16)	& 0x000000ff;
	desc |= base		& 0xff000000;

	/* Shift up the bits to their higher corresponding parts */
	desc <<= 32;

	/* Create the lover part of the descriptor. */
	desc |= limit		& 0x0000ffff;
	desc |= (base << 16)	& 0xffff0000;

	/* Return the descriptor */
	return desc;
}
