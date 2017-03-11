/* ------------------------------------------------
 * THIS IS NO LONGER IN USE. SEE NEW paging.c FILE!
 * ------------------------------------------------*/


/*
 * Part of OS4, paging.c
 * Author: Mikael Henriksson, miklhh
 */


/*
 * This file 'paging.c' is heavaly influenced by 'levex' OSDEV source code.
 * LINK: "https://github.com/levex/osdev/"  
 */
#include <stdint.h>
#include <stdio.h>

static uint32_t* 	page_directory = 0;
static uint32_t*	last_page = 0;

void paging_enable()
{
	/* Load the page directory location to Control Register 3. Then set the
	 * paging bit of Control Register 0 */
	uint32_t pagedir_loc = (uint32_t) page_directory;
	asm volatile	("mov %%eax, %%cr3"
			 : // No output
			 :"a"(pagedir_loc)
			);
	asm volatile("mov %cr0, %eax");
	asm volatile("or $0x80000000, %eax");
	asm volatile("mov %eax, %cr0");
}

void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
	uint16_t id = virt >> 22;
	for (uint16_t i = 0; i < 1024; i++)
	{
		last_page[i] = phys | 0x03;
		phys += 4096;
	}
	page_directory[id] = ((uint32_t) last_page) | 3;
	last_page = (uint32_t*) (((uint32_t) last_page) + 4096);
	printf("Mapping %h to %h.\n", virt, phys);
}

void paging_init()
{
	printf("------| Setting up paging. |-----\n");
	page_directory = (uint32_t*)0x400000;
	last_page = (uint32_t*) 0x404000;
	
	for(int i = 0; i < 1024; i++)
	{
		page_directory[i] = 0 | 2;
	}

	paging_map_virtual_to_phys(0, 0);
	paging_map_virtual_to_phys(0x400000, 0x400000);
	paging_enable();
	printf("------| Paging initialized.|-----\n");
}
