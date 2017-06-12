/*
 * Part of OS4, memory.c
 * Author Mikael Henriksson, miklhh
 */

#include <string.h>
#include <stdint.h>
#include <memory/memory.h>
#include <stdio.h>
#include <kernel/panic.h>

/* MACROS */
#define MAX_PAGE_ALIGNED_ALLOCS 32

/* Variables */
static uint32_t last_alloc 	= 0;
static uint32_t heap_end 	= 0;
static uint32_t heap_start 	= 0;
static uint32_t pheap_start 	= 0;
static uint32_t pheap_end	= 0;
static uint8_t* pheap_desc	= 0;
static uint32_t memory_used	= 0;

/* Function declaring */
void  mm_init(uint32_t);
void* kmalloc(size_t size);
void  free(void* mem);

/* Memory management init function. */
void mm_init(uint32_t kernel_end)
{
	/* Setup the 'heap' variables */
	last_alloc 	= kernel_end + 0x1000;
	heap_start 	= last_alloc;
	pheap_end 	= 0x400000;
	pheap_start	= pheap_end - (MAX_PAGE_ALIGNED_ALLOCS * 4096);
	heap_end	= pheap_end;
	
	/* Set the entire heap data to 0 (initialize the heap) */
	memset((char*) heap_start, 0, heap_end - heap_start);

	/* Setup the Page-heap descriptor. */
	pheap_desc = (uint8_t*) kmalloc(MAX_PAGE_ALIGNED_ALLOCS);

	/* Done, print and return. */
	printf("Kernel heap memory setup. Kernel heap start: %h\n", heap_start);
}

/* Kernel malloc, page alligned. There is, for the record no way of
 * freeing this kind of memory. Please don not try to use the standard
 * kfree to free this memory.*/
void* kmalloc_p(size_t size, uint32_t* phys)
{
	/* This is a real waste. Redo later. Create a page aligned allocation. */
	void* address = kmalloc(size + 0x1000);
	address = (void*) ((uint32_t) address & 0xFFFFF000);
	address = (void*) ((uint32_t) address + 0x1000);

	*phys = *(uint32_t*)address;
	return address;
}

/* Used for debung, print kernel heap information. */
void mm_print()
{
	printf("Heap-memory used: %u bytes\n", memory_used);
	printf("Heap-memory free: %u bytes\n", heap_end - heap_start - memory_used);
	printf("Heap size %u bytes\n", heap_end - heap_start);
	printf("Heap start: %h\n", heap_start);
	printf("Heap end: %h\n", heap_end);
}

/* Vanilla kmalloc. */
void* kmalloc(size_t size)
{
	if (size == 0) return (void*) 0;
	
	/* Loop thorughout the blocks and find the next free block with enougth space. */
	uint8_t* mem = (uint8_t*) heap_start;
	while((uint32_t) mem < last_alloc)
	{
		alloc_t *a = (alloc_t*) mem;	// Memory pointer.	
		if (!a->size) goto nalloc;	// If size = 0, memory is full.

		/* If the alloc is taken (status == 1), add it's size of to search-
		 * pointer and keep continue with next iteration. */
		if (a->status)
		{
			mem += a->size;		  // Add the size wher next alloc_t is.
			mem += sizeof(alloc_t);	  // Add the size of an alloc_t.
			mem += 4;		  // Add another four bytes.
			continue;
		}

		/* If the space is bigger than or of the same size as the new memory
		 * allocation, take it and return a pointer to it. */
		if (a->size >= size)
		{
			a->status = 1;		// Set the alloc_t status to 1 (taken).
			a->size   = size;	// Set the alloc_t size to 'size'.
			
			/* Restore the memory to zeros, set the new total used heap
			 * memory, and return a pointer to the newly allocated memory. */
			memset(mem + sizeof(alloc_t), 0, size);
			memory_used += size + sizeof(alloc_t);
			return (void *) (mem + sizeof(alloc_t));
		}

		/* If the place isn't allocated, but to small for the current needed
		 * size, add the size of the place to the memory pointer and continue. */
		mem += a->size;
		mem += sizeof(alloc_t);
		mem += 4;
	}

	/* The latest allocation was smaller then the current requested memory size. */
	nalloc:			// New alloc.
	if (last_alloc + size + sizeof(alloc_t) >= heap_end)
	{
		panic("Kernel panic, cannot allocate more memory.");
	}
	
	alloc_t* alloc  = (alloc_t*)last_alloc;	// Allocate memory by the last alloc.
	alloc->status 	= 1;			// Mark it as active.
	alloc->size 	= size;			// Set it's size.
	last_alloc += size;			// Move the 'last_alloc'.
	last_alloc += sizeof(alloc_t);		// Move the 'last_alloc'.
	last_alloc += 4;			// Move the 'last_alloc'.
	
	memory_used += size + sizeof(alloc_t) + 4;
	memset((char*) ((uint32_t) alloc + sizeof(alloc_t)), 0, size);
	return (void*) ((uint32_t) alloc + sizeof(alloc_t));
}

/* Used to return page aligned memory. */
/*
void kfree_p(void *page_mem)
{
	
}
*/

void kfree(void *mem)
{
	alloc_t* alloc = (alloc_t*) (mem - sizeof(alloc_t));
	memory_used -= alloc->size + sizeof(alloc_t);
	alloc->status = 0;
}


