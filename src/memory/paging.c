/*
 * Part of OS4, paging2.c
 * Author: Mikael Henriksson, miklhh
 */

#include <memory/memory.h>
#include <stdio.h>
#include <kernel/panic.h>

#define MAX_PAGE_DIRECTORY_ENTRIES 1024

#define PAGE_DIR_PAGE_SIZE_BIT		(1 << 7)
#define PAGE_DIR_ACCESSED_BIT		(1 << 5)
#define PAGE_DIR_CACHE_DISABLE_BIT	(1 << 4)
#define PAGE_DIR_WRITE_THROUGH_BIT	(1 << 3)
#define PAGE_DIR_USER_BIT		(1 << 2)
#define PAGE_DIR_READ_WRITE_BIT		(1 << 1)
#define PAGE_DIR_PRESENT_BIT		(1 << 0)

#define PAGE_TABLE_GLOBAL_BIT		(1 << 8)
#define PAGE_TABLE_DIRTY_BIT		(1 << 6)
#define PAGE_TABLE_ACCESSED_BIT		(1 << 5)
#define PAGE_TABLE_CACHE_DISSABLED_BIT	(1 << 4)
#define PAGE_TABLE_WRITE_THROUGH_BIT	(1 << 3)
#define PAGE_TABLE_USER_BIT		(1 << 2)
#define PAGE_TABLE_READ_WRITE_BIT	(1 << 1)
#define PAGE_TABLE_PRESENT_BIT		(1 << 0)

/* Change these when a page-frame allocater has been added. */
static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t test_page_table[1024] __attribute__((aligned(4096)));

extern void load_page_directory(uint32_t* page_dir);
extern void enable_paging();

void paging_init()
{
	/* Make sure the page-directory has been properly 4k-aligned. */
	if ((uint32_t)page_directory % 0x1000 != 0)
	{
		panic("Kernel panic: Could not 4k-align the Page-Directory.");
	}

	printf("Page-directory start location: %h\n", (uint32_t) page_directory);

	/* Set all the entries in the page directory to non-present. */
	for (uint16_t i = 0; i < 1024; i++)
	{
		page_directory[i] = PAGE_DIR_READ_WRITE_BIT;
	}

	/* Create a page table and */
	for (uint16_t i = 0; i < 1024; i++)
	{
		test_page_table[i] = 	(i * 0x1000) 			| 
					PAGE_TABLE_PRESENT_BIT 		|
					PAGE_TABLE_READ_WRITE_BIT	|
					PAGE_TABLE_USER_BIT;
	}

	/* Add the page table to the page directory. */
	page_directory[0] = 	((uint32_t) test_page_table) 	|
				PAGE_DIR_PRESENT_BIT 		|
				PAGE_DIR_READ_WRITE_BIT		|
				PAGE_DIR_USER_BIT;
	
	/* Enable paging */
	load_page_directory(page_directory);
	enable_paging();
	printf("Paging enabled.\n");

}


