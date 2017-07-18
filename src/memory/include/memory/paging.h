/* 
 * Part of OS4, paging.h
 * Author: Mikael Henriksson, miklhh
 */

#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>

/* Structure for a page. (page table entry) */
typedef struct page{
	uint32_t present    : 1;	// Present bit.
	uint32_t rw         : 1;	// Read write bit.
	uint32_t user       : 1;	// User bit.
	uint32_t accessed   : 1;	// Accessed bit.
	uint32_t dirty      : 1;	// Dirty bit.
	uint32_t unused     : 7;
	uint32_t frame      : 20;	// Frame address (shifted 12 bit right).
} page_t;


/* Structure for page table */
typedef struct page_table{
	page_t pages[1024];
} page_table_t;


/* Structure for page directory. */
typedef struct page_directory{
	page_table_t*  tables[1024];
	uint32_t 	   tables_physical[1024];
	uint32_t	   pyhiscal_address;
} page_directory_t;

/* Functions. */
void paging_init();
extern void load_page_directory(uintptr_t page_dir);

#endif
