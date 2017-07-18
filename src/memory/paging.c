/*
 * Part of OS4, paging.c
 * Author: Mikael Henriksson, miklhh
 */

#include <memory/memory.h>
#include <memory/paging.h>
#include <kstdio.h>
#include <kernel/panic.h>

#define MAX_PAGE_DIRECTORIES 1024

#define PAGE_DIR_PAGE_SIZE_BIT          (1 << 7)
#define PAGE_DIR_ACCESSED_BIT           (1 << 5)
#define PAGE_DIR_CACHE_DISABLE_BIT      (1 << 4)
#define PAGE_DIR_WRITE_THROUGH_BIT      (1 << 3)
#define PAGE_DIR_USER_BIT               (1 << 2)
#define PAGE_DIR_READ_WRITE_BIT         (1 << 1)
#define PAGE_DIR_PRESENT_BIT            (1 << 0)

#define PAGE_TABLE_GLOBAL_BIT           (1 << 8)
#define PAGE_TABLE_DIRTY_BIT            (1 << 6)
#define PAGE_TABLE_ACCESSED_BIT         (1 << 5)
#define PAGE_TABLE_CACHE_DISSABLED_BIT  (1 << 4)
#define PAGE_TABLE_WRITE_THROUGH_BIT    (1 << 3)
#define PAGE_TABLE_USER_BIT             (1 << 2)
#define PAGE_TABLE_READ_WRITE_BIT       (1 << 1)
#define PAGE_TABLE_PRESENT_BIT          (1 << 0)

/* Change these when a page-frame allocater has been added. */
uint32_t kernel_page_directory[1024] __attribute__((aligned(4096)));
static uint32_t kernel_page_table[1024] __attribute__((aligned(4096)));

extern void enable_paging();

void paging_init()
{
	/* Make sure the page-directory has been properly 4k-aligned. */
	if ((uint32_t)kernel_page_directory % 0x1000 != 0)
	{
		panic("Kernel panic: Could not 4k-align the Page-Directory.");
	}

	kprintf(
        "Kernel page-directory start location: %x\n", 
        (uint32_t) kernel_page_directory);

	/* Set all the entries in the page directory to non-present. */
	for (uint16_t i = 0; i < 1024; i++)
	{
		kernel_page_directory[i] = PAGE_DIR_READ_WRITE_BIT;
	}

	/* Page the first four mebibytes of memory the their corresponding address. */
	for (uint32_t i = 0; i < 1024; i++)
	{
		kernel_page_table[i] = 	
                    (i * 0x1000)                    | 
                    PAGE_TABLE_PRESENT_BIT          |
                    PAGE_TABLE_READ_WRITE_BIT       |
                    PAGE_TABLE_USER_BIT;
	}

	/* Add the page table to the page directory. */
	kernel_page_directory[0] = 	
                ((uint32_t) kernel_page_table) |
				PAGE_DIR_PRESENT_BIT                |
				PAGE_DIR_READ_WRITE_BIT             |
				PAGE_DIR_USER_BIT;
	
	/* Enable paging */
	load_page_directory((uintptr_t) kernel_page_directory);
	enable_paging();
	kprintf("Paging enabled.\n");
}
