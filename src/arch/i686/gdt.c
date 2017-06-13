/*
 * Part of OS4, gdt.c
 * Author: Mikael Henriksson, miklhh
 */

#include <stdint.h>
#include <stddef.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdio.h>
#include <kernel/gdt.h>
#include "tss_entry_struct.h"
#include <string.h>

/* The structure for the GDT can be found on:
 * http://wiki.osdev.org/GDT 	[1]
 * Last up-time check: 2017-01-07 */

#define FLAG_PRESENT            (1 << 7)
#define FLAG_FOURTH_BIT         (1 << 4)
#define FLAG_VALID_SECTOR       (FLAG_PRESENT | FLAG_FOURTH_BIT)
#define FLAG_PROTECTED_MODE     (1 << 14)
#define FLAG_REAL_MODE          (0 << 14)
#define FLAG_EXECUTABLE         (1 << 3)
#define FLAG_NOT_EXECUTABLE     (0 << 3)
#define FLAG_READWRITEBIT       (1 << 1)
#define FLAG_ACCESSBIT		    (1 << 0)

#define RING_LEVEL(x)		    (x << 5)
#define FLAG_GRANULARITY_BYTE 	(0 << 15)
#define FLAG_GRANULARITY_PAGE 	(1 << 15)
#define FLAG_READ		        (0 << 1)
#define FLAG_WRITE		        (1 << 1)



#define TYPE_SEG ((1 << 4) | FLAG_PRESENT)
#define TYPE_TSS ((1 << 0) | FLAG_PRESENT)

extern void _set_gdtr();
extern void _reload_segments();
extern uint32_t interrupt_stack_top;

static uint32_t gdt_pointer = 0;
static uint32_t gdt_size = 0;
static uint32_t gdtr_location = 0;
static tss_entry_t tss_entry;


void gdt_init()
{
	/* Initialize the GDT position in memory (location is hardcoded, see bootfile). */
	gdt_pointer = 	0x806;
	gdtr_location =	0x800;
	printf("GDT-Start location (in memory): %h\n", gdt_pointer);
	printf("GDT-Descriptor location (in memory): %h\n", gdtr_location);

	/* -------------------------------------------------------------------------------/
	 * ------------------------------- GDT Content -----------------------------------/
	 * ------------------------------------------------------------------------------*/
	/* Null descriptor. Entry 0. Offset 0x00 */
	gdt_add_descriptor(0, 0);

	/* Kernel code segment. Entry 1. Offset 0x08. */
	gdt_add_descriptor(
		1, 
		gdt_create_descriptor(
			0x00000000,     // Descriptor start address.
			0xFFFFF,        // Descripted size (in pages (4096 bytes)).
			FLAG_VALID_SECTOR | FLAG_PROTECTED_MODE | RING_LEVEL(0) | 
			FLAG_EXECUTABLE | FLAG_READWRITEBIT | FLAG_GRANULARITY_PAGE));

	/* Kernel data segment. Entry 2. Offset 0x10. */
	gdt_add_descriptor(
		2,
		gdt_create_descriptor(
			0x00000000,     // Descriptor start address.
			0xFFFFF,        // Descripted size (in pages (4096 bytes)).
			FLAG_VALID_SECTOR | FLAG_PROTECTED_MODE | RING_LEVEL(0) |
			FLAG_NOT_EXECUTABLE | FLAG_READWRITEBIT | FLAG_GRANULARITY_PAGE));

	/* User code segment. Entry 3. Offset 0x18. */
	gdt_add_descriptor(
		3,
		gdt_create_descriptor(
			0x00000000,     // Descriptor start address.
			0xFFFFF,        // Descripted size (in pages (4096 bytes)).
			FLAG_VALID_SECTOR | FLAG_PROTECTED_MODE | RING_LEVEL(3) |
			FLAG_EXECUTABLE | FLAG_READWRITEBIT | FLAG_GRANULARITY_PAGE));

	/* User data segment. Entry 4. Offset 0x20. */
	gdt_add_descriptor(
		4,
		gdt_create_descriptor(
			0x00000000,     // Descriptor start address.
			0xFFFFF,        // Descripted size (in pages (4096 bytes)).
			FLAG_VALID_SECTOR | FLAG_PROTECTED_MODE | RING_LEVEL(3) |
			FLAG_NOT_EXECUTABLE | FLAG_READWRITEBIT | FLAG_GRANULARITY_PAGE));

	/* TSS entry. */
	gdt_add_descriptor(
		5,
		gdt_create_descriptor(
			(uint32_t) &tss_entry,
			sizeof(tss_entry),
			FLAG_PRESENT | FLAG_EXECUTABLE | FLAG_ACCESSBIT |
			FLAG_GRANULARITY_PAGE));
			
	
	/* Give the gdt to the CPU. */
	*(uint16_t*)gdtr_location = (gdt_size - 1) & 0x0000FFFF;
	*(uint32_t*)(gdtr_location + 2) = gdt_pointer;

	/* Set the global descriptortable register and reload the segments. */
	_set_gdtr();
	printf("GDTR was set. GDTR-size = %h, GDTR-memory-offset = %h\n",
		*(uint16_t*)gdtr_location + 1,
		*(uint32_t*)(gdtr_location + 2));
	_reload_segments();
	printf("Segments reloaded.\n");

	/* Setup the TSS-entry and load it. */
	memset(&tss_entry, 0, sizeof(tss_entry));   // Clear the entry.
	tss_entry.ss0	= 0x10;     // Use kernel data entry.
	tss_entry.esp0	= 0x00;     // Edited with 'set_kernel_stack'.
	tss_entry.cs	= 0x0b;
	tss_entry.ss	= 0x13;
	tss_entry.ds	= 0x13;
	tss_entry.fs	= 0x13;
	tss_entry.gs	= 0x13;

	/* 'Load task register'. */
	asm volatile(	
            "movw   $0x2b, %%ax \n"
			"ltr    %%ax        \n" 
			: 
            : 
            : "%ax");
	
	/* The descriptor has been set up and is running. */
	printf("New GDT has been loaded by the CPU.\n");
	printf("-------\n");
}

void set_kernel_stack(uint32_t stack)
{
	tss_entry.esp0 = stack;
}

int gdt_add_descriptor(uint8_t id, uint64_t desc)
{
	uint32_t loc = gdt_pointer + sizeof(uint64_t) * id;
	*(uint64_t*) loc = desc;
	printf("Added entry %u = %h << 32 | %h\n", 
		id, 
		(uint32_t) ((*(uint64_t*)loc) >> 32),
		(uint32_t) (*(uint64_t*)loc));
	gdt_size += sizeof(desc);
	return 0;
}


uint64_t gdt_create_descriptor(uint32_t base, uint32_t limit, uint16_t flags)
{
	uint64_t desc = 0;

	/* Create the higher part of the descriptor. */
	desc |= limit           & 0x000f0000;
	desc |= (flags << 8)    & 0x00f0ff00;
	desc |= (base >> 16)    & 0x000000ff;
	desc |= base            & 0xff000000;

	/* Shift up the bits to their higher corresponding parts */
	desc <<= 32;

	/* Create the lover part of the descriptor. */
	desc |= limit           & 0x0000ffff;
	desc |= (base << 16)    & 0xffff0000;

	/* Return the descriptor */
	return desc;
}

