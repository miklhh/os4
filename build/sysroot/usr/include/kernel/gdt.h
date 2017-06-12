/*
 * Part of OS4, gdt.h
 * Author Mikael Henriksson, miklhh
 */

#ifndef _gdt_h
#define _gdt_h


#include <stdint.h>

void 		gdt_init();
int 		gdt_add_descriptor(uint8_t id, uint64_t desc);
uint64_t	gdt_create_descriptor(uint32_t base, uint32_t limit, uint16_t flags);
void		set_kernel_stack();



#endif
