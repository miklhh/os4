#ifndef _gdt_h
#define _gdt_h

/* ------------------------------------------------
 * Header for handling the global descriptor table.
 * ------------------------------------------------ */



#include <stdint.h>

void 		gdt_init();
int 		gdt_add_descriptor(uint8_t id, uint64_t desc);
uint64_t	gdt_create_descriptor(uint32_t base, uint32_t limit, uint16_t flags);



#endif
