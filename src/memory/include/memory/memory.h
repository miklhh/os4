/*
 * Part of OS4, memory.h
 * Author Mikael Henriksson, miklhh
 */

#ifndef _MEMORY_H
#define _MEMORY_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{ 
	uint8_t  status;
	uint32_t size;
} alloc_t;

/* Allocation functions */
void*	kmalloc(size_t mem);
void 	kfree(void* mem);
void 	mm_init();
void 	mm_print();


#endif
